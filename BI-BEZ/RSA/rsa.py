import sys
import os
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import padding
from cryptography.hazmat.primitives import padding as padding2

"""
1st argument: encrypt/decrypt
2nd argument: file to encrypt/decrypt
3rd argument: key (pubkey for encrypt, privkey for decrypt)
"""


def main(args):
    if len(args) != 3:
        print("Wrong number of arguments")
        exit(0)
    if args[0].upper() not in ["ENCRYPT", "DECRYPT"]:
        print("App can only encrypt/decrypt")
        exit(0)
    if not os.access(args[1], os.R_OK):
        print("File couldn't be opened, try again.\n")
        exit(0)

    if args[0].upper() == "ENCRYPT":
        encrypt(file=args[1], pem=args[2])
    else:
        decrypt(file=args[1], pem=args[2])


def encrypt(file, pem):
    print("AES cipher will be used to encrypt your data, which mode would you like to use?\nAvailable modes: CBC, CFB")
    mode = ""
    while True:
        mode = input()
        if mode.upper() in ["CBC", "CFB"]:
            break
        else:
            print("Sorry, this mode isn't supported.\nAvailable modes: CBC, CFB")
    key = os.urandom(32)
    iv = os.urandom(16)

    with open(pem, "rb") as key_file:
        public_key = serialization.load_pem_public_key(key_file.read(), backend=default_backend())

    encrypted_key = public_key.encrypt(
        key,
        padding.OAEP(mgf=padding.MGF1(algorithm=hashes.SHA256()), algorithm=hashes.SHA256(), label=None))

    encrypted_file = open("encrypted_file", "wb")
    encrypted_file.write(b'AES')

    if mode.upper() == "CBC":
        encrypted_file.write(b'CBC')
    else:
        encrypted_file.write(b'CFB')

    encrypted_file.write(len(encrypted_key).to_bytes(2, 'big'))

    encrypted_file.write(encrypted_key)

    encrypted_file.write(iv)

    if mode.upper() == "CBC":
        cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
    else:
        cipher = Cipher(algorithms.AES(key), modes.CFB(iv), backend=default_backend())

    x = open(file, "rb")
    while True:
        data = x.read(16)
        if len(data) != 16:
            padder = padding2.PKCS7(128).padder()
            padded_data = padder.update(data) + padder.finalize()
            ct = cipher.encryptor().update(data)
            unpadder = padding2.PKCS7(128).unpadder()
            data = unpadder.update(padded_data)
            encrypted_file.write(data + unpadder.finalize())
            break
        ct = cipher.encryptor().update(data)
        encrypted_file.write(ct)
    cipher.encryptor().finalize()

    x.close()
    encrypted_file.close()


def decrypt(file, pem):
    encrypted_file = open(file, "rb")

    used_cipher = encrypted_file.read(3)
    if used_cipher != b'AES':
        print(f'Sorry, the cipher "{used_cipher}" isn\'t supported')
        exit(0)

    used_mode = encrypted_file.read(3)
    if used_mode not in [b"CBC", b"CFB"]:
        print(f'Sorry, the mode "{used_mode}" isn\'t supported')
        exit(0)

    len_of_encrypted_key = encrypted_file.read(2)
    encrypted_key = encrypted_file.read(int.from_bytes(len_of_encrypted_key, "big"))

    iv = encrypted_file.read(16)

    with open(pem, "rb") as key_file:
        private_key = serialization.load_pem_private_key(
            key_file.read(), password=None, backend=default_backend())

    decrypted_key = private_key.decrypt(
        encrypted_key,
        padding.OAEP(
            mgf=padding.MGF1(algorithm=hashes.SHA256()), algorithm=hashes.SHA256(), label=None))

    if used_mode == b"CBC":
        cipher = Cipher(algorithms.AES(decrypted_key), modes.CBC(iv), backend=default_backend())
    else:
        cipher = Cipher(algorithms.AES(decrypted_key), modes.CFB(iv), backend=default_backend())

    decrypted_file = open("decrypted_file", "wb")
    while True:
        data = encrypted_file.read(16)
        if len(data) != 16:
            padder = padding2.PKCS7(128).padder()
            padded_data = padder.update(data) + padder.finalize()
            ct = cipher.decryptor().update(data)
            unpadder = padding2.PKCS7(128).unpadder()
            data = unpadder.update(padded_data)
            decrypted_file.write(data + unpadder.finalize())
            break
        ct = cipher.decryptor().update(data)
        decrypted_file.write(ct)

    cipher.decryptor().finalize()
    decrypted_file.close()
    encrypted_file.close()

if __name__ == "__main__":
    main(sys.argv[1:])
