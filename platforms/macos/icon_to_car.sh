#!/usr/bin/env bash

ICON_PATH="PartyBoard.icon"
OUTPUT_PATH="icons"
PLIST_PATH="assetcatalog_generated_info.plist"
DEVELOPMENT_REGION="en" # Change if necessary

# Adapted from https://github.com/electron/packager/pull/1806/files
actool $ICON_PATH --compile $OUTPUT_PATH \
  --output-format human-readable-text --notices --warnings --errors \
  --output-partial-info-plist $PLIST_PATH \
  --app-icon PartyBoard --include-all-app-icons \
  --enable-on-demand-resources NO \
  --development-region $DEVELOPMENT_REGION \
  --target-device mac \
  --minimum-deployment-target 11.0 \
  --platform macosx
