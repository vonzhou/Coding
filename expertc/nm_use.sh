
cd /lib/x86_64-linux-gnu/
for i in lib?* 
do
    echo $i
    nm $i | grep pthread_create | grep -v UNDEF
done

cd ~/Coding/expertc/


















