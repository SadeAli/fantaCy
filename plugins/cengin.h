#ifndef CENGIZ_H
#define CENGIZ_H

#define ENTRY _EntryPoint

#define STRINGIFY(x) STRINGIFY2(x)
#define STRINGIFY2(x) #x
#define ENTRY_NAME STRINGIFY(ENTRY)
#define ENTRY_FUNCTION void ENTRY()

#endif // CENGIZ_H