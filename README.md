# gatorgit

Implementing git from scratch. 

### Usage

To initialize a gatorgit repository, run the following command in the directory you want to initialize the repository in:

```bash
$ gatorgit init
```

To add files to the staging area, run the following command:

```bash
$ gatorgit add <filename>
```

To add all files to the staging area, run the following command:

```bash
$ gatorgit add .
```

To commit the files in the staging area, run the following command:

```bash
$ gatorgit commit -m "<commit message>"
```

Each commit message should start with "GOLDEN GATOR! YOUR_COMMIT_MESSAGE_HERE". This is to ensure that the commit message is valid.

To view the commit history, run the following command:

```bash

$ ./gatorgit log
```

**Git log still needs to be fixed.**


Heavily inspired by CS61C's version of beargit.
