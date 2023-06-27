A Todo List Manager for the Command Line!

# Why?
I personally enjoy and perfer working using the terminal. I use vim as a text editor and bash commands to view and manipulate files. This is a habit I picked up since I had linux as my main OS for a couple years.

I found myself constantly opening up vim in random places within my file tree to write a todo list on the spot. This causes problems later because these files are scattered and not all in one place. As such, I decided to write a program to manage my own Todos in the terminal. 

No flashy GUI, No complicated commands.

Just something like

```bash
$ todo ls 
$ todo add <item> 
$ todo rm 2 # removes second item
```

It then became practical to have my todos grouped together by category. For example my work todos and uni todos. 

```bash
$ todo mk <group>
$ todo ls <group>
$ todo add -g <group> <item>
$ todo rm -g <group> <item>
```

With the old ls add and rm working on a "default" group.

# Commands 
1. List

Shows all items in the group. If no group provided default group is assumed.
```bash
$ todo ls
$ todo ls <group>
```

1. Make

Makes a new group.
```bash
$ todo mk
```

1. Add

Adds Items to a group. if no group provided default group is assumed.
```bash
$ todo add this is an example item
$ todo add -g <group> this is an example item
```
1. Remove

Removes item from a group. Uses item count. Item count is shown in List output. If no group is provided default group is assumed.
```bash
$ todo rm 2 
$ todo rm -g <group> 2 
```

# How to use?
1. Currently the todos directory that holds the text files with the todo lists' data is hardcoded in the code to /Users/abdelrahmanelhawary/.todos, so change it to /Your/path/.todos 

1. Then Compile the code. 

1. place the compiled binary into some folder that is in you PATH environment variable

1. Use todo from anywhere on the command line to manage your todos!
