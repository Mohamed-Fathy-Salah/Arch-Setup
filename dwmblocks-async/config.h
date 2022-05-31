#define CMDLENGTH 100
#define DELIMITER " ┃ "
#define CLICKABLE_BLOCKS

const Block blocks[] = {
	BLOCK("sb-date",    0,    1),
	BLOCK("sb-time",    60,   2),
    BLOCK("sb-prayer",  60,   10),
	BLOCK("sb-memory",  5,    3),
	BLOCK("sb-loadavg", 5,    4),
	BLOCK("sb-temp",    5,    5),
	BLOCK("sb-volume",  0,    6),
	BLOCK("sb-mic",     0,    7),
	BLOCK("sb-network", 5,    9),
	BLOCK("sb-lang",    0,    8),
};
