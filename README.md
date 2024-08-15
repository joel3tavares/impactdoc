# impactdoc

A tool to extract impact information from doc comments.

## Motivation

Many large applications are tightly coupled, so changes in one part can impact others. This project will implement a tool that extracts the information about the impact from the tag @impact in doc comments and shows them for help when the code is changed.

The following is a simplified diagram.

![implementation overview](images/1.png)

## Tags

### @impact

The @impact tag can be used to document side effects that may occur if the code is changed.

```
@impact <description>
```

Example:

```
/**
 * @impact This change affects login and logout functionality.
 */
function doSomething()
{
    // ...
}
```

## Requirements

* g++ with support for the C++20 standard
* make

## Build

```
$ make
```

## Usage

```
impactdoc <SourceCode.php> <Changed lines separated by spaces>
```

Example:

```
$ impactdoc LoginService.php 30 55
```

## Current issues

The current version is a pre-release and only supports parsing PHP code. If you want to fix a bug or implement a new feature, feel free to submit a pull request.