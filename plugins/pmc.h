#ifndef PMC_H
#define PMC_H

// pmc stands for "plugin message codes"
// These are the codes that are returned by the plugin
// to the parent program to indicate what to do next.
// The parent program will then act accordingly.

#define FAILURE -1
#define SUCCESS 0
#define EXIT 1
#define RECOMPILE 2

#endif