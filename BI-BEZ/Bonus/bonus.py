import string


def main():
    f = open("ciphertexts", "r")
    ciphertexts = [line.rstrip() for line in f]
    ciphertexts = [bytearray.fromhex(ciphertext) for ciphertext in ciphertexts]
    key = get_key(ciphertexts)
    print(key)
    while(not is_key_complete(key)):
        print(
            " 0         1         2         3         4         5         6         7         8         9         0         1         2         ")
        print(
            " 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789")
        for y, x in enumerate(ciphertexts):
            xored_text = xor_key(x, key)
            print(f'{y}{to_ascii(xored_text)}')
        indices = input()
        x = indices.split(" ")
        print(f'x:{x[1]} y:{x[0]} char:{x[2]}')
        if x[2] == "del":
            key[int(x[1])] = None
        elif x[2] == "space":
            key[int(x[1])] = ord(" ") ^ ciphertexts[int(x[0])][int(x[1])]
        else:
            key[int(x[1])] = ord(x[2]) ^ ciphertexts[int(x[0])][int(x[1])]

def is_key_complete(key):
    for x in key:
        if x is None:
            return False
    return True


def xor_key(ciphertext, key):
    xored = []
    for x in range(0, len(ciphertext)):
        if key[x] != None:
            xored.append(key[x] ^ ciphertext[x])
        else:
            xored.append(None)
    return xored


def to_ascii(a):
    text = ""
    for x in a:
        if x != None:
            text += str(chr(x))
        else:
            text += "."
    return text


def xor(a, b):
    return [c ^ d for c, d in zip(a, b)]


def partial_key(ciphertexts):
    key = [None for _ in range(0, len(ciphertexts[0]))]

    for x in range(0, len(ciphertexts)):
        space_counter = {}
        for y in range(0, len(ciphertexts)):
            if x != y:
                xored = xor(ciphertexts[x], ciphertexts[y])
                for z in range(0, len(xored)):
                    if xored[z] == 0x00 or chr(xored[z]) in string.ascii_letters:
                        if z not in space_counter:
                            space_counter[z] = 1
                        else:
                            space_counter[z] += 1

        for index, count in space_counter.items():
            if count == len(ciphertexts) - 1:
                key[index] = ord(" ") ^ ciphertexts[x][index]

    return key


def get_key(ciphertexts):
    sorted_ciphertexts = sorted(ciphertexts, key=len)
    key = []

    while len(sorted_ciphertexts) > 1 and sorted_ciphertexts[0] != bytearray(b''):
        key += partial_key(sorted_ciphertexts)

        string_length = len(sorted_ciphertexts[0])
        print(f'deleting: {sorted_ciphertexts[0]}')
        sorted_ciphertexts.pop(0)
        for i in range(0, len(sorted_ciphertexts)):
            sorted_ciphertexts[i] = sorted_ciphertexts[i][string_length:]

    return key


if __name__ == '__main__':
    main()
