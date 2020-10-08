#ifndef CONFIG_H

#ifdef __x86_64__
#define NTALERT_TITLE_BITLY "64-bit"
#else
#define NTALERT_TITLE_BITLY "32-bit"
#endif

#define NTALERT_VERSION_STRING "v0.2-rc2"

#define NTALERT_TITLE \
    ("NT Alert " NTALERT_VERSION_STRING " (" NTALERT_TITLE_BITLY ")" )

#endif /* CONFIG_H */
