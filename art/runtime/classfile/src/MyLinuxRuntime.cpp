#ifndef MYLINUX_RUNTIME_CPP
#define MYLINUX_RUNTIME_CPP

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#define CLASS_MAGIC 0xCAFEBABE
#define MAX_CLASS_SIZE (16 * 1024 * 1024)

namespace mylinux {
namespace art {

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef int32_t s4;

struct Reader {
    std::vector<u1> data;
    size_t pos = 0;

    bool read1(u1& v) {
        if (pos >= data.size()) return false;
        v = data[pos++];
        return true;
    }

    bool read2(u2& v) {
        u1 a, b;
        if (!read1(a) || !read1(b)) return false;
        v = ((u2)a << 8) | b;
        return true;
    }

    bool read4(u4& v) {
        u1 a, b, c, d;
        if (!read1(a) || !read1(b) ||
            !read1(c) || !read1(d)) return false;

        v = ((u4)a << 24) |
            ((u4)b << 16) |
            ((u4)c << 8) |
            (u4)d;
        return true;
    }

    bool readBytes(size_t n, std::vector<u1>& output) {
        if (n > data.size() - pos) return false;

        output.assign(data.begin() + pos,
                      data.begin() + pos + n);
        pos += n;
        return true;
    }

    bool skip(size_t n) {
        if (n > data.size() - pos) return false;
        pos += n;
        return true;
    }

    bool finished() const {
        return pos == data.size();
    }
};

struct Constant {
    u1 tag = 0;
    u4 value = 0;
    u2 a = 0;
    u2 b = 0;
    std::string text;
};

struct Method {
    std::string name;
    std::string descriptor;
    u2 maxStack = 0;
    u2 maxLocals = 0;
    std::vector<u1> code;
    bool hasCode = false;
};

struct ClassFile {
    u2 minorVersion = 0;
    u2 majorVersion = 0;
    std::vector<Constant> pool;
    std::vector<Method> methods;
};

class ClassParser {
private:
    static bool parseConstantPool(
        Reader& r,
        ClassFile& cf
    ) {
        u2 count;

        if (!r.read2(count) || count == 0) return false;

        cf.pool.resize(count);

        for (u2 i = 1; i < count; ++i) {
            Constant& c = cf.pool[i];

            if (!r.read1(c.tag)) return false;

            switch (c.tag) {
                case 1: {
                    u2 length;
                    if (!r.read2(length)) return false;

                    std::vector<u1> bytes;
                    if (!r.readBytes(length, bytes)) return false;

                    c.text.assign(bytes.begin(), bytes.end());
                    break;
                }

                case 3:
                case 4:
                    if (!r.read4(c.value)) return false;
                    break;

                case 5:
                case 6:
                    if (!r.read4(c.value) ||
                        !r.read4(c.a)) return false;

                    if (i + 1 >= count) return false;
                    ++i;
                    break;

                case 7:
                case 8:
                case 16:
                case 19:
                case 20:
                    if (!r.read2(c.a)) return false;
                    break;

                case 9:
                case 10:
                case 11:
                case 12:
                case 17:
                case 18:
                    if (!r.read2(c.a) ||
                        !r.read2(c.b)) return false;
                    break;

                case 15:
                    if (!r.read1(c.tag) ||
                        !r.read2(c.a)) return false;
                    break;

                default:
                    std::puts("ART: unsupported constant-pool tag");
                    return false;
            }
        }

        return true;
    }

    static std::string utf8(
        const ClassFile& cf,
        u2 index
    ) {
        if (index == 0 || index >= cf.pool.size() ||
            cf.pool[index].tag != 1) {
            throw std::runtime_error("Invalid UTF8 constant");
        }

        return cf.pool[index].text;
    }

