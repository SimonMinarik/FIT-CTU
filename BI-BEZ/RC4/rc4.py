import sys
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend


def main(arg):
    if arg[0] == "encrypt":
        encrypt()

    elif arg[0] == "decrypt":
        decrypt()

    elif arg[0] == "decipher":
        decipher()

    else:
        print("Zly argument.. dostupne: \"encrypt\", \"decrypt\", \"decipher\"")


def encrypt():
    iv = b'doesnt_matter'
    print("Kluc pre zasifrovanie sprav (16 znakov):")
    key = get_key()
    algorithm = algorithms.ARC4(key)
    cipher = Cipher(algorithm, mode=None, backend=default_backend())
    encryptor = cipher.encryptor()
    print("Text na zasifrovanie:")  # Knowledge will give you power.
    encode_str = input()
    ct2 = encryptor.update(encode_str.encode()) + encryptor.finalize()
    print(f'Zasifrovany text "{encode_str}":')
    print_hex(ct2)


def decrypt():
    print("Kluc pre desifrovanie sprav (16 znakov):")
    key = get_key()
    print("Text na desifrovanie:")  # Knowledge will give you power.
    encode_str = input()
    algorithm = algorithms.ARC4(key)
    cipher1 = Cipher(algorithm, mode=None, backend=default_backend())
    decryptor = cipher1.decryptor()
    dt1 = decryptor.update(bytes.fromhex(encode_str)) + decryptor.finalize()
    print(f'Desifrovany text: {dt1}')


def decipher():
    print("Znamy text?")
    znamy_text = input()

    print(f'Zasifrovany text pre znamy text {znamy_text}?')
    x = input()
    if not is_correct(x, 0):
        exit(0)
    x = bytearray.fromhex(x)  # znamy_text

    print("Zasifrovany text pre neznamy text?")
    y_str = input()
    if not is_correct(y_str, 1):
        exit(0)
    y = bytearray.fromhex(y_str)  # secret

    abc = znamy_text.encode()

    key = [c ^ d for c, d in zip(x, abc)]  # ziskanie klucu

    ot = [c ^ d for c, d in
          zip(bytearray(key), y[:len(znamy_text)])]  # xor klucu a zasifrovaneho textu = ot

    print("Desifrovany text:")
    for p in ot:
        print(chr(p), end="")
    if len(ot) < len(y_str):
        for x in range(len(ot) * 2, len(y_str)):
            print(y_str[x], end="")
    print()


def get_key():
    key_str = input()  # pribinacek_kakao
    if len(key_str) != 16:
        print("Nespravna dlzka klucu")
        exit(0)
    return key_str.encode()


def print_hex(y):
    for x in y:
        if len(hex(x)[2:]) == 1:
            print("0" + hex(x)[2:], end="")
        else:
            print(hex(x)[2:], end="")
    print()


def is_correct(x, length=None):
    if length is None:
        if len(x) != 60:
            print("Zla dlzka textu")
            return False
    tmp = x
    for character in ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f"]:
        tmp = tmp.upper().replace(character.upper(), "")
    if len(tmp) != 0:
        print("Nekorektny hex format")
        return False
    return True


if __name__ == '__main__':
    main(sys.argv[1:])
