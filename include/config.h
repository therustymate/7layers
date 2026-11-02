#pragma once

#include "7layers.h"

#define DEBUG_MODE 1

// -------------------------------------------

typedef enum FILE_TYPE {
    DOCUMENT,
    IMAGE,
    VIDEO,
    AUDIO,
    TEXT,
    GENERAL,
    BINARY,
    DUMMY,
    SCRIPT,
    DUMP,
    VDISK,
} FILE_TYPE;

typedef struct _EXT_SCOPE {
    FILE_TYPE   type;
    const char* extension;
} EXT_SCOPE;

typedef struct _PATH_SCOPE {
    const char* path;
    int         recursive;
    int         max_depth;
} PATH_SCOPE;

// -------------------------------------------

static const EXT_SCOPE SCOPE_EXT_LIST[] = {
    // Allowed: Text File
    { TEXT,     "txt"       },      // Plain Text
    { TEXT,     "md"        },      // Markdown
    { TEXT,     "csv"       },      // Comma-Separated Values
    { TEXT,     "tsv"       },      // Tab-Separated Values
    { TEXT,     "json"      },      // JSON Data
    { TEXT,     "xml"       },      // XML Document
    { TEXT,     "yaml"      },      // YAML Data
    { TEXT,     "yml"       },      // YAML Data
    { TEXT,     "rtf"       },      // Rich Text Format

    // Allowed: Document
    { DOCUMENT, "pdf"       },      // PDF Document
    { DOCUMENT, "hwp"       },      // Hancom Document
    { DOCUMENT, "hwpx"      },      // Hancom XML Document
    { DOCUMENT, "doc"       },      // Legacy Word Document
    { DOCUMENT, "docx"      },      // Word Document
    { DOCUMENT, "odt"       },      // OpenDocument Text
    { DOCUMENT, "xls"       },      // Legacy Excel Spreadsheet
    { DOCUMENT, "xlsx"      },      // Excel Spreadsheet
    { DOCUMENT, "ods"       },      // OpenDocument Spreadsheet
    { DOCUMENT, "ppt"       },      // Legacy PowerPoint
    { DOCUMENT, "pptx"      },      // PowerPoint Presentation
    { DOCUMENT, "odp"       },      // OpenDocument Presentation
    { DOCUMENT, "epub"      },      // Electronic Publication

    // Allowed: Image
    { IMAGE,    "jpg"       },      // JPEG Image
    { IMAGE,    "jpeg"      },      // JPEG Image
    { IMAGE,    "png"       },      // Portable Network Graphics
    { IMAGE,    "bmp"       },      // Bitmap Image
    { IMAGE,    "gif"       },      // Graphics Interchange Format
    { IMAGE,    "webp"      },      // WebP Image
    { IMAGE,    "tif"       },      // Tagged Image File
    { IMAGE,    "tiff"      },      // Tagged Image File
    { IMAGE,    "svg"       },      // Scalable Vector Graphics

    // Allowed: Video
    { VIDEO,    "mp4"       },      // MPEG-4 Video
    { VIDEO,    "mkv"       },      // Matroska Video
    { VIDEO,    "avi"       },      // Audio Video Interleave
    { VIDEO,    "mov"       },      // QuickTime Video
    { VIDEO,    "webm"      },      // WebM Video
    { VIDEO,    "wmv"       },      // Windows Media Video

    // Allowed: Audio
    { AUDIO,    "mp3"       },      // MPEG Audio
    { AUDIO,    "wav"       },      // Waveform Audio
    { AUDIO,    "flac"      },      // Free Lossless Audio Codec
    { AUDIO,    "ogg"       },      // Ogg Container
    { AUDIO,    "m4a"       },      // MPEG-4 Audio
    { AUDIO,    "aac"       },      // Advanced Audio Coding
    { AUDIO,    "opus"      },      // Opus Audio

    // Allowed: Test Files
    { DUMMY,    "flag"      },      // Capture The Flag
    { DUMMY,    "target"    },      // Custom Test Target
    { DUMMY,    "dummy"     },      // Dummy Data

    // Conflict Test
    // { GENERAL,  "7layers"   },      // Encrypted File
};