    static bool parseCode(
        Reader& attribute,
        Method& method
    ) {
        u4 codeLength;

        if (!attribute.read2(method.maxStack) ||
            !attribute.read2(method.maxLocals) ||
            !attribute.read4(codeLength)) {
            return false;
        }

        if (codeLength > MAX_CLASS_SIZE) return false;

        if (!attribute.readBytes(codeLength, method.code)) {
            return false;
        }

        u2 exceptionCount;
        if (!attribute.read2(exceptionCount)) return false;

        if (!attribute.skip((size_t)exceptionCount * 8)) {
            return false;
        }

        u2 attributesCount;
        if (!attribute.read2(attributesCount)) return false;

        for (u2 i = 0; i < attributesCount; ++i) {
            u2 name;
            u4 length;

            if (!attribute.read2(name) ||
                !attribute.read4(length) ||
                !attribute.skip(length)) {
                return false;
            }
        }

        return attribute.finished();
    }

public:
    static bool parse(
        const char* filename,
        ClassFile& cf
    ) {
        assert(filename != nullptr);

        std::ifstream file(filename, std::ios::binary);

        if (!file) {
            std::puts("ART: cannot open class file");
            return false;
        }

        file.seekg(0, std::ios::end);
        std::streamoff size = file.tellg();

        if (size < 10 || size > MAX_CLASS_SIZE) {
            std::puts("ART: invalid class file size");
            return false;
        }

        file.seekg(0, std::ios::beg);

        Reader r;
        r.data.resize((size_t)size);

        if (!file.read(
                reinterpret_cast<char*>(r.data.data()),
                size)) {
            return false;
        }

        u4 magic;

        if (!r.read4(magic) || magic != CLASS_MAGIC) {
            std::puts("ART: invalid class magic");
            return false;
        }

        if (!r.read2(cf.minorVersion) ||
            !r.read2(cf.majorVersion)) {
            return false;
        }

        if (cf.majorVersion < 45 || cf.majorVersion > 52) {
            std::puts("ART: unsupported class version");
            return false;
        }

        if (!parseConstantPool(r, cf)) {
            std::puts("ART: constant-pool parsing failed");
            return false;
        }

        u2 accessFlags;
        u2 thisClass;
        u2 superClass;

        if (!r.read2(accessFlags) ||
            !r.read2(thisClass) ||
            !r.read2(superClass)) {
            return false;
        }

        u2 interfaceCount;
        if (!r.read2(interfaceCount) ||
            !r.skip((size_t)interfaceCount * 2)) {
            return false;
        }

        u2 fieldCount;
        if (!r.read2(fieldCount)) return false;

        for (u2 i = 0; i < fieldCount; ++i) {
            u2 flags, name, descriptor, attributes;

            if (!r.read2(flags) ||
                !r.read2(name) ||
                !r.read2(descriptor) ||
                !r.read2(attributes)) {
                return false;
            }

            for (u2 j = 0; j < attributes; ++j) {
                u2 attributeName;
                u4 length;

                if (!r.read2(attributeName) ||
                    !r.read4(length) ||
                    !r.skip(length)) {
                    return false;
                }
            }
        }

        u2 methodCount;
        if (!r.read2(methodCount)) return false;

        for (u2 i = 0; i < methodCount; ++i) {
            Method method;
            u2 flags, nameIndex, descriptorIndex, count;

            if (!r.read2(flags) ||
                !r.read2(nameIndex) ||
                !r.read2(descriptorIndex) ||
                !r.read2(count)) {
                return false;
            }

            method.name = utf8(cf, nameIndex);
            method.descriptor = utf8(cf, descriptorIndex);

            for (u2 j = 0; j < count; ++j) {
                u2 attributeName;
                u4 length;

                if (!r.read2(attributeName) ||
                    !r.read4(length)) {
                    return false;
                }

                if (length > r.data.size() - r.pos) {
                    return false;
                }

                std::vector<u1> bytes;

                if (!r.readBytes(length, bytes)) {
                    return false;
                }

                Reader attribute;
                attribute.data = std::move(bytes);

                if (utf8(cf, attributeName) == "Code") {
                    if (!parseCode(attribute, method)) {
                        return false;
                    }

                    method.hasCode = true;
                }
            }

            cf.methods.push_back(method);
        }

        u2 classAttributeCount;
        if (!r.read2(classAttributeCount)) return false;

        for (u2 i = 0; i < classAttributeCount; ++i) {
            u2 name;
            u4 length;

            if (!r.read2(name) ||
                !r.read4(length) ||
                !r.skip(length)) {
                return false;
            }
        }

        return r.finished();
    }

    static std::string getUtf8(
        const ClassFile& cf,
        u2 index
    ) {
        return utf8(cf, index);
    }
};

struct Value {
    int kind = 0;
    s4 integer = 0;
    std::string text;
};

enum {
    VALUE_INT = 1,
    VALUE_STRING = 2,
    VALUE_SYSTEM_OUT = 3,
    VALUE_NULL = 4
};

class Interpreter {
private:
    static Constant getConstant(
        const ClassFile& cf,
        u2 index
    ) {
        if (index == 0 || index >= cf.pool.size()) {
            throw std::runtime_error("Bad constant index");
        }

        return cf.pool[index];
    }

    static std::string resolveUtf8(
        const ClassFile& cf,
        u2 index
    ) {
        return ClassParser::getUtf8(cf, index);
    }

