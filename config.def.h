/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 5;        /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrains Mono:size=12" };
static const char col_gray1[]       = "#1E1E2E";
static const char col_gray2[]       = "#45475A";
static const char col_gray3[]       = "#CDD6F4";
static const char col_lavender[]    = "#B4BEFE";

static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray3, col_gray2, col_lavender },
};

/* tagging */
static const char *tags[] = { ".", ".", ".", ".", "." };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Google-chrome", NULL,    NULL,      1 << 1,      0,           -1 },
    { "Zathura",       NULL,    NULL,      1 << 2,      0,           -1 },
    { NULL,            NULL,  "Spotify",   1 << 4,      0,            1 },
    { "Pavucontrol",   NULL,    NULL,      0,           1,           -1 },
    { "Lxappearance",  NULL,    NULL,      0,           1,           -1 },
    { "Pcmanfm",       NULL,    NULL,      0,           1,           -1 },
};

/* layout(s) */
static const float mfact        = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;    /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    //{ "[]=",      tile },    /* first entry is default */
    { "",         tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define TERMINAL "alacritty"

#define STATUSBAR "dwmblocks"

/* commands */
static char monarg[2] = "0"; /* set to ascii value of current monitor number by spawn() */
static const char *dmenucmd[]     = { "dmenu_run", "-m", monarg, NULL };
static const char *termcmd[]      = { TERMINAL, NULL };
static const char *browser[]      = { "google-chrome-stable", NULL };
static const char *file_manager[] = { TERMINAL, "-e", "ranger", NULL };
static const char *powermenu[]    = { "powermenu", "-m", monarg, NULL };
static const char *network[]      = { "networkmanager_dmenu", "-m", monarg, "-l", "20", NULL };
static const char *bluetooth[]    = { "dmenu-bluetooth", "-m", monarg, NULL };
static const char *passmenu[]     = { "passmenu", "-m", monarg, NULL };
static const char *screenshot[]   = { "dmenu-screenshot", "-m", monarg, NULL };
static const char *todo[]         = { "todo", "-m", monarg, NULL };

static const Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask,             XK_s,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
    { MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
    { MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
    { MODKEY,                       XK_space,  zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY,                       XK_q,      killclient,     {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY|ShiftMask,             XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_f,      togglefloating, {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { MODKEY,                       XK_b,      spawn,          {.v = browser } },
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = file_manager } },
    { MODKEY,                       XK_x,      spawn,          {.v = powermenu } },
    { MODKEY|ShiftMask,             XK_n,      spawn,          {.v = network } },
    { MODKEY|ShiftMask,             XK_b,      spawn,          {.v = bluetooth } },
    { MODKEY|ShiftMask,             XK_p,      spawn,          {.v = passmenu } },
    { 0,                            XK_Print,  spawn,          {.v = screenshot } },
    { MODKEY|ShiftMask,             XK_t,      spawn,          {.v = todo } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
    { ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
    { ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
