#! /bin/bash

for i in $( ls | grep '\.cl$' ); do
    #echo $i
    ../../cool --lex $i |& grep -i 'lex'
    lex=$?
    ../../cool --parse $i |& grep -i 'parse'
    parse=$?
    ../../cool --type $i |& grep -i 'type'
    type=$?
    #echo $lex
    #echo $parse
    #echo $type
    if [ $lex -eq 0 ]; then
        mv $i lex/$i
    elif [ $parse -eq 0 ]; then
        mv $i parse/$i
    elif [ $type -eq 0 ]; then
        mv $i type/$i
    else
        mv $i valid/$i
    fi;
done;