    static Value integerValue(s4 n) {
        Value v;
        v.kind = VALUE_INT;
        v.integer = n;
        return v;
    }

    static Value pop(std::vector<Value>& stack) {
        if (stack.empty()) {
            throw std::runtime_error("Operand stack underflow");
        }

        Value v = stack.back();
        stack.pop_back();
        return v;
    }

    static s4 popInteger(std::vector<Value>& stack) {
        Value v = pop(stack);

        if (v.kind != VALUE_INT) {
            throw std::runtime_error("Expected integer");
        }

        return v.integer;
    }

    static void push(
        std::vector<Value>& stack,
        const Value& value,
        u2 maxStack
    ) {
        if (stack.size() >= maxStack) {
            throw std::runtime_error("Operand stack overflow");
        }

        stack.push_back(value);
    }

    static Value loadConstant(
        const ClassFile& cf,
        u2 index
    ) {
        Constant c = getConstant(cf, index);

        if (c.tag == 3) {
            return integerValue((s4)c.value);
        }

        if (c.tag == 8) {
            Value v;
            v.kind = VALUE_STRING;
            v.text = resolveUtf8(cf, c.a);
            return v;
        }

        throw std::runtime_error("Unsupported ldc constant");
    }

    static std::string resolveMethodName(
        const ClassFile& cf,
        u2 index,
        std::string& descriptor
    ) {
        Constant method = getConstant(cf, index);

        if (method.tag != 10 && method.tag != 11) {
            throw std::runtime_error("Expected method reference");
        }

        Constant nat = getConstant(cf, method.b);

        if (nat.tag != 12) {
            throw std::runtime_error("Invalid NameAndType");
        }

        descriptor = resolveUtf8(cf, nat.b);
        return resolveUtf8(cf, nat.a);
    }

