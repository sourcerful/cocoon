#!/usr/bin/env bash
#
# setup_rootfs.sh — Download and extract an Alpine Linux mini root filesystem
# for use as the container rootfs in cocoon.
#

set -euo pipefail

ALPINE_VERSION="3.21"
ALPINE_ARCH="x86_64"
ALPINE_MIRROR="https://dl-cdn.alpinelinux.org/alpine"
TARBALL="alpine-minirootfs-${ALPINE_VERSION}.0-${ALPINE_ARCH}.tar.gz"
URL="${ALPINE_MIRROR}/v${ALPINE_VERSION}/releases/${ALPINE_ARCH}/${TARBALL}"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
ROOTFS_DIR="${PROJECT_ROOT}/rootfs"

if [ -d "$ROOTFS_DIR" ] && [ "$(ls -A "$ROOTFS_DIR" 2>/dev/null)" ]; then
    echo "[*] rootfs/ already exists and is non-empty — skipping download."
    echo "    To re-download, remove it first: rm -rf ${ROOTFS_DIR}"
    exit 0
fi

echo "[*] Downloading Alpine Linux ${ALPINE_VERSION} mini-rootfs (${ALPINE_ARCH})..."
echo "    URL: ${URL}"

mkdir -p "$ROOTFS_DIR"

if command -v curl &>/dev/null; then
    curl -fSL "$URL" -o "/tmp/${TARBALL}"
elif command -v wget &>/dev/null; then
    wget -q --show-progress "$URL" -O "/tmp/${TARBALL}"
else
    echo "[!] Error: neither curl nor wget found. Install one and retry."
    exit 1
fi

echo "[*] Extracting to ${ROOTFS_DIR}..."
tar -xzf "/tmp/${TARBALL}" -C "$ROOTFS_DIR"
rm -f "/tmp/${TARBALL}"

echo "[*] Done. Root filesystem is ready at: ${ROOTFS_DIR}"
echo "    Contents:"
ls "$ROOTFS_DIR"
