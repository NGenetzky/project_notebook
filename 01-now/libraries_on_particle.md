
# The Red Hat newlib C Library

Particle supports all functions in the [newlib C library][1]

```
• _Exit:	  	End program execution without cleaning up
• a64l:	  	String to long long
• abort:	  	Abnormal termination of a program
• abs:	  	Integer absolute value (magnitude)
• assert:	  	Macro for Debugging Diagnostics
• atexit:	  	Request execution of functions at program exit
• atof:	  	String to double or float
• atoi:	  	String to integer
• atoll:	  	String to long long
• bsearch:	  	Binary search
• calloc:	  	Allocate space for arrays
• div:	  	Divide two integers
• ecvtbuf:	  	Double or float to string of digits
• ecvt:	  	Double or float to string of digits (malloc result)
• __env_lock:	  	Lock environment list for getenv and setenv
• gvcvt:	  	Format double or float as string
• exit:	  	End program execution
• getenv:	  	Look up environment variable
• labs:	  	Long integer absolute value (magnitude)
• ldiv:	  	Divide two long integers
• llabs:	  	Long long integer absolute value (magnitude)
• lldiv:	  	Divide two long long integers
• malloc:	  	Allocate and manage memory (malloc, realloc, free)
• mallinfo:	  	Get information about allocated memory
• __malloc_lock:	  	Lock memory pool for malloc and free
• mbsrtowcs:	  	Convert a character string to a wide-character string
• mbstowcs:	  	Minimal multibyte string to wide string converter
• mblen:	  	Minimal multibyte length
• mbtowc:	  	Minimal multibyte to wide character converter
• on_exit:	  	Request execution of functions at program exit
• qsort:	  	Array sort
• rand:	  	Pseudo-random numbers
• rand48:	  	Uniformly distributed pseudo-random numbers
• strtod:	  	String to double or float
• strtol:	  	String to long
• strtoll:	  	String to long long
• strtoul:	  	String to unsigned long
• strtoull:	  	String to unsigned long long
• wcsrtombs:	  	Convert a wide-character string to a character string
• wcstod:	  	Wide string to double or float
• wcstol:	  	Wide string to long
• wcstoll:	  	Wide string to long long
• wcstoul:	  	Wide string to unsigned long
• wcstoull:	  	Wide string to unsigned long long
• system:	  	Execute command string
• wcstombs:	  	Minimal wide string to multibyte string converter
• wctomb:	  	Minimal wide character to multibyte converter
```

[1]: https://sourceware.org/newlib/libc.html