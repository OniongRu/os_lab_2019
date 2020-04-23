#! /bin?sh
res=0
for m in $@
do
        res=$(($res + $m))
done
res=$(($res/$#))
echo "Кол-во праметров: $#\nИх среднее арифметическое: $res"
exit 0
