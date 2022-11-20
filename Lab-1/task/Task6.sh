for file in $@
do
if [ -f $file ]
then
echo $file | tr [:lower:] [:upper:]
else
echo "File $file does not exist"
fi
done