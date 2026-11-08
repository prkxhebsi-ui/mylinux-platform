package android

import (
	"fmt"
	"os"
	"strconv"
	"strings"
	"unicode"
)

type token struct {
	kind string
	text string
	pos  int
}

type lexer struct {
	input string
	pos   int
}

func (l *lexer) next() (token, error) {
	for l.pos < len(l.input) {
		ch := l.input[l.pos]

		if unicode.IsSpace(rune(ch)) {
			l.pos++
			continue
		}

		if strings.HasPrefix(l.input[l.pos:], "//") {
			for l.pos < len(l.input) && l.input[l.pos] != '\n' {
				l.pos++
			}
			continue
		}

		if strings.HasPrefix(l.input[l.pos:], "/*") {
			end := strings.Index(l.input[l.pos+2:], "*/")
			if end < 0 {
				return token{}, fmt.Errorf("unterminated comment at %d", l.pos)
			}
			l.pos += end + 4
			continue
		}

		break
	}

	if l.pos >= len(l.input) {
		return token{kind: "eof", pos: l.pos}, nil
	}

	start := l.pos
	ch := l.input[l.pos]

	if ch == '"' {
		l.pos++

		for l.pos < len(l.input) {
			if l.input[l.pos] == '\\' {
				l.pos += 2
				continue
			}

			if l.input[l.pos] == '"' {
				l.pos++
				raw := l.input[start:l.pos]
				value, err := strconv.Unquote(raw)
				if err != nil {
					return token{}, err
				}
				return token{kind: "string", text: value, pos: start}, nil
			}

			l.pos++
		}

		return token{}, fmt.Errorf("unterminated string at %d", start)
	}

	if strings.ContainsRune("{}[]:,", rune(ch)) {
		l.pos++
		return token{kind: string(ch), text: string(ch), pos: start}, nil
	}

	if unicode.IsLetter(rune(ch)) || ch == '_' {
		for l.pos < len(l.input) {
			r := rune(l.input[l.pos])
			if !unicode.IsLetter(r) &&
				!unicode.IsDigit(r) &&
				r != '_' {
				break
			}
			l.pos++
		}

		return token{
			kind: "ident",
			text: l.input[start:l.pos],
			pos:  start,
		}, nil
	}

	return token{}, fmt.Errorf("unexpected character %q at %d", ch, start)
}

type parser struct {
	lex lexer
	tok token
}

func newParser(source string) (*parser, error) {
	p := &parser{lex: lexer{input: source}}
	if err := p.advance(); err != nil {
		return nil, err
	}
	return p, nil
}

func (p *parser) advance() error {
	t, err := p.lex.next()
	if err != nil {
		return err
	}
	p.tok = t
	return nil
}

func (p *parser) expect(kind string) error {
	if p.tok.kind != kind {
		return fmt.Errorf(
			"expected %q at %d, got %q",
			kind, p.tok.pos, p.tok.text,
		)
	}
	return p.advance()
}

func (p *parser) value() (any, error) {
	switch p.tok.kind {
	case "string":
		v := p.tok.text
		return v, p.advance()

	case "ident":
		v := p.tok.text
		if err := p.advance(); err != nil {
			return nil, err
		}

		switch v {
		case "true":
			return true, nil
		case "false":
			return false, nil
		default:
			return nil, fmt.Errorf("unsupported value %q", v)
		}

	case "[":
		if err := p.advance(); err != nil {
			return nil, err
		}

		var values []any

		for p.tok.kind != "]" {
			if p.tok.kind == "eof" {
				return nil, fmt.Errorf("unterminated list")
			}

			v, err := p.value()
			if err != nil {
				return nil, err
			}

			values = append(values, v)

			if p.tok.kind == "," {
				if err := p.advance(); err != nil {
					return nil, err
				}
			} else if p.tok.kind != "]" {
				return nil, fmt.Errorf("expected comma or closing bracket")
			}
		}

		return values, p.advance()

	default:
		return nil, fmt.Errorf("unexpected value at %d", p.tok.pos)
	}
}

func (p *parser) module() (*Module, error) {
	if p.tok.kind != "ident" {
		return nil, fmt.Errorf("expected module type at %d", p.tok.pos)
	}

	moduleType := p.tok.text

	if err := p.advance(); err != nil {
		return nil, err
	}

	if err := p.expect("{"); err != nil {
		return nil, err
	}

	properties := make(map[string]any)

	for p.tok.kind != "}" {
		if p.tok.kind == "eof" {
			return nil, fmt.Errorf("unterminated module %s", moduleType)
		}

		if p.tok.kind != "ident" {
			return nil, fmt.Errorf("expected property at %d", p.tok.pos)
		}

		key := p.tok.text

		if _, exists := properties[key]; exists {
			return nil, fmt.Errorf("duplicate property %s", key)
		}

		if err := p.advance(); err != nil {
			return nil, err
		}

		if err := p.expect(":"); err != nil {
			return nil, err
		}

		v, err := p.value()
		if err != nil {
			return nil, fmt.Errorf("property %s: %w", key, err)
		}

		properties[key] = v

		if p.tok.kind == "," {
			if err := p.advance(); err != nil {
				return nil, err
			}
		} else if p.tok.kind != "}" {
			return nil, fmt.Errorf("expected comma or closing brace")
		}
	}

	if err := p.advance(); err != nil {
		return nil, err
	}

	m := &Module{
		Type:       moduleType,
		Enabled:    true,
		Properties: properties,
	}

	name, ok := properties["name"].(string)
	if !ok || name == "" {
		return nil, fmt.Errorf("%s module requires a name", moduleType)
	}
	m.Name = name

	m.Srcs = stringList(properties["srcs"])
	m.Cflags = stringList(properties["cflags"])

	m.Deps = append(m.Deps, stringList(properties["deps"])...)
	m.Deps = append(m.Deps, stringList(properties["shared_libs"])...)
	m.Deps = append(m.Deps, stringList(properties["static_libs"])...)
	m.Deps = append(m.Deps, stringList(properties["whole_static_libs"])...)

	if enabled, ok := properties["enabled"].(bool); ok {
		m.Enabled = enabled
	}

	return m, nil
}

func stringList(value any) []string {
	values, ok := value.([]any)
	if !ok {
		return nil
	}

	var result []string

	for _, v := range values {
		if s, ok := v.(string); ok {
			result = append(result, s)
		}
	}

	return result
}

func Parse(source string) ([]*Module, error) {
	p, err := newParser(source)
	if err != nil {
		return nil, err
	}

	var modules []*Module

	for p.tok.kind != "eof" {
		m, err := p.module()
		if err != nil {
			return nil, err
		}
		modules = append(modules, m)
	}

	return modules, nil
}

func ParseFile(path string) ([]*Module, error) {
	data, err := os.ReadFile(path)
	if err != nil {
		return nil, err
	}

	return Parse(string(data))
}
