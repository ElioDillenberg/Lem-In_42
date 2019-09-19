#!/bin/bash
LINES_REQUIRED=0
NUMBER_OF_TESTS=20
NB_PASSED=0


echo "RUNNNING $NUMBER_OF_TESTS --flow-one tests";
for ((cnt = 0 ; cnt < $NUMBER_OF_TESTS ; cnt++)); do { grep -e "KO" &};
    ARG=$(./generator --flow-one)
    LINES_REQUIRED=$(echo "$ARG" | grep -e "#Here is the number of lines required:" | sed -E 's/#Here is the number of lines required: ([0-9]+)/\1/' | uniq)
    ret=$(echo "$ARG" | ./lem-in | grep -e "^L[0-9]*" | wc -l)
    if [[  $ret -le $LINES_REQUIRED ]]; then
        ((NB_PASSED++))
    else
        echo "Number of extra lines$((ret - LINES_REQUIRED))"
    fi
done

echo "RUNNNING $NUMBER_OF_TESTS --flow-ten tests";
for ((cnt = 0 ; cnt < $NUMBER_OF_TESTS ; cnt++)); do { grep -e "KO" &};
    ARG=$(./generator --flow-ten)
    LINES_REQUIRED=`echo "$ARG" | grep -e "#Here is the number of lines required:" | sed -E 's/#Here is the number of lines required: ([0-9]+)/\1/' | uniq`
    ret=$(echo "$ARG" | ./lem-in | grep -e "^L[0-9]*" | wc -l)
    if [[  $ret -le $LINES_REQUIRED ]]; then
        ((NB_PASSED++))
    else
        echo "Number of extra lines$((ret - LINES_REQUIRED))"
    fi
done

echo "RUNNNING $NUMBER_OF_TESTS --flow-thousand tests";
for ((cnt = 0 ; cnt < $NUMBER_OF_TESTS ; cnt++)); do { grep -e "KO" &};
    ARG=$(./generator --flow-thousand)
    LINES_REQUIRED=$(echo "$ARG" | grep -e "#Here is the number of lines required:" | sed -E 's/#Here is the number of lines required: ([0-9]+)/\1/' | uniq)
    ret=$(echo "$ARG" | ./lem-in | grep -e "^L[0-9]*" | wc -l)
    if [[  $ret -le $LINES_REQUIRED ]]; then
        ((NB_PASSED++))
    else
        echo "Number of extra lines : $((ret - LINES_REQUIRED))"
    fi
done


echo "RUNNNING $NUMBER_OF_TESTS --big tests";
for ((cnt = 0 ; cnt < $NUMBER_OF_TESTS ; cnt++)); do { grep -e "KO" &};
    ARG=$(./generator --big)
    LINES_REQUIRED=$(echo "$ARG" | grep -e "#Here is the number of lines required:" | sed -E 's/#Here is the number of lines required: ([0-9]+)/\1/' | uniq)
    ret=$(echo "$ARG" | ./lem-in | grep -e "^L[0-9]*" | wc -l)
    if [[  $ret -le $LINES_REQUIRED ]]; then
        ((NB_PASSED++))
    else
        echo "Number of extra lines $((ret - LINES_REQUIRED))"
    fi
done

echo "RUNNNING $NUMBER_OF_TESTS --big-superposition tests";
for ((cnt = 0 ; cnt < $NUMBER_OF_TESTS ; cnt++)); do { grep -e "KO" &};
    ARG=$(./generator --big-superposition)
    LINES_REQUIRED=$(echo "$ARG" | grep -e "#Here is the number of lines required:" | sed -E 's/#Here is the number of lines required: ([0-9]+)/\1/' | uniq)
    ret=$(echo "$ARG" | ./lem-in | grep -e "^L[0-9]*" | wc -l)
    if [[ $ret -le $((LINES_REQUIRED + 10)) ]]; then
        ((NB_PASSED++))
        echo "Under 10"
    else
        echo "Number of extra lines $((ret - LINES_REQUIRED))"
    fi
done

echo "Number of passed tests under 10 : $NB_PASSED/$((NUMBER_OF_TESTS))"