/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
#define TERMINAL "st"
/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]    = {
    "SauceCodePro Nerd Font:pixelsize=16:antialias=true:autohint=true" ,
    "Noto Naskh Arabic:pixelsize=16:antialias=true:autohint=true"
};

static const char dmenufont[] =  "SauceCodePro Nerd Font:pixelsize=16:antialias=true:autohint=true";
static const char normfgcolor[]      = "#ebdbb2";
static const char normbgcolor[]      = "#282828";
static const char normbordercolor[]  = "#928374";
static const char selfgcolor[]       = "#3281ea";
static const char selbgcolor[]       = "#282828";
static const char selbordercolor[]   = "#3281ea";
static const char *colors[][3]       = {
    /*                fg            bg              border           */
    [SchemeNorm]  = { normfgcolor,  normbgcolor,    normbordercolor  },
    [SchemeSel]   = { selfgcolor,   selbgcolor,     selbordercolor   },
    //[SchemeTitle] = { titlefgcolor, titlebgcolor,   titlebordercolor },
};

/* tagging */
static const char *tags[] = { "Ⅰ", "Ⅱ", "Ⅲ", "Ⅳ", "Ⅴ"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "  ",      tile },    /* first entry is default */
	{ " ",      centeredmaster },
	{ "  ",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALT Mod1Mask

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                    KEY,      view,            {.ui = 1 << TAG} }, \
	{ MODKEY|ALT,                KEY,      tag,             {.ui = 1 << TAG} }, \


#define STACKKEYS(MOD,ACTION) \
    { MOD,  XK_l,   ACTION##stack,  {.i = INC(+1) } }, \
    { MOD,  XK_h,   ACTION##stack,  {.i = INC(-1) } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define STATUSBAR "dwmblocks"

static char dmenumon[2] = "0";
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };

static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ALT,                      push)

	TAGKEYS(		            	XK_1,	   0)
	TAGKEYS(		            	XK_2,	   1)
	TAGKEYS(		    	        XK_3,	   2)
	TAGKEYS(		    	        XK_4,	   3)
	TAGKEYS(		            	XK_5,	   4)

	{ MODKEY,		            	XK_q,	   killclient,     {0} },
	{ MODKEY|ALT,               	XK_q,	   spawn,          SHCMD("sysact") },
	{ MODKEY,		            	XK_w,	   spawn,          SHCMD("firefox") },
	{ MODKEY,		    	        XK_c,	   spawn,          SHCMD("code") },
	{ MODKEY,		    	        XK_v,	   spawn,          SHCMD(TERMINAL " -e vim") },
	{ MODKEY,		            	XK_f,	   spawn,          SHCMD(TERMINAL " -e lf") },
	{ MODKEY,          	            XK_s,      spawn,          SHCMD(TERMINAL " -e htop") },

	{ MODKEY|ALT,			        XK_t,	   setlayout,      {.v = &layouts[0]} }, /* tile */
	{ MODKEY|ALT,			        XK_c,	   setlayout,      {.v = &layouts[1]} }, /* centeredmaster */
	{ MODKEY|ALT,    		        XK_f,	   setlayout,      {.v = &layouts[2]} }, /* float */
	{ MODKEY|ALT,			        XK_m,	   togglefullscr,  {0} },

	{ MODKEY|ALT,	                XK_i,	   incnmaster,     {.i = +1 } },
	{ MODKEY|ALT,	                XK_u,	   incnmaster,     {.i = -1 } },

	{ MODKEY,                       XK_i,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_u,      setmfact,       {.f = -0.05} },

	{ MODKEY,			            XK_d,	   spawn,          {.v = dmenucmd} },

	{ MODKEY,			            XK_j,	   shiftview,      { .i = -1 } },
	{ MODKEY,			            XK_k,	   shiftview,      { .i = +1 } },
	{ MODKEY|ALT,   	            XK_j,	   shifttag,       { .i = -1 } },
	{ MODKEY|ALT,   	            XK_k,	   shifttag,       { .i = +1 } },

	{ MODKEY,	            		XK_Return, spawn,		   {.v = termcmd } },

	{ MODKEY,			            XK_b,	   togglebar,	   {0} },

	{ MODKEY,			            XK_e,	   zoom,		   {0} },
	//{ MODKEY|ShiftMask,	XK_f,	togglefloating,	{0} },

	//{ 0,				            XK_Print,  spawn,	       SHCMD("maim ~/pictures/pic-full-$(date '+%y%m%d-%H%M-%S').png ;cat ~/pictures/pic-full-$(date '+%y%m%d-%H%M-%S').png | xclip -selection clipboard -t image/png") },
	//{ ALT,      		            XK_Print,  spawn,		   SHCMD("maim -i $(xdotool getactivewindow) ~/pictures/pic-full-$(date '+%y%m%d-%H%M-%S').png ;cat ~/pictures/pic-full-$(date '+%y%m%d-%H%M-%S').png | xclip -selection clipboard -t image/png") },
	{ 0,				            XK_Print,  spawn,	       SHCMD("maim ~/Pictures/pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ ShiftMask,		            XK_Print,  spawn,		   SHCMD("maim -s ~/Pictures/pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ ALT,      		            XK_Print,  spawn,		   SHCMD("maim -i $(xdotool getactivewindow) ~/Pictures/pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ ControlMask,				    XK_Print,  spawn,	       SHCMD("maim | xclip -selection clipboard -t image/png") },
	{ ControlMask|ShiftMask,	    XK_Print,  spawn,		   SHCMD("maim -s | xclip -selection clipboard -t image/png") },
	{ ControlMask|ALT,      		XK_Print,  spawn,		   SHCMD("maim -i $(xdotool getactivewindow) | xclip -selection clipboard -t image/png") },
	//{ MODKEY,			XK_Print,	spawn,		SHCMD("dmenurecord") },
	//{ MODKEY|ShiftMask,	XK_Print,	spawn,		SHCMD("dmenurecord kill") },
	//{ MODKEY,			XK_Delete,	spawn,		SHCMD("dmenurecord kill") },

	{ 0, XF86XK_AudioMute,		    spawn,	   SHCMD("pactl set-sink-mute 0 toggle && kill-40 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,	   SHCMD("pactl -- set-sink-volume 0 +5% && kill-40 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,	   SHCMD("pactl -- set-sink-volume 0 -5% && kill-40 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPrev,	        spawn,	   SHCMD("mpc prev") },
	{ 0, XF86XK_AudioNext,	        spawn,	   SHCMD("mpc next") },
	{ 0, XF86XK_AudioPause,	        spawn,	   SHCMD("mpc pause") },
	{ 0, XF86XK_AudioPlay,	        spawn,	   SHCMD("mpc play") },
	{ 0, XF86XK_AudioStop,	        spawn,	   SHCMD("mpc stop") },
	{ 0, XF86XK_AudioRewind,        spawn,	   SHCMD("mpc seek -10") },
	{ 0, XF86XK_AudioForward,   	spawn,	   SHCMD("mpc seek +10") },
	{ 0, XF86XK_AudioMedia,	    	spawn,	   SHCMD(TERMINAL " -e ncmpcpp") },
	{ 0, XF86XK_AudioMicMute,   	spawn,	   SHCMD("pactl set-source-mute 0 toggle") },
	{ 0, XF86XK_PowerOff,	    	spawn,	   SHCMD("sysact") },
	{ 0, XF86XK_Calculator,	    	spawn,	   SHCMD(TERMINAL " -e bc -l") },
	{ 0, XF86XK_Sleep,	        	spawn,     SHCMD("sudo -A zzz") },
	//{ 0, XF86XK_Mail,		spawn,		SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ 0, XF86XK_MyComputer,		    spawn,     SHCMD(TERMINAL " -e lf /") },
	/* { 0, XF86XK_Battery,		spawn,		SHCMD("") }, */

	//{ 0, XF86XK_TouchpadToggle,	spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	//{ 0, XF86XK_TouchpadOff,	spawn,		SHCMD("synclient TouchpadOff=1") },
	//{ 0, XF86XK_TouchpadOn,		spawn,		SHCMD("synclient TouchpadOff=0") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,     SHCMD("xbacklight -inc 15") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,	   SHCMD("xbacklight -dec 15") },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	//{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	//{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	//{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	//{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	//{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,            0,              Button4,        shiftview,      { .i = +1 } },
	{ ClkStatusText,        0,              Button5,        shiftview,      { .i = -1 } },
	{ ClkClientWin,         MODKEY,         Button4,        shifttag,       { .i = +1 } },
	{ ClkClientWin,         MODKEY,         Button5,        shifttag,       { .i = -1 } },
};