static const PATH_SCOPE SCOPE_PATH_LIST[] = {
    { "%USERPROFILE%\\Documents",   1, 5 },
    { "%USERPROFILE%\\Downloads",   1, 1 },
    { "%USERPROFILE%\\Desktop",     1, 3 },
    { "%USERPROFILE%\\Pictures",    1, 3 },
    { "%USERPROFILE%\\Videos",      1, 3 },
    // { "%USERPROFILE%\\OneDrive",    1, 3 }, // Conflict Test
};

// -------------------------------------------

/*
[ DISCLAIMER ]
The current hard deny list is essential for ensuring the safety of red team exercises.
As this project is a ransomware simulation framework, additional precautions are necessary.
Therefore, any individual who modifies the files or entries currently protected by the hard deny list 
assumes full responsibility for any resulting damage, loss, or consequences.
*/

static const EXT_SCOPE HARD_DENY_EXT[] = {
    // Denied: General & 7layers
    { GENERAL,      "7layers"   },      // Encrypted File
    { GENERAL,      "tmp"       },      // Temporary File
    { GENERAL,      "clg"       },      // Catalog File

    // Denied: Log File
    { TEXT,         "log"       },      // General Log
    { TEXT,         "evtx"      },      // Modern Windows XML Event Log
    { TEXT,         "evt"       },      // Legacy Event Log
    { TEXT,         "etl"       },      // Event Trace Log
    { TEXT,         "iis"       },      // Web Server Activity Log

    // Denied: Dump File
    { DUMP,         "dmp"       },      // Standard Windows Memory Dump
    { DUMP,         "mdmp"      },      // Microsoft Minidump
    { DUMP,         "hdmp"      },      // Usermode Heap Dump
    { DUMP,         "dump"      },      // Generic Dump File
    { DUMP,         "dxdmp"     },      // DirectX Dump File
    { DUMP,         "core"      },      // Core Memory Snapshots

    // Denied: Disk Image
    { VDISK,        "vhd"       },      // Virtual Hard Disk
    { VDISK,        "vhdx"      },      // Virtual Hard Disk v2
    { VDISK,        "avhd"      },      // Snapshot Image
    { VDISK,        "vfd"       },      // Virtual Floppy Disk
    { VDISK,        "vdi"       },      // Oracle VirtualBox
    { VDISK,        "vmdk"      },      // VMWare
    { VDISK,        "iso"       },      // Standard Disk Image
    { VDISK,        "img"       },      // Raw Disk Image
    { VDISK,        "wim"       },      // Windows Imaging Format
    { VDISK,        "swm"       },      // Split Windows Image
    { VDISK,        "esd"       },      // Electronic Software Download

    // Denied: Binary
    { BINARY,       "exe"       },      // Standard Windows Executable
    { BINARY,       "dll"       },      // Dynamic Link Library
    { BINARY,       "sys"       },      // System & Device Driver
    { BINARY,       "com"       },      // Legacy Command-line Program
    { BINARY,       "msi"       },      // Windows Installer Package
    { BINARY,       "msp"       },      // Windows Patch File
    { BINARY,       "cpl"       },      // Control Panel Extension
    { BINARY,       "scr"       },      // Windows Screensaver
    { BINARY,       "bin"       },      // Raw Binary

    // Denied: Powershell & Batch
    { SCRIPT,       "bat"       },      // Batch Script
    { SCRIPT,       "cmd"       },      // CMD Script
    { SCRIPT,       "ps1"       },      // PowerShell Script
    { SCRIPT,       "psm1"      },      // Script Module
    { SCRIPT,       "psd1"      },      // Module Manifest / Data
    { SCRIPT,       "ps1xml"    },      // XML Configuration
    { SCRIPT,       "pssc"      },      // Session Configuration File
    { SCRIPT,       "psrc"      },      // Role Capability File
    { SCRIPT,       "cdxml"     },      // Cmdlet Definition XML
    { SCRIPT,       "psc1"      },      // Console File
};

static const PATH_SCOPE HARD_DENY_PATH[] = {
    { "%USERPROFILE%\\OneDrive",    0, 0 },
    { "%USERPROFILE%\\AppData",     0, 0 },
};