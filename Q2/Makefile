instructions:
	echo "\n\nThere are four text files available:\nChristina Alberta's father.txt\nHistoria del levantamiento, guerra y.txt\nMountains and molehills.txt\nStraight America, a call to national service.txt\n\nTo compile the file run 'make compile'\n\nTo clean temporary files run 'make clean'\n\nTo run the file run './txt2epub *file1.txt* *file2.txt* ... *fileN.txt*', with the book names within quotes\n\nExample: txt2epub 'Christina Alberta's father.txt' 'Historia del levantamiento, guerra y.txt'  'Mountains and molehills.txt'\n"

clean:
	rm *.epub
	rm txt2epub
	rm *.zip

compile:
	gcc -Wall -o txt2epub txt2epub.c
