html2cpp
========

`html2cpp` is a (very) simple program that converts HTML documents to C++
programs.

OK, that statement was not very clear. Let me try again.

`html2cpp` takes an HTML document as standard input, transforms it according to
some basic rules, and writes a resulting C++ source file to standard output.

These "basic rules" are as follows:

1. Everything inside HTML comments (`<!--` and `-->`) is treated as C++
code, and is output verbatim.

2. Everything outside HTML comments are converted to a C++ double-quoted
strings.

I told you it was simple. It's basically the inverse of the C++ CGI tutorials
you'll find online - you don't embed HTML in your C++, you embed C++ in your
HTML.

This works in the same way as PHP, with code and raw output interspersed,
except that instead of the `<?php` and `?>` delimiters, you use regular HTML
comments.

Disadvantages
-------------

I wrote `html2cpp` in a couple of hours. It really is a quick-and-dirty
solution to get the job done. Here is some of the dirt.

### Confusing Syntax

The syntax can look confusing at first. The reason for this is that everything
outside HTML comments are treated as C++ strings, and so you need to do
something with them. You can't just have a C++ string sitting on it's own - it
has to be transformed, sent to standard output, etc, etc.

For example, beginning a C++ `for` loop may require the first character
to be a semi-colon (ending the previous operation with the HTML C++ string) and
likewise, the first characters after the opening brace might have to be
an instruction to do something with the trailing HTML C++ string.

    <!-- std::cout << -->I'm counting to <strong>10</strong>
    <!--; for (int i = 1; i <= 10; ++i) { std::cout << -->
        <strong><!-- << i << --></strong>
    <!--;} -->

A different way of formatting it might be:

    <!--
    #include <iostream>
    using std::cout;
    
    int main(int argc, const char** argv)
    {
        cout << -->I'm counting to <strong>10</strong><!--;
        for (int i = 1; i <= 10; ++i)
        {
            std::cout << --><strong><!-- << i << --></strong><!--;
        }
    }
    -->

Note, that it's easier to think of the syntax as `-->` and `<!--` surrounding a
double-quoted string. E.g., `-->LOOK AT ME, I'M A STRING<!--`.

### Possibility to Combine Responsibilities

Separation of concerns, particularly in relation to business logic and
presentation, is an important programming concept, and helps produce more
maintainable code. Because you have the full power of the C++ language in
your HTML templates, you might be tempted to just perform a little SQL or
transform a file, etc. This is a dangerous road. While libraries like
Java's [String Template] (http://www.stringtemplate.org/) *actively prevent*
the developer from doing something stupid in the view template, `html2cpp` has
no such safety belt - you have to maintain discipline and exercise common
sense about what you put in your template. You don't want to create a big
ball of mud, so in my view, you should limit yourself to only sending HTML
to standard output (or some other stream) and only performing const-operations
(no data mutation whatsoever, only data display). 

### Extra Build Step

Because C++ is the *output* of the program, you may need to add another
step to your build script. If you're using `cmake`, `make`, etc, this
could pose issues for your build-dependency detection, as the regeneration
will cause the file's timestamps to be updated. If your build tool has the
option to use checksums to detect changes, then this may not be an issue.

### Embedding HTML Comments

Because HTML comments are the C++ delimiters, it takes extra characters to
output HTML comments.

Advantages
----------

Here are some of the advantages.

### Valid HTML

Because the C++ code is contained in HTML comments, the templates themselves
can be [fully HTML-compliant] (https://validator.w3.org/). That means you
can get a non-developer to write up a pretty HTML page, then you can insert
the data by simply commenting on their HTML.

### Simple Syntax

Yes, the syntax can be ugly. But like anything, the more you use it, the more
you get used to it. Are you a vim power user? If so, you'll remember the
initial frustration of your early experiences before you learnt about
text objects, movements, custom operators, etc.

### Flexible Implementation

Do you want your view to be a class? Do you want it to be a simple function?
Do you want to provide it is a shared-library (`.so` file) that can be
distributed? Do whatever you want. It's C++ and C-style strings.

### Fast

Because the HTML strings are in-memory, any generated C++ code will be fast.  I
haven't written any benchmarks, because I don't want to waste my time. But I
imagine it'd be faster than other approaches, such as pseudo-template
languages, passing data to PHP for processing, etc, etc.

Similar Projects
----------------

* [C++ Server Pages] (http://www.micronovae.com/CSP.html) by micronovae. The
reason why I didn't like this project was that it was too complicated.
* [Poco C++ Page Compiler] (https://pocoproject.org/docs/PageCompilerUserGuide.html).
The Poco project is awesome, but again, what if you don't want to subclass
`Poco::Net::HTTPRequestHandler`?
* [Google cTemplate] (https://github.com/OlafvdSpek/ctemplate). A great project
but I dislike the API.
* [Mustache] (https://github.com/no1msd/mstch).

Licence
-------

This project is licenced under the GPL 3.0. See `LICENCE.markdown`.
