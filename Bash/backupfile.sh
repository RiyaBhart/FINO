#!/bin/bash


if [ $# -ne 1 ]; then
    echo "Usage: $0 <directory_path>"
    exit 1
fi

SOURCE_DIR=$1
BACKUP_DIR=~/backups 
TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
BACKUP_PATH="$BACKUP_DIR/backup_$(basename "$SOURCE_DIR")_$TIMESTAMP"


mkdir -p "$BACKUP_DIR"

rsync -av --progress "$SOURCE_DIR" "$BACKUP_PATH"

FILE_COUNT=$(find "$SOURCE_DIR" -type f | wc -l)
DIR_COUNT=$(find "$SOURCE_DIR" -type d | wc -l)

echo "Backup completed!"
echo "Backup location: $BACKUP_PATH"
echo "Files backed up: $FILE_COUNT"
echo "Directories backed up: $DIR_COUNT"