    static void executeInvokeVirtual(
        const ClassFile& cf,
        u2 index,
        std::vector<Value>& stack
    ) {
        std::string descriptor;
        std::string name =
            resolveMethodName(cf, index, descriptor);

        if (name != "println") {
            throw std::runtime_error("Unsupported virtual method");
        }

        Value argument = pop(stack);
        Value receiver = pop(stack);

        if (receiver.kind != VALUE_SYSTEM_OUT) {
            throw std::runtime_error("Unsupported method receiver");
        }

        if (descriptor == "(I)V" &&
            argument.kind == VALUE_INT) {
            std::printf("%d\n", argument.integer);
        } else if (descriptor == "(Ljava/lang/String;)V" &&
                   argument.kind == VALUE_STRING) {
            std::puts(argument.text.c_str());
        } else {
            throw std::runtime_error("Unsupported println descriptor");
        }
    }

public:
    static bool execute(
        const ClassFile& cf,
        const char* methodName
    ) {
        const Method* method = nullptr;

        for (const Method& candidate : cf.methods) {
            if (candidate.name == methodName &&
                candidate.descriptor == "([Ljava/lang/String;)V") {
                method = &candidate;
                break;
            }
        }

        if (method == nullptr) {
            std::puts("ART: main method not found");
            return false;
        }

        if (!method->hasCode) {
            std::puts("ART: main method has no Code attribute");
            return false;
        }

        std::vector<Value> stack;
        std::vector<Value> locals(method->maxLocals);

        Value args;
        args.kind = VALUE_NULL;

        if (!locals.empty()) {
            locals[0] = args;
        }

        size_t pc = 0;

        try {
            while (pc < method->code.size()) {
                u1 op = method->code[pc++];

                if (op == 0x00) {
                    continue;
                }

                if (op >= 0x02 && op <= 0x08) {
                    push(stack, integerValue((s4)op - 3),
                         method->maxStack);
                    continue;
                }

                if (op == 0x10) {
                    if (pc >= method->code.size()) {
                        throw std::runtime_error("Truncated bipush");
                    }

                    s4 n = (int8_t)method->code[pc++];
                    push(stack, integerValue(n), method->maxStack);
                    continue;
                }

                if (op == 0x11) {
                    if (pc + 1 >= method->code.size()) {
                        throw std::runtime_error("Truncated sipush");
                    }

                    u2 n = ((u2)method->code[pc] << 8) |
                           method->code[pc + 1];
                    pc += 2;

                    push(stack, integerValue((int16_t)n),
                         method->maxStack);
                    continue;
                }

                if (op >= 0x1a && op <= 0x1d) {
                    size_t index = op - 0x1a;

                    if (index >= locals.size()) {
                        throw std::runtime_error("Invalid local index");
                    }

                    push(stack, locals[index], method->maxStack);
                    continue;
                }

                if (op == 0x15 || op == 0x36) {
                    if (pc >= method->code.size()) {
                        throw std::runtime_error("Truncated local instruction");
                    }

                    size_t index = method->code[pc++];

                    if (index >= locals.size()) {
                        throw std::runtime_error("Invalid local index");
                    }

                    if (op == 0x15) {
                        push(stack, locals[index], method->maxStack);
                    } else {
                        locals[index] = pop(stack);
                    }

                    continue;
                }

                if (op >= 0x3b && op <= 0x3e) {
                    size_t index = op - 0x3b;

                    if (index >= locals.size()) {
                        throw std::runtime_error("Invalid istore index");
                    }

                    locals[index] = integerValue(popInteger(stack));
                    continue;
                }

                if (op == 0x60 || op == 0x64 || op == 0x68) {
                    s4 b = popInteger(stack);
                    s4 a = popInteger(stack);
                    uint32_t result = 0;

                    if (op == 0x60) {
                        result = (uint32_t)a + (uint32_t)b;
                    } else if (op == 0x64) {
                        result = (uint32_t)a - (uint32_t)b;
                    } else {
                        result = (uint32_t)a * (uint32_t)b;
                    }

                    push(stack, integerValue((s4)result),
                         method->maxStack);
                    continue;
                }

                if (op == 0x6c) {
                    s4 b = popInteger(stack);
                    s4 a = popInteger(stack);

                    if (b == 0) {
                        throw std::runtime_error("Integer division by zero");
                    }

                    if (a == INT32_MIN && b == -1) {
                        push(stack, integerValue(INT32_MIN),
                             method->maxStack);
                    } else {
                        push(stack, integerValue(a / b),
                             method->maxStack);
                    }

                    continue;
                }

                if (op == 0x12 || op == 0x13) {
                    u2 index;

                    if (op == 0x12) {
                        if (pc >= method->code.size()) {
                            throw std::runtime_error("Truncated ldc");
                        }
                        index = method->code[pc++];
                    } else {
                        if (pc + 1 >= method->code.size()) {
                            throw std::runtime_error("Truncated ldc_w");
                        }

                        index = ((u2)method->code[pc] << 8) |
                                method->code[pc + 1];
                        pc += 2;
                    }

                    push(stack, loadConstant(cf, index),
                         method->maxStack);
                    continue;
                }

                if (op == 0xb2) {
                    if (pc + 1 >= method->code.size()) {
                        throw std::runtime_error("Truncated getstatic");
                    }

                    u2 index = ((u2)method->code[pc] << 8) |
                               method->code[pc + 1];
                    pc += 2;

                    Constant field = getConstant(cf, index);

                    if (field.tag != 9) {
                        throw std::runtime_error("Invalid field reference");
                    }

                    Constant nat = getConstant(cf, field.b);

                    if (nat.tag != 12 ||
                        resolveUtf8(cf, nat.a) != "out") {
                        throw std::runtime_error("Unsupported static field");
                    }

                    Value v;
                    v.kind = VALUE_SYSTEM_OUT;
                    push(stack, v, method->maxStack);
                    continue;
                }

                if (op == 0xb6) {
                    if (pc + 1 >= method->code.size()) {
                        throw std::runtime_error("Truncated invokevirtual");
                    }

                    u2 index = ((u2)method->code[pc] << 8) |
                               method->code[pc + 1];
                    pc += 2;

                    executeInvokeVirtual(cf, index, stack);
                    continue;
                }

                if (op == 0xb1) {
                    std::puts("MyLinux ART: main returned");
                    return true;
                }

                throw std::runtime_error(
                    "Unsupported JVM opcode: " +
                    std::to_string(op)
                );
            }
        } catch (const std::exception& e) {
            std::fprintf(stderr, "ART interpreter error: %s\n",
                         e.what());
            return false;
        }

        std::puts("ART: method ended without return");
        return false;
    }
};

}
}

int main(int argc, char* argv[]) {
    using namespace mylinux::art;

    if (argc != 2) {
        std::puts("MyLinux Android Runtime (ART)");
        std::puts("Usage: mylinux-runtime file.class");
        return 1;
    }

    ClassFile cf;

    std::puts("MyLinux ART: loading class");

    if (!ClassParser::parse(argv[1], cf)) {
        std::puts("MyLinux ART: class loading failed");
        return 1;
    }

    std::puts("MyLinux ART: class parsed");
    std::printf("Class version: %u.%u\n",
                cf.majorVersion, cf.minorVersion);

    std::puts("MyLinux ART: executing main");

    if (!Interpreter::execute(cf, "main")) {
        return 1;
    }

    return 0;
}

#endif
