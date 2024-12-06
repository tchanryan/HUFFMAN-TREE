What is Encoding?
Encoding is the process of converting data into a different format.

In the real world, data often needs to be converted into different formats for efficient processing, storage or transmission, so there are many examples of encoding:

ASCII encoding, which converts commonly used characters to a 7 bit code
UTF-8 encoding, which converts a much wider range of characters to a 8-32 bit code
Base64 encoding, which converts binary data (often images) to Base64 text
SHA-256 converts a text/byte sequence to a hash which can be used for security purposes
QR codes, which convert various kinds of information (often a link) to a grid of black/white pixels
The aim of this assignment is to encode and decode text into/from a compressed format using an algorithm known as Huffman coding.

Huffman Coding
Huffman coding is an encoding method used for data compression where each character is encoded as a sequence of bits (0's and 1's). The result of running the algorithm is a Huffman tree, which is used for both encoding and decoding. Here is an example of a Huffman tree:


In a Huffman tree, all leaf nodes (and only leaf nodes) contain a character, and the encoding of each character, also known as the code word (or simply code) is defined by the path from the root to the character, with left and right corresponding to 0 and 1 respectively. For the above example, this means the code of "s" is "00", the code of "t" is "010", and so on. The text "stirred", which consists of multiple characters, would be encoded as "000101111010011110".

Since only the leaves of a Huffman tree contain characters, a Huffman code is known as a "prefix code", which is a type of code system where no code word is a prefix of another code word. This means that special markers are not required between code words (unlike Morse code, where long pauses are used to separate letters and words), and each encoding can be uniquely decoded - in other words, it is not possible for an encoding to be decoded to two different texts.

What makes Huffman coding particularly notable is that it produces an optimal prefix code. This means that out of all possible prefix codes, Huffman coding will always produce the encoding with the shortest length. This is achieved by making sure that characters that occur more frequently in the text will have shorter code words.

Binary Search Tree
A binary search tree is a binary tree which is ordered such that for each node, all items in its left subtree are less than the item in the node, and all items in its right subtree are greater than the item in the node. In the lectures and labs, we have been using binary search trees of integers - however in this assignment, you will be using binary search trees of strings.

You will use a binary search tree to implement a Counter ADT, which keeps track of the frequencies of characters. To achieve this, each node in the binary search tree will contain not just a character and left and right pointers, but an integer which indicates the number of occurrences of the character. For example, consider the following binary search tree of characters:


This shows, for example, that the character "e" occurs 5 times, the characters "a" and "s" occur 4 times, the characters "i", "n", "r" and "t" occur 3 times, and so on.

The World of Characters
So far in your computer science degree, you have likely mainly dealt with ASCII characters. There are 128 ASCII characters, which means an ASCII character can be represented by 7 bits (as 27 = 128). Most computers represent an ASCII character using 1 byte (8 bits), as it is easier for computers to read one byte at a time (as opposed to 7 bits).

In the real world however, there are many more than 128 characters, such as mathematical symbols (e.g., ∀, ∃), Chinese characters (e.g., ⽇, ⽉), Greek letters (e.g., Φ, Ψ) and emoji (e.g., 🐶️, 😺️). Unicode, which is a text encoding standard maintained by the Unicode Consortium, defines almost 150,000 characters that are used in various contexts around the world. Since it is clearly not possible to represent all of these characters using just one byte, Unicode characters are typically represented by a series of one to four bytes, depending on the character.

In this assignment, we will ensure that our Huffman coding algorithm is capable of encoding all kinds of text by representing a character as a string of one to four chars. This means that ASCII characters will be represented by a string with one char (plus the null terminating byte '\0'), whereas other characters (such as Greek letters) will be represented by a string of two, three or four chars (plus '\0'). You will not need to know or learn exactly how these characters are represented, as you will be provided with an ADT to read characters one at a time from a file. When working with these characters, you can treat them as regular C strings.
