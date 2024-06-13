#!/bin/bash

MONGO_URL="mongodb://backup_user:************@192.168.7.109:30101,192.168.7.109:30102,192.168.7.109:30103/Database?authSource=admin&replicaSet=rs1"
BACKUP_DIR="mongobackup-`date +%Y-%m-%d`"
BACKUP_COLLECTION_PARALLELISM="4"
KEEP_DAYS=30

echo "##################################"
echo "Remove old backup Older than '$KEEP_DAYS' days"
echo "##################################"

find /jobs/backups/ -type d -mtime +$KEEP_DAYS -exec rm -rf {} \; 

echo "##################################"
echo "Backup will start at '`date`' for database: '$MONGO_URL'"
echo "##################################"

mongodump --uri="$MONGO_URL" --numParallelCollections="$BACKUP_COLLECTION_PARALLELISM" --gzip --out "/jobs/backups/$BACKUP_DIR"

echo "##################################"
echo "Backup completed at '`date`' to '$BACKUP_PARENT_DIR/$BACKUP_DIR'"
echo "##################################"

