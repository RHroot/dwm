#include <X11/XF86keysym.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>

/* appearance */
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const char *fonts[] = {"FiraCode Nerd Font:size=14"};
/* custom colors */
#include "config_colors.h"
static const char *colors[][3] = {
    [SchemeNorm] = {col_fg_dim, col_bg, col_bg},
    [SchemeOcc] = {col_fg, col_bg_alt, col_bg_alt},
    [SchemeSel] = {col_fg, col_bg_sel, col_accent},
};

static const char *const autostart[] = {
    /* Display setup */
    "sh", "-c",
    "out=$(xrandr | awk '/ primary/{print $1}'); "
    "[ -z \"$out\" ] && out=$(xrandr | awk '/ connected/{print $1; exit}'); "
    "[ -n \"$out\" ] && xrandr --output \"$out\" --mode 1920x1080 --rate 60",
    NULL,
    /* Daemons */
    "sh", "-c", "pgrep -x picom >/dev/null || picom", NULL, "sh", "-c",
    "pgrep -x dunst >/dev/null || dunst", NULL, "sh", "-c",
    "pgrep -x nm-applet >/dev/null || nm-applet", NULL, "sh", "-c",
    "pgrep -x clipmenud >/dev/null || clipmenud", NULL, "sh", "-c",
    "pgrep -x slstatus >/dev/null || slstatus", NULL, "sh", "-c",
    "pgrep -x libinput-gestures >/dev/null || libinput-gestures", NULL,
    /* Input */
    "xset", "r", "rate", "200", "40", NULL,
    /* Wallpaper */
    "sh", "-c", "sleep 0.5; [ -f ~/.fehbg ] && ~/.fehbg", NULL,

    NULL};

/* tagging */
static const char *tags[] = {"", "",  "", "", "",
                             "", "󰗀", "", "", ""};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Gimp", NULL, NULL, 0, 1, -1},
    {"Firefox", NULL, NULL, 1 << 8, 0, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */
static const int refreshrate =
    120; /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static const char *myterminal[] = {"alacritty", NULL};
static const char *myfilemanager[] = {"nautilus", NULL};
static const char *mymenu[] = {"rofi", "-show", "run", NULL};
static const char *mybettermenu[] = {"rofi", "-show", "drun", NULL};
static const char *mythememenu[] = {"sh", "-c",
                                    "$HOME/env/nixos/modules/WM/wset", NULL};
static const char *mybrowserpersonal[] = {"brave",
                                          "--profile-directory=Default", NULL};
static const char *mybrowserwork[] = {"brave", "--profile-directory=Profile 1",
                                      NULL};

static const Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_Return, spawn, {.v = myterminal}},
    {MODKEY, XK_space, spawn, {.v = mymenu}},
    {MODKEY, XK_e, spawn, {.v = myfilemanager}},
    {MODKEY | ShiftMask, XK_space, spawn, {.v = mybettermenu}},
    {MODKEY, XK_b, spawn, {.v = mybrowserpersonal}},
    {MODKEY | ShiftMask, XK_b, spawn, {.v = mybrowserwork}},
    {ControlMask | ShiftMask, XK_space, spawn, {.v = mythememenu}},
    {MODKEY, XK_q, killclient, {0}},
    {MODKEY | ShiftMask, XK_p, togglebar, {0}},
    {MODKEY | ShiftMask, XK_v, spawn, SHCMD("pavucontrol")},
    {MODKEY, XK_v, spawn, SHCMD("CM_LAUNCHER=rofi clipmenu")},
    {MODKEY, XK_f, togglefullscr, {0}},
    {MODKEY, XK_j, viewprev, {0}},
    {MODKEY, XK_k, viewnext, {0}},
    {ALTKEY | ShiftMask, XK_space, spawn,
     SHCMD("$HOME/env/nixos/modules/WM/wset")},
    {MODKEY | ShiftMask, XK_Right, tagtonext, {0}},
    {MODKEY | ShiftMask, XK_Left, tagtoprev, {0}},
    {ALTKEY, XK_j, focusstack, {.i = +1}},
    {ALTKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY | ControlMask, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY | ShiftMask, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY | ControlMask, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY | ControlMask, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY | ControlMask, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_f, togglefloating, {0}},
    {MODKEY | ShiftMask, XK_minus, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    {MODKEY | ShiftMask,
     XK_r,
     quit,
     {1}}, /* this is for reloading dwm without quitting the X session */
    {MODKEY | ControlMask, XK_q, quit, {0}},
    {0, XF86XK_MonBrightnessUp, spawn, SHCMD("brightnessctl set +10%")},
    {0, XF86XK_MonBrightnessDown, spawn, SHCMD("brightnessctl set 10%-")},
    {0, XF86XK_AudioRaiseVolume, spawn,
     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+")},
    {0, XF86XK_AudioLowerVolume, spawn,
     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-")},
    {0, XF86XK_AudioMute, spawn,
     SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle")},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8) TAGKEYS(XK_0, 9)};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function
       argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
