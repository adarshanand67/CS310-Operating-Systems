# # 7a) To extract a substring
# echo "Enter a string"
# read str
# echo "Enter a substring"
# read sub
# echo "Substring is: ${str#"$sub"}"

# b) To find the length of a given string
echo "Enter a string"
read str
len=${#str}
echo "Length of the string is $len"