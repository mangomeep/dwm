/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
static const int horizpadbar        = 0;     /* horizontal padding for statusbar */
static const int vertpadbar         = 0;     /* vertical padding for statusbar */
static const char *fonts[]          = { "Courier Prime Code:size=10" };
static const char dmenufont[]       = "Courier Prime Code:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#7700cc";
static const char col_urgborder[]   = "#ff0000";

//#include "/home/ratking/.cache/wal/colors-wal-dwm.h"
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeUrg]  = { col_gray4, col_cyan,  col_urgborder  },
};

/* tagging */
static const char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII", "IIX", "IX" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "(M)",      monocle },
	{ "HHH",      grid },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define PrtScn 0x0000ff61
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *termcmd[]  = { "alacritty", NULL }; //alacritty

static const char *discord[] = { "discord", "--use-gl=deskto:p", NULL };
//static const char *thunar[] = { "thunar", NULL };
static const char *firefox[] = { "firefox", NULL };
static const char *code[] = { "code-oss", NULL };

static const char *screenshot[] = { "scrot", "-q", "100", "/home/ratking/media/images/screenshots/%Y-%m-%d-%s.png", NULL };
//static const char *screenshotselect[] = { "maim", "-s", "|", "xclip", "-selection", "clipboard", "-t", "image/png", NULL };



static Key keys[] = {
	/* modifier				key			function	argument */
	{ MODKEY|ShiftMask,		XK_c,		killclient,	{0} },
	{ MODKEY|ShiftMask,		XK_p,		spawn,		{.v = dmenucmd } },
	{ MODKEY|ShiftMask,		XK_Return,	spawn,		{.v = termcmd } },

	{ MODKEY|ShiftMask,		XK_s,		spawn,		{.v = code } },
	{ MODKEY|ShiftMask,		XK_d,		spawn,		{.v = discord } },
	{ MODKEY|ShiftMask,		XK_f,		spawn,		{.v = firefox } },

//	{ MODKEY|ShiftMask,		XK_t,		spawn,		{.v = thunar } },

	{ MODKEY,				PrtScn,		spawn,		{.v = screenshot } },
//	{ MODKEY|ShiftMask,		PrtScn,		spawn,		{.v = screenshotselect} },

	{ MODKEY|ShiftMask,		XK_k,		rotatestack,	{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_j,		rotatestack,	{.i = -1 } },

	{ MODKEY,				XK_k,		focusstack,	{.i = +1 } },
	{ MODKEY,				XK_j,		focusstack,	{.i = -1 } },

	{ MODKEY,				XK_h,		setmfact,	{.f = -0.05} },
	{ MODKEY,				XK_l,		setmfact,	{.f = +0.05} },

	{ MODKEY,				XK_q,		incnmaster,	{.i = +1 } },
	{ MODKEY,				XK_e,		incnmaster,	{.i = -1 } },

	{ MODKEY,				XK_Return,	zoom,		{0} },
	{ MODKEY,				XK_Tab,		view,		{0} },
/*
	{ MODKEY|ShiftMask,		XK_t,		setlayout,	{.v = &layouts[0]} },
	{ MODKEY|ShiftMask,		XK_f,		setlayout,	{.v = &layouts[1]} },
	{ MODKEY|ShiftMask,		XK_m,		setlayout,	{.v = &layouts[2]} },
	{ MODKEY|ShiftMask,		XK_g,		setlayout,	{.v = &layouts[3]} },
*/
	{ MODKEY,				XK_comma,	cyclelayout,	{.i = -1 } },
	{ MODKEY,				XK_period,	cyclelayout,	{.i = +1 } },

	{ MODKEY,				XK_comma,	focusmon,	{.i = -1 } },
	{ MODKEY,				XK_period,	focusmon,	{.i = +1 } },

	{ MODKEY|ShiftMask,		XK_comma,	tagmon,		{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_period,	tagmon,		{.i = +1 } },

	{ MODKEY,				XK_space,	setlayout,	{0} },
	{ MODKEY|ShiftMask,		XK_space,	togglefloating,	{0} },

	{ MODKEY,				XK_b,		togglebar,	{0} },



	{ MODKEY,				XK_0,		view,		{.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,		tag,		{.ui = ~0 } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
/*
	TAGKEYS(                        XK_KP_1,                      0)
	TAGKEYS(                        XK_KP_2,                      1)
	TAGKEYS(                        XK_KP_3,                      2)
	TAGKEYS(                        XK_KP_4,                      3)
	TAGKEYS(                        XK_KP_5,                      4)
	TAGKEYS(                        XK_KP_6,                      5)
	TAGKEYS(                        XK_KP_7,                      6)
	TAGKEYS(                        XK_KP_8,                      7)
	TAGKEYS(                        XK_KP_9,                      8)
*/

	{ MODKEY|ShiftMask,				XK_q,      quit,           {1} },
	{ ControlMask|ShiftMask,		XK_q,      quit,           {0} },

};



/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button1,        zoom,           {0} },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkLtSymbol,			0,				Button1,		cyclelayout,	{.i = +1 }},
	{ ClkLtSymbol,			0,				Button3,		cyclelayout,	{.i = -1 }},
};
