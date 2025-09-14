#!/usr/bin/env bash
set -euo pipefail

REPO_DIR="/opt/iobroker/iobroker-data/esphome.0"
BRANCH="main"

cd "$REPO_DIR"

# Repo für root als "safe"
git config --global --add safe.directory "$REPO_DIR"

# Änderungen? (erfasst auch untracked)
if [ -n "$(git status --porcelain)" ]; then
  # Liste geänderter Dateien für Syslog (nach dem Add ist die Liste ggf. anders)
  CHANGES="$(git status --porcelain | awk '{print $2}' | xargs echo || true)"

  git add -A
  git commit -m "ESPHome Auto-Commit $(date +'%Y-%m-%d %H:%M:%S')"

  if git push origin "$BRANCH"; then
    logger -t esphome-git "Auto-Commit OK: $(date +'%Y-%m-%d %H:%M:%S')"
    [ -n "$CHANGES" ] && logger -t esphome-git "Geändert: $CHANGES"
  else
    logger -t esphome-git "Auto-Commit FEHLGESCHLAGEN: $(date +'%Y-%m-%d %H:%M:%S')"
    exit 1
  fi
else
  logger -t esphome-git "Keine Änderungen"
fi

