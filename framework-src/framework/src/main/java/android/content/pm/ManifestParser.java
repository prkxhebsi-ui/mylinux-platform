package android.content.pm;

public final class ManifestParser {
    private String source;
    private int position;
    private int length;
    private ManifestNode root;
    private ManifestNode[] stack;
    private int depth;

    public ManifestDocument parse(String xml) {
        if (xml == null) throw new IllegalArgumentException("Null XML");

        source = xml;
        position = 0;
        length = xml.length();
        root = null;
        stack = new ManifestNode[32];
        depth = 0;

        while (position < length) {
            if (source.charAt(position) == '<') {
                parseMarkup();
            } else {
                parseText();
            }
        }

        if (depth != 0) fail("Unclosed XML element");
        if (root == null) fail("Missing XML root element");

        ManifestDocument document = new ManifestDocument(root);
        document.parsed = true;
        return document;
    }

    private void parseMarkup() {
        if (startsWith("<!--")) {
            skipUntil("-->");
            return;
        }

        if (startsWith("<?")) {
            skipUntil("?>");
            return;
        }

        if (startsWith("<![CDATA[")) {
            position += 9;
            int end = source.indexOf("]]>", position);
            if (end < 0) fail("Unclosed CDATA section");

            if (depth > 0) {
                stack[depth - 1].appendText(
                        source.substring(position, end));
            }

            position = end + 3;
            return;
        }

        if (startsWith("</")) {
            parseClosingTag();
            return;
        }

        if (startsWith("<!")) {
            fail("Unsupported XML declaration");
        }

        parseOpeningTag();
    }

    private void parseOpeningTag() {
        position++;

        String name = readName();
        if (name.length() == 0) fail("Missing element name");

        ManifestNode node = new ManifestNode(name);
        boolean selfClosing = false;

        while (position < length) {
            skipWhitespace();

            if (startsWith("/>")) {
                position += 2;
                selfClosing = true;
                break;
            }

            if (startsWith(">")) {
                position++;
                break;
            }

            String key = readName();
            if (key.length() == 0) fail("Invalid attribute name");

            skipWhitespace();

            if (position >= length || source.charAt(position) != '=') {
                fail("Expected '=' after attribute");
            }

            position++;
            skipWhitespace();

            if (position >= length) fail("Missing attribute value");

            char quote = source.charAt(position);

            if (quote != '"' && quote != '\'') {
                fail("Attribute values must be quoted");
            }

            position++;
            int start = position;

            while (position < length && source.charAt(position) != quote) {
                position++;
            }

            if (position >= length) fail("Unclosed attribute value");

            String value = decodeEntities(source.substring(start, position));
            position++;

            node.setAttribute(key, value);
        }

        if (depth == 0) {
            if (root != null) fail("Multiple XML root elements");
            root = node;
        } else {
            stack[depth - 1].addChild(node);
        }

        if (!selfClosing) {
            if (depth == stack.length) {
                ManifestNode[] expanded =
                        new ManifestNode[stack.length * 2];

                for (int i = 0; i < depth; i++) expanded[i] = stack[i];
                stack = expanded;
            }

            stack[depth++] = node;
        }
    }

    private void parseClosingTag() {
        position += 2;

        String name = readName();
        skipWhitespace();

        if (position >= length || source.charAt(position) != '>') {
            fail("Invalid closing tag");
        }

        position++;

        if (depth == 0) fail("Unexpected closing tag");

        ManifestNode current = stack[depth - 1];

        if (!current.name.equals(name)) {
            fail("Mismatched closing tag: " + name);
        }

        stack[--depth] = null;
    }

    private void parseText() {
        int start = position;

        while (position < length && source.charAt(position) != '<') {
            position++;
        }

        if (depth > 0) {
            stack[depth - 1].appendText(
                    decodeEntities(source.substring(start, position)));
        } else {
            String outside = source.substring(start, position).trim();
            if (outside.length() != 0) fail("Text outside XML root");
        }
    }

    private String readName() {
        int start = position;

        while (position < length) {
            char c = source.charAt(position);

            if (Character.isLetterOrDigit(c)
                    || c == '_' || c == '-' || c == ':' || c == '.') {
                position++;
            } else {
                break;
            }
        }

        return source.substring(start, position);
    }

    private void skipWhitespace() {
        while (position < length
                && Character.isWhitespace(source.charAt(position))) {
            position++;
        }
    }

    private boolean startsWith(String value) {
        return source.startsWith(value, position);
    }

    private void skipUntil(String terminator) {
        int end = source.indexOf(terminator, position);

        if (end < 0) fail("Unclosed XML declaration");

        position = end + terminator.length();
    }

    private String decodeEntities(String value) {
        StringBuilder output = new StringBuilder();

        for (int i = 0; i < value.length(); i++) {
            char c = value.charAt(i);

            if (c != '&') {
                output.append(c);
                continue;
            }

            int end = value.indexOf(';', i + 1);

            if (end < 0) {
                fail("Invalid XML entity");
            }

            String entity = value.substring(i + 1, end);

            if ("amp".equals(entity)) output.append('&');
            else if ("lt".equals(entity)) output.append('<');
            else if ("gt".equals(entity)) output.append('>');
            else if ("quot".equals(entity)) output.append('"');
            else if ("apos".equals(entity)) output.append('\'');
            else if (entity.startsWith("#")) {
                try {
                    int code;

                    if (entity.startsWith("#x")) {
                        code = Integer.parseInt(entity.substring(2), 16);
                    } else {
                        code = Integer.parseInt(entity.substring(1));
                    }

                    output.append((char) code);
                } catch (RuntimeException error) {
                    fail("Invalid numeric XML entity");
                }
            } else {
                fail("Unknown XML entity: " + entity);
            }

            i = end;
        }

        return output.toString();
    }

    private void fail(String message) {
        throw new IllegalArgumentException(
                message + " at XML position " + position);
    }
}
