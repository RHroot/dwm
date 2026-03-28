#!/usr/bin/env bash

FILE="$HOME/.cache/Matugen/Matugen.colors"

# fallback colors (your current palette)
BG="#0e1116"
BG_ALT="#141922"
FG="#cfd6df"
FG_DIM="#5f6a7a"
ACCENT="#6a2c52"
BORDER="#243447"

get() {
  awk -F= -v s="$1" -v k="$2" '
        $0 ~ "\\["s"\\]" {f=1; next}
        f && $1==k {print $2; exit}
    ' "$FILE"
}

if [ -f "$FILE" ]; then
  BG=$(get "Colors:View" "BackgroundNormal" || echo "$BG")
  BG_ALT=$(get "Colors:View" "BackgroundAlternate" || echo "$BG_ALT")

  FG=$(get "Colors:View" "ForegroundNormal" || echo "$FG")
  FG_DIM=$(get "Colors:View" "ForegroundInactive" || echo "$FG_DIM")

  ACCENT=$(get "Colors:Selection" "BackgroundNormal" || echo "$ACCENT")
  BORDER=$(get "Colors:Window" "BackgroundNormal" || echo "$BORDER")
fi

cat >config_colors.h <<EOF
static const char col_bg[]     = "$BG";
static const char col_bg_alt[] = "$BG_ALT";

static const char col_fg[]     = "$FG";
static const char col_fg_dim[] = "$FG_DIM";

static const char col_accent[] = "$ACCENT";
static const char col_border[] = "$BORDER";
EOF
