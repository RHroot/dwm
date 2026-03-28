#!/usr/bin/env bash

FILE="$HOME/.cache/Matugen/waybar-colors.css" # adjust path if needed
OUT="$HOME/dwm/config_colors.h"

# fallback colors
BG="#0e1116"
BG_ALT="#141922"
FG="#cfd6df"
FG_DIM="#5f6a7a"
ACCENT="#6a2c52"
BORDER="#243447"

get() {
  grep -E "@define-color $1 " "$FILE" | awk '{print $3}' | tr -d ';'
}

if [ -f "$FILE" ]; then
  BG=$(get surface || echo "$BG")
  BG_ALT=$(get surface_container || echo "$BG_ALT")
  BG_SEL=$(get surface_container_high || echo "$BG_ALT")

  FG=$(get on_surface || echo "$FG")
  FG_DIM=$(get on_surface_variant || echo "$FG_DIM")

  ACCENT=$(get primary || echo "$ACCENT")
  BORDER=$(get outline_variant || echo "$BORDER")
fi

cat >"$OUT" <<EOF
static const char col_bg[]     = "$BG";
static const char col_bg_alt[] = "$BG_ALT";
static const char col_bg_sel[] = "$BG_SEL";

static const char col_fg[]     = "$FG";
static const char col_fg_dim[] = "$FG_DIM";

static const char col_accent[] = "$ACCENT";
static const char col_border[] = "$BORDER";
EOF
