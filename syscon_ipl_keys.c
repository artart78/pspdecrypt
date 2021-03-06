/* Functions for handling 02g-11g BFC00210 Xor Keys with required syscon secrets
    by Proxima - 2021
*/

#include <stdio.h>
#include <string.h>
#include "libkirk/AES.h"

unsigned char sc_secret_01_tabl[0x400] = 
{   0x1A, 0x52, 0x1B, 0xDE, 0x7A, 0xDB, 0x8D, 0xDF, 0xF6, 0x07, 0x9F, 0xCC, 0x0F, 0x0B, 0x67, 0x14, 
    0x8C, 0x8F, 0x46, 0x24, 0xFA, 0xE0, 0x2C, 0x2C, 0x7F, 0xF5, 0x71, 0x1C, 0x93, 0x9A, 0xA7, 0x02, 
    0xAB, 0xE2, 0x8F, 0xE7, 0xDA, 0x89, 0x08, 0x27, 0x3D, 0xEF, 0x6E, 0x42, 0x07, 0x95, 0xB3, 0x30, 
    0x87, 0x37, 0x1B, 0x17, 0x50, 0x11, 0x36, 0xEE, 0xBD, 0x00, 0x8B, 0x27, 0x8C, 0xD6, 0xD1, 0x89, 
    0x75, 0xD1, 0x06, 0x61, 0x44, 0x83, 0xBF, 0x64, 0x7A, 0x16, 0xEE, 0x67, 0xFE, 0x81, 0xAB, 0xB5, 
    0xD2, 0x65, 0x10, 0x66, 0xFE, 0x74, 0x9F, 0x19, 0x1A, 0xD4, 0xB1, 0x15, 0x74, 0x00, 0x61, 0x79, 
    0xAE, 0xFA, 0xBA, 0xCF, 0x1C, 0x5F, 0x88, 0x7E, 0xF1, 0x5D, 0xE4, 0xAF, 0xE1, 0xAB, 0x51, 0xF6, 
    0xD6, 0xD0, 0xC0, 0x26, 0x56, 0x0E, 0x34, 0x11, 0x43, 0xFF, 0x51, 0xC4, 0x23, 0x36, 0x3A, 0xAE, 
    0xCE, 0x89, 0x52, 0xE2, 0xD2, 0xB5, 0x9D, 0xF5, 0x0A, 0xFC, 0x17, 0x6F, 0x25, 0xE8, 0x84, 0xD6, 
    0x22, 0x4E, 0x4B, 0x4E, 0x13, 0x6B, 0x3D, 0xB6, 0x73, 0xD2, 0x1C, 0xFC, 0xD1, 0x64, 0xD9, 0xFE, 
    0x97, 0xD7, 0xED, 0x0E, 0x60, 0xEC, 0x47, 0x21, 0x28, 0x86, 0xDE, 0xB9, 0xA6, 0x8D, 0xE1, 0x85, 
    0x23, 0xD3, 0x19, 0xD1, 0xF0, 0x7D, 0x42, 0xAE, 0x26, 0xDD, 0xDF, 0x87, 0x1E, 0x1F, 0xDE, 0x18, 
    0x43, 0x45, 0xF7, 0x12, 0xD9, 0xF0, 0xC7, 0x80, 0xC8, 0x39, 0x02, 0x52, 0xCD, 0xC9, 0x90, 0x9F, 
    0x48, 0x66, 0x99, 0x2D, 0xAE, 0x61, 0xDC, 0x88, 0xD2, 0x2C, 0x84, 0x1D, 0x6A, 0x31, 0x94, 0x35, 
    0x7E, 0xC9, 0x9C, 0x2F, 0x9B, 0xBC, 0xB4, 0x51, 0xD5, 0x01, 0x06, 0x1E, 0x3C, 0xC6, 0xD0, 0x8B, 
    0x7A, 0x24, 0x75, 0x0B, 0x6E, 0x66, 0x09, 0xF5, 0x0B, 0xBA, 0xD6, 0x3F, 0x5A, 0xEC, 0x70, 0xC8, 
    0x56, 0x9E, 0x31, 0x46, 0x5C, 0x39, 0xC4, 0xC5, 0x29, 0xB3, 0x79, 0x77, 0x5A, 0xF2, 0xB1, 0x8E, 
    0x10, 0xA2, 0x5E, 0xD0, 0xD4, 0xE7, 0xB3, 0x0C, 0x22, 0x16, 0xE3, 0x32, 0x92, 0x41, 0x99, 0x5E, 
    0xB0, 0x87, 0x29, 0x56, 0xCD, 0x3B, 0xB5, 0x99, 0xAD, 0xC7, 0xA5, 0xC3, 0xD0, 0x4B, 0x72, 0x09, 
    0xE8, 0xAF, 0x95, 0x89, 0x3B, 0x36, 0x11, 0x8F, 0x1E, 0xB8, 0x67, 0x1C, 0xC8, 0x89, 0x04, 0xDE, 
    0x3C, 0x5D, 0xFD, 0x38, 0xBE, 0x26, 0x42, 0x66, 0xAC, 0x28, 0x6B, 0x99, 0x38, 0x8F, 0x4E, 0xCD, 
    0xBA, 0x52, 0xAF, 0x42, 0xE1, 0x82, 0x3D, 0x62, 0xD5, 0xA8, 0x05, 0x80, 0x73, 0x58, 0x6E, 0x2C, 
    0x07, 0xAE, 0x50, 0x17, 0x83, 0x3F, 0x7C, 0x15, 0xE8, 0x5A, 0xE4, 0x16, 0x26, 0x1C, 0xFC, 0xC3, 
    0xF8, 0x5F, 0x20, 0x93, 0x0C, 0x99, 0x85, 0x9F, 0xF8, 0x82, 0x63, 0xC3, 0x1E, 0x68, 0x79, 0xEB, 
    0x2C, 0x3C, 0x92, 0x3B, 0x16, 0xD9, 0xA2, 0x5A, 0x6C, 0x5C, 0x5F, 0xC1, 0x97, 0xDA, 0xA4, 0x76, 
    0x37, 0x13, 0x92, 0x76, 0xFB, 0x73, 0x89, 0x8F, 0xAF, 0xDB, 0x4A, 0xAF, 0x0F, 0xFB, 0xCE, 0x54, 
    0xCA, 0x31, 0x85, 0xCC, 0x03, 0x4F, 0x9A, 0x5C, 0x71, 0x74, 0xAB, 0x6F, 0xB5, 0x87, 0x3C, 0xC7, 
    0x2C, 0x09, 0x3C, 0x79, 0xB5, 0x76, 0xBB, 0xCA, 0x92, 0x22, 0xD3, 0x9E, 0xDB, 0xEC, 0xAE, 0xE4, 
    0xC4, 0xDD, 0x7F, 0xEE, 0x0A, 0x48, 0xAE, 0xC4, 0x35, 0x6F, 0x99, 0x37, 0x26, 0xCA, 0x6D, 0x1C, 
    0x87, 0x2B, 0x46, 0x6A, 0xE0, 0x42, 0xBA, 0x8E, 0xB9, 0x05, 0x68, 0x3B, 0x58, 0xAA, 0xD5, 0xF7, 
    0xD0, 0xC8, 0xE3, 0x2B, 0xD2, 0x81, 0x8A, 0x7F, 0xBB, 0x89, 0xAD, 0x74, 0x5F, 0xF0, 0xBA, 0x1A, 
    0x73, 0x85, 0x56, 0xA6, 0x8D, 0x34, 0xB6, 0x4C, 0xD5, 0xC7, 0xC7, 0x8E, 0xC3, 0x96, 0xDF, 0xC0, 
    0xF9, 0x70, 0xDD, 0x66, 0x47, 0x66, 0x6D, 0xA1, 0x30, 0x33, 0xE9, 0x67, 0xBC, 0x09, 0x66, 0x58, 
    0x7D, 0x75, 0x70, 0x0C, 0x1A, 0x72, 0x38, 0x53, 0xCC, 0x92, 0x91, 0xAD, 0xE1, 0x96, 0x45, 0x86, 
    0x8B, 0x7C, 0xBB, 0x7B, 0x22, 0x00, 0x3B, 0x06, 0xDA, 0x5C, 0x7B, 0xE5, 0xBD, 0x38, 0xE4, 0x5C, 
    0x38, 0xE0, 0x6B, 0xE0, 0x12, 0x6C, 0x65, 0x43, 0xF2, 0x4E, 0x86, 0x8C, 0xDC, 0xA0, 0x52, 0x75, 
    0xF4, 0x4E, 0x9D, 0x13, 0x83, 0x30, 0xB7, 0xCA, 0xBA, 0x5D, 0x09, 0x76, 0x91, 0xF8, 0x01, 0x43, 
    0x5E, 0x88, 0xDC, 0x0D, 0x50, 0x09, 0x58, 0x50, 0xEA, 0xE4, 0x7C, 0xEA, 0xF3, 0x0A, 0x29, 0x68, 
    0xD3, 0x51, 0xAE, 0x2C, 0xBF, 0x64, 0x1A, 0x83, 0xFC, 0x90, 0xB5, 0xBF, 0xF1, 0xE9, 0x8F, 0x06, 
    0xB3, 0xE8, 0xE2, 0xC2, 0xDD, 0xCA, 0x9C, 0xC7, 0xF6, 0x6C, 0x0F, 0x76, 0x36, 0x95, 0x89, 0x3A, 
    0xC5, 0x36, 0x95, 0xC1, 0xFA, 0x82, 0x78, 0xCD, 0x9A, 0x27, 0xBA, 0xA2, 0x30, 0xBE, 0xBA, 0x9C, 
    0x5A, 0xC2, 0x8A, 0x76, 0x8A, 0xA3, 0xBF, 0xAA, 0xFD, 0x57, 0xA6, 0x94, 0x98, 0x67, 0x9F, 0xFB, 
    0x3B, 0x08, 0xC1, 0xB9, 0x5B, 0xC7, 0x93, 0x81, 0x49, 0x01, 0xB7, 0x2F, 0xBB, 0x9C, 0x63, 0x86, 
    0x79, 0x38, 0x12, 0x0C, 0x60, 0x36, 0xE5, 0xDC, 0x05, 0xD1, 0xB2, 0x79, 0x59, 0xCE, 0x34, 0x39, 
    0x12, 0x2E, 0xB9, 0x4A, 0x72, 0x12, 0x1C, 0x21, 0x93, 0x86, 0xCE, 0x08, 0x3D, 0xE5, 0x37, 0xBB, 
    0xD7, 0xAB, 0x76, 0x7F, 0xB2, 0x7A, 0x7B, 0x2E, 0x81, 0xF2, 0xE8, 0xCF, 0x66, 0xFD, 0x32, 0x7B, 
    0xC0, 0xAE, 0x2C, 0x7A, 0xA4, 0x60, 0xBE, 0xD5, 0x16, 0xC2, 0x98, 0xB6, 0x5F, 0x5D, 0xFD, 0x8E, 
    0x64, 0x3F, 0x37, 0xD8, 0x86, 0xE1, 0x35, 0x2C, 0x3F, 0x9D, 0x8A, 0x43, 0x96, 0xAB, 0xC6, 0xE7, 
    0xCD, 0xE4, 0xEB, 0xF7, 0x09, 0xCA, 0x1E, 0x6A, 0x35, 0x2F, 0x67, 0x5F, 0x6B, 0x6E, 0xF7, 0x64, 
    0xED, 0xDE, 0x5D, 0xF9, 0xC1, 0x8B, 0x57, 0xCD, 0x2F, 0x8D, 0x81, 0x9A, 0x54, 0xD3, 0x94, 0xC0, 
    0xC7, 0x1D, 0x8B, 0x0F, 0x00, 0x77, 0x8E, 0x8C, 0xB9, 0x97, 0xAE, 0xE8, 0x87, 0x74, 0x0F, 0x04, 
    0x63, 0xB8, 0xF9, 0x77, 0x18, 0x10, 0x2B, 0xDE, 0xF0, 0x09, 0x72, 0x08, 0x0E, 0x59, 0x5D, 0xC3, 
    0x06, 0x71, 0xE0, 0x20, 0xAA, 0xF9, 0x03, 0x30, 0xA6, 0x9C, 0xDE, 0x16, 0xEF, 0xCB, 0xE4, 0xAF, 
    0x2E, 0x9A, 0x50, 0x55, 0x91, 0xE0, 0xEC, 0xC2, 0xBC, 0x60, 0x6F, 0xEF, 0x9C, 0xD3, 0xF7, 0x32, 
    0x98, 0x6C, 0xE7, 0xB5, 0x0F, 0x46, 0x1F, 0x13, 0xED, 0xC9, 0x0C, 0x4D, 0x20, 0xB7, 0x01, 0x71, 
    0xE8, 0x9B, 0x6A, 0x1F, 0x0D, 0x02, 0x0E, 0xFC, 0xB4, 0x59, 0x2A, 0x91, 0x88, 0xDD, 0x7A, 0x0B, 
    0x3D, 0xC9, 0x03, 0x73, 0x94, 0x32, 0x2C, 0x63, 0x81, 0xF7, 0xDF, 0xA4, 0xD0, 0x42, 0x91, 0x6E, 
    0x57, 0x09, 0x64, 0xA6, 0xF0, 0x55, 0x7F, 0x48, 0xCA, 0xD6, 0xB7, 0x96, 0x4A, 0xAA, 0x22, 0x41, 
    0xDD, 0x10, 0xB8, 0x24, 0x39, 0x72, 0x11, 0x30, 0x25, 0x06, 0x19, 0xCD, 0xC2, 0xDD, 0x52, 0x37, 
    0xEF, 0x23, 0x44, 0xAC, 0x18, 0xFE, 0x4A, 0xB7, 0xE7, 0x4D, 0x46, 0x5F, 0x7E, 0xD0, 0x4E, 0xEA, 
    0x4F, 0x67, 0xEB, 0xCF, 0x3E, 0x22, 0xF2, 0xCD, 0xE7, 0x94, 0xA2, 0xEC, 0xE8, 0x2F, 0x6F, 0x5A, 
    0x21, 0xB7, 0x43, 0x63, 0xDD, 0xE6, 0x33, 0x59, 0xF0, 0xDB, 0xDC, 0x9C, 0x09, 0x2E, 0x25, 0xA8, 
    0xFC, 0x35, 0x4C, 0xF0, 0xFF, 0xD1, 0xC5, 0xA2, 0x7B, 0x8D, 0xE3, 0x0C, 0xC5, 0xF0, 0x11, 0xD9, 
    0x8F, 0xD3, 0xDF, 0xE5, 0x45, 0x8B, 0xBD, 0x95, 0xAF, 0x2A, 0x19, 0x2B, 0x6D, 0x64, 0xE3, 0xA2 };

unsigned char sc_secret_02_tabl[0x400] = 
{   0x1A, 0x52, 0x1B, 0xDE, 0x7A, 0xDB, 0x8D, 0xDF, 0xF6, 0x07, 0x9F, 0xCC, 0x0F, 0x0B, 0x67, 0x14, 
    0x8C, 0x8F, 0x46, 0x24, 0xFA, 0xE0, 0x2C, 0x2C, 0x7F, 0xF5, 0x71, 0x1C, 0x93, 0x9A, 0xA7, 0x02, 
    0xAB, 0xE2, 0x8F, 0xE7, 0xDA, 0x89, 0x08, 0x27, 0x3D, 0xEF, 0x6E, 0x42, 0x07, 0x95, 0xB3, 0x30, 
    0x87, 0x37, 0x1B, 0x17, 0x50, 0x11, 0x36, 0xEE, 0xBD, 0x00, 0x8B, 0x27, 0x8C, 0xD6, 0xD1, 0x89, 
    0x75, 0xD1, 0x06, 0x61, 0x44, 0x83, 0xBF, 0x64, 0x7A, 0x16, 0xEE, 0x67, 0xFE, 0x81, 0xAB, 0xB5, 
    0xD2, 0x65, 0x10, 0x66, 0xFE, 0x74, 0x9F, 0x19, 0x1A, 0xD4, 0xB1, 0x15, 0x74, 0x00, 0x61, 0x79, 
    0xAE, 0xFA, 0xBA, 0xCF, 0x1C, 0x5F, 0x88, 0x7E, 0xF1, 0x5D, 0xE4, 0xAF, 0xE1, 0xAB, 0x51, 0xF6, 
    0xD6, 0xD0, 0xC0, 0x26, 0x56, 0x0E, 0x34, 0x11, 0x43, 0xFF, 0x51, 0xC4, 0x23, 0x36, 0x3A, 0xAE, 
    0xCE, 0x89, 0x52, 0xE2, 0xD2, 0xB5, 0x9D, 0xF5, 0x0A, 0xFC, 0x17, 0x6F, 0x25, 0xE8, 0x84, 0xD6, 
    0x22, 0x4E, 0x4B, 0x4E, 0x13, 0x6B, 0x3D, 0xB6, 0x73, 0xD2, 0x1C, 0xFC, 0xD1, 0x64, 0xD9, 0xFE, 
    0x97, 0xD7, 0xED, 0x0E, 0x60, 0xEC, 0x47, 0x21, 0x28, 0x86, 0xDE, 0xB9, 0xA6, 0x8D, 0xE1, 0x85, 
    0x23, 0xD3, 0x19, 0xD1, 0xF0, 0x7D, 0x42, 0xAE, 0x26, 0xDD, 0xDF, 0x87, 0x1E, 0x1F, 0xDE, 0x18, 
    0x43, 0x45, 0xF7, 0x12, 0xD9, 0xF0, 0xC7, 0x80, 0xC8, 0x39, 0x02, 0x52, 0xCD, 0xC9, 0x90, 0x9F, 
    0x48, 0x66, 0x99, 0x2D, 0xAE, 0x61, 0xDC, 0x88, 0xD2, 0x2C, 0x84, 0x1D, 0x6A, 0x31, 0x94, 0x35, 
    0x7E, 0xC9, 0x9C, 0x2F, 0x9B, 0xBC, 0xB4, 0x51, 0xD5, 0x01, 0x06, 0x1E, 0x3C, 0xC6, 0xD0, 0x8B, 
    0x7A, 0x24, 0x75, 0x0B, 0x6E, 0x66, 0x09, 0xF5, 0x0B, 0xBA, 0xD6, 0x3F, 0x5A, 0xEC, 0x70, 0xC8, 
    0xC0, 0xF0, 0x41, 0xDD, 0x55, 0xD5, 0x93, 0xAA, 0x10, 0xE0, 0x87, 0xE5, 0x16, 0x04, 0xD0, 0x31, 
    0xFD, 0x80, 0xEC, 0xD8, 0x37, 0x28, 0xAF, 0x59, 0xEE, 0x58, 0xFE, 0x6B, 0x06, 0x5E, 0x88, 0x77, 
    0xA0, 0x81, 0x21, 0xC2, 0xCC, 0x21, 0xE9, 0xB4, 0x8B, 0xD9, 0x42, 0xF4, 0xF6, 0xB4, 0x9F, 0x9F, 
    0xBA, 0xA0, 0x60, 0xF7, 0x6B, 0xFC, 0x1C, 0x23, 0x6D, 0x1B, 0xFE, 0x32, 0x5C, 0x74, 0xA0, 0x71, 
    0x04, 0x54, 0x6D, 0x25, 0x0B, 0x57, 0x7D, 0xC1, 0x21, 0x6C, 0x52, 0xAE, 0x10, 0x46, 0xE0, 0x77, 
    0x15, 0xAD, 0xA1, 0xBE, 0xE1, 0x8F, 0xF9, 0xC5, 0xE4, 0x2F, 0x17, 0xD1, 0x5F, 0xF1, 0x92, 0xAB, 
    0x35, 0xA9, 0x57, 0x90, 0x95, 0x51, 0x43, 0xD0, 0x71, 0x25, 0xA0, 0x4A, 0x6F, 0x79, 0x05, 0xDB, 
    0xD4, 0x08, 0x51, 0x96, 0x2C, 0x5C, 0xF0, 0x50, 0x5F, 0xC0, 0x5C, 0xBF, 0x63, 0x49, 0x94, 0x36, 
    0xE5, 0x4A, 0x0F, 0xC3, 0x29, 0xA5, 0x7C, 0xB0, 0x8D, 0x01, 0xB3, 0x9B, 0x08, 0xF1, 0x10, 0xF4, 
    0x1F, 0xBF, 0x88, 0xC4, 0xE0, 0x31, 0x8C, 0xF8, 0x31, 0x95, 0x61, 0x67, 0x6F, 0x74, 0x1A, 0xBB, 
    0x98, 0x78, 0x53, 0x40, 0xE9, 0x86, 0xD6, 0x98, 0xF0, 0x57, 0x8E, 0xD1, 0xD7, 0x14, 0xBE, 0x1B, 
    0xED, 0xDD, 0x7B, 0xAB, 0x25, 0x65, 0x44, 0xD0, 0xD7, 0x16, 0xDD, 0xA7, 0xFB, 0x3C, 0xC0, 0x19, 
    0x2F, 0x0B, 0xC1, 0x1D, 0xCC, 0xAD, 0x8D, 0x93, 0xD0, 0xA1, 0xC2, 0xF1, 0xA7, 0xA5, 0xFD, 0xD0, 
    0xB6, 0xA6, 0xA7, 0xDF, 0x11, 0x3A, 0x34, 0x4F, 0x29, 0xC1, 0x73, 0x62, 0x67, 0x15, 0x31, 0x89, 
    0xE8, 0xB5, 0xCC, 0xC5, 0xC0, 0x0B, 0xB4, 0x03, 0x65, 0x90, 0xF2, 0x15, 0xFE, 0xB8, 0x04, 0x77, 
    0xC4, 0xB8, 0xA4, 0x36, 0x00, 0x3A, 0xCF, 0xC2, 0xAF, 0xB8, 0x21, 0x4B, 0x5E, 0x12, 0xFA, 0x65, 
    0x5D, 0x88, 0x4E, 0x46, 0xF5, 0x3F, 0x5E, 0xAA, 0x72, 0x48, 0x36, 0x80, 0xE6, 0x8D, 0xC2, 0xBC, 
    0x75, 0x32, 0x46, 0xB2, 0xE4, 0x07, 0x82, 0x95, 0xE9, 0xB4, 0xB1, 0x03, 0xE5, 0xE3, 0x66, 0xED, 
    0xEE, 0x68, 0x0E, 0x1D, 0xE5, 0xD2, 0x9B, 0x75, 0x95, 0xF2, 0x37, 0xA9, 0x0A, 0x2A, 0xA6, 0xC5, 
    0x63, 0x59, 0x68, 0x6A, 0x5C, 0xF0, 0xCB, 0x60, 0xC3, 0xA2, 0x73, 0xE6, 0x15, 0x20, 0xDF, 0x76, 
    0xA9, 0x05, 0xF5, 0xAD, 0x40, 0xD2, 0x14, 0x5B, 0x47, 0xAA, 0x51, 0x71, 0xAE, 0xA6, 0x1E, 0xC7, 
    0x83, 0x57, 0xDE, 0x36, 0x2A, 0x70, 0x70, 0xFF, 0x99, 0xB8, 0x78, 0x1C, 0x6E, 0x25, 0x87, 0xDC, 
    0xF8, 0x28, 0xEB, 0x2A, 0x56, 0x80, 0x32, 0xC3, 0xB4, 0x3E, 0x17, 0x39, 0x94, 0x56, 0x3D, 0x7F, 
    0xEB, 0xD8, 0xD3, 0x5A, 0x64, 0xE5, 0x1B, 0xBB, 0x0E, 0xFF, 0x86, 0x29, 0x75, 0xE7, 0xAA, 0x43, 
    0x0B, 0xF5, 0x16, 0x6A, 0x5E, 0x5D, 0xA8, 0xD8, 0x5E, 0xF2, 0xE7, 0xA5, 0x08, 0x4A, 0x16, 0x69, 
    0x9F, 0xE3, 0x80, 0x9C, 0x8B, 0x13, 0xEE, 0x3A, 0x1F, 0xE8, 0x72, 0x21, 0x84, 0xCC, 0x6E, 0x10, 
    0xA9, 0x38, 0x35, 0x7D, 0xB0, 0x13, 0xF1, 0x60, 0x31, 0x96, 0xFE, 0x9D, 0x38, 0x14, 0xE1, 0xB7, 
    0x18, 0xEB, 0x57, 0x2B, 0x82, 0x9E, 0xAC, 0xC4, 0x77, 0x83, 0x2E, 0x6E, 0x34, 0x48, 0x2E, 0xF9, 
    0x8F, 0xD8, 0x72, 0xB3, 0x3C, 0xCD, 0x39, 0xE3, 0xE9, 0x4B, 0x22, 0x5B, 0xC0, 0x9C, 0xFF, 0x42, 
    0x88, 0x67, 0xF0, 0x5D, 0x78, 0x5E, 0x2D, 0x2F, 0x90, 0xEF, 0x6F, 0xC9, 0x29, 0x12, 0xAE, 0x0C, 
    0x2E, 0x2D, 0x32, 0xC3, 0xA9, 0x91, 0x20, 0xA8, 0xA2, 0x4E, 0xE6, 0x1E, 0x95, 0xD1, 0x88, 0x75, 
    0x61, 0xB8, 0xD8, 0x88, 0x0B, 0xF7, 0x10, 0x78, 0x34, 0x4B, 0x80, 0x28, 0xE2, 0xBB, 0x46, 0xD1, 
    0x35, 0xF6, 0xC6, 0x88, 0x09, 0x3D, 0x73, 0xB7, 0x5B, 0x80, 0x0A, 0x18, 0xE6, 0x3B, 0x2B, 0x22, 
    0xD8, 0x3F, 0xA2, 0x1E, 0x1C, 0x8E, 0x06, 0x81, 0x1C, 0xAA, 0xDB, 0xF5, 0x70, 0xFA, 0x0A, 0xA3, 
    0x5D, 0x64, 0xAC, 0xE7, 0x1D, 0x35, 0x20, 0xF8, 0x87, 0x71, 0x8D, 0x6A, 0x92, 0x5A, 0x6E, 0x46, 
    0xD3, 0xB1, 0x6D, 0xDC, 0xED, 0x0D, 0xE8, 0x7C, 0x91, 0xAC, 0x81, 0x7B, 0x8F, 0xE6, 0x75, 0x37, 
    0x0D, 0x09, 0xE8, 0xB8, 0xF3, 0xF0, 0x65, 0x1B, 0x5F, 0x46, 0x1D, 0x90, 0x1C, 0xB8, 0x77, 0x72, 
    0xD7, 0x92, 0xA4, 0xCD, 0xDC, 0x65, 0x4E, 0x36, 0x1B, 0x51, 0x32, 0xBE, 0x65, 0x9A, 0x3B, 0x79, 
    0x99, 0x5A, 0x1C, 0xB1, 0x80, 0xBF, 0x52, 0xB3, 0x4C, 0x5C, 0xAF, 0x46, 0x6B, 0x78, 0x54, 0x8D, 
    0xC3, 0xD3, 0x92, 0xA3, 0xA8, 0x0D, 0x7D, 0x16, 0x9D, 0x8A, 0x99, 0xA6, 0xA8, 0xDB, 0x17, 0xDA, 
    0x22, 0xF3, 0xF0, 0x57, 0xD7, 0x6C, 0x18, 0x36, 0xB6, 0x0C, 0x94, 0x53, 0x37, 0x6E, 0x5D, 0x81, 
    0x29, 0x0B, 0xC4, 0xD5, 0x45, 0xBF, 0x09, 0xD5, 0x4F, 0xA0, 0xC6, 0x08, 0x65, 0x95, 0xF7, 0xE5, 
    0x79, 0x08, 0xE7, 0x12, 0x68, 0x79, 0x92, 0xD5, 0xF3, 0x5D, 0xDA, 0xF0, 0x21, 0xA8, 0x97, 0x47, 
    0x0F, 0x85, 0x3F, 0x28, 0xA5, 0x16, 0x0A, 0x17, 0xA1, 0x31, 0xDA, 0x07, 0xCE, 0xA7, 0x17, 0x5E, 
    0x7B, 0x3E, 0x94, 0x90, 0x30, 0xCD, 0xF4, 0xFE, 0x61, 0xC1, 0x9E, 0x02, 0x0B, 0xB0, 0xF4, 0x4F, 
    0x02, 0x63, 0x33, 0x9C, 0x7E, 0x05, 0xA0, 0x53, 0xB1, 0x3A, 0x12, 0xBA, 0xF3, 0xA6, 0x0A, 0xAE, 
    0x5C, 0x94, 0xD9, 0x36, 0x0D, 0x24, 0x3B, 0xE1, 0xF4, 0x68, 0x63, 0x18, 0x41, 0x19, 0x54, 0x3D, 
    0x58, 0xEA, 0x73, 0x85, 0xBE, 0xAB, 0xA4, 0x04, 0x6A, 0x51, 0xC5, 0x17, 0xF1, 0x0D, 0xB5, 0xD9 };

unsigned char sc_secret_03_tabl[0x400] = 
{   0x1A, 0x52, 0x1B, 0xDE, 0x7A, 0xDB, 0x8D, 0xDF, 0xF6, 0x07, 0x9F, 0xCC, 0x0F, 0x0B, 0x67, 0x14, 
    0x8C, 0x8F, 0x46, 0x24, 0xFA, 0xE0, 0x2C, 0x2C, 0x7F, 0xF5, 0x71, 0x1C, 0x93, 0x9A, 0xA7, 0x02, 
    0xAB, 0xE2, 0x8F, 0xE7, 0xDA, 0x89, 0x08, 0x27, 0x3D, 0xEF, 0x6E, 0x42, 0x07, 0x95, 0xB3, 0x30, 
    0x87, 0x37, 0x1B, 0x17, 0x50, 0x11, 0x36, 0xEE, 0xBD, 0x00, 0x8B, 0x27, 0x8C, 0xD6, 0xD1, 0x89, 
    0x75, 0xD1, 0x06, 0x61, 0x44, 0x83, 0xBF, 0x64, 0x7A, 0x16, 0xEE, 0x67, 0xFE, 0x81, 0xAB, 0xB5, 
    0xD2, 0x65, 0x10, 0x66, 0xFE, 0x74, 0x9F, 0x19, 0x1A, 0xD4, 0xB1, 0x15, 0x74, 0x00, 0x61, 0x79, 
    0xAE, 0xFA, 0xBA, 0xCF, 0x1C, 0x5F, 0x88, 0x7E, 0xF1, 0x5D, 0xE4, 0xAF, 0xE1, 0xAB, 0x51, 0xF6, 
    0xD6, 0xD0, 0xC0, 0x26, 0x56, 0x0E, 0x34, 0x11, 0x43, 0xFF, 0x51, 0xC4, 0x23, 0x36, 0x3A, 0xAE, 
    0xCE, 0x89, 0x52, 0xE2, 0xD2, 0xB5, 0x9D, 0xF5, 0x0A, 0xFC, 0x17, 0x6F, 0x25, 0xE8, 0x84, 0xD6, 
    0x22, 0x4E, 0x4B, 0x4E, 0x13, 0x6B, 0x3D, 0xB6, 0x73, 0xD2, 0x1C, 0xFC, 0xD1, 0x64, 0xD9, 0xFE, 
    0x97, 0xD7, 0xED, 0x0E, 0x60, 0xEC, 0x47, 0x21, 0x28, 0x86, 0xDE, 0xB9, 0xA6, 0x8D, 0xE1, 0x85, 
    0x23, 0xD3, 0x19, 0xD1, 0xF0, 0x7D, 0x42, 0xAE, 0x26, 0xDD, 0xDF, 0x87, 0x1E, 0x1F, 0xDE, 0x18, 
    0x43, 0x45, 0xF7, 0x12, 0xD9, 0xF0, 0xC7, 0x80, 0xC8, 0x39, 0x02, 0x52, 0xCD, 0xC9, 0x90, 0x9F, 
    0x48, 0x66, 0x99, 0x2D, 0xAE, 0x61, 0xDC, 0x88, 0xD2, 0x2C, 0x84, 0x1D, 0x6A, 0x31, 0x94, 0x35, 
    0x7E, 0xC9, 0x9C, 0x2F, 0x9B, 0xBC, 0xB4, 0x51, 0xD5, 0x01, 0x06, 0x1E, 0x3C, 0xC6, 0xD0, 0x8B, 
    0x7A, 0x24, 0x75, 0x0B, 0x6E, 0x66, 0x09, 0xF5, 0x0B, 0xBA, 0xD6, 0x3F, 0x5A, 0xEC, 0x70, 0xC8, 
    0xF7, 0x7F, 0xAC, 0x20, 0x1C, 0xD1, 0x01, 0x6C, 0xA7, 0x0A, 0x27, 0xB9, 0x13, 0xC8, 0xA5, 0xF3, 
    0x67, 0x6D, 0x41, 0x1E, 0xEE, 0x6F, 0xF1, 0xAA, 0xD5, 0xA0, 0xD4, 0xE9, 0xA9, 0x57, 0x12, 0xC2, 
    0x4E, 0x3E, 0x6F, 0x86, 0x1A, 0xD1, 0xDD, 0xEE, 0x01, 0x66, 0xAB, 0xC1, 0xE3, 0x1D, 0x5F, 0x21, 
    0x42, 0x59, 0x69, 0x68, 0xE1, 0xBC, 0xE6, 0x1A, 0xE2, 0xF3, 0x1B, 0x5B, 0x97, 0xAD, 0x17, 0x5A, 
    0x48, 0x79, 0x56, 0x90, 0x68, 0xEA, 0xB1, 0x06, 0x94, 0xB8, 0x13, 0x66, 0x1B, 0x43, 0x10, 0x37, 
    0x00, 0x78, 0x41, 0x6A, 0xF1, 0x56, 0x3D, 0xDF, 0xF4, 0xC6, 0x4A, 0xDB, 0xEA, 0xC1, 0x15, 0xE1, 
    0xD1, 0x32, 0x77, 0x30, 0xAB, 0x44, 0x8E, 0xB2, 0xCF, 0x05, 0x49, 0x6D, 0x80, 0xF0, 0x95, 0x5E, 
    0x40, 0x0F, 0x59, 0x5A, 0x14, 0xEC, 0x5E, 0xD1, 0x03, 0xD8, 0x42, 0x5A, 0xF8, 0xF3, 0x47, 0xFA, 
    0xDA, 0x7E, 0x7C, 0x66, 0x8E, 0xB2, 0xDE, 0x90, 0x0F, 0x28, 0xE4, 0xEE, 0xD0, 0xAA, 0x2C, 0x2C, 
    0xA6, 0xDE, 0xF2, 0x47, 0x94, 0xDE, 0xA4, 0x43, 0xE0, 0xC2, 0xCC, 0xDB, 0x23, 0xF5, 0x60, 0x27, 
    0x44, 0x91, 0x52, 0x30, 0xE9, 0x3D, 0x96, 0xE0, 0xD2, 0xE5, 0xCD, 0x37, 0x42, 0xAB, 0x47, 0xC2, 
    0x3E, 0x2F, 0x16, 0x09, 0xD0, 0xFC, 0x40, 0x05, 0xA7, 0xBC, 0xB0, 0xB0, 0x60, 0xAB, 0x2F, 0x6E, 
    0x3D, 0xFC, 0x26, 0x75, 0xFB, 0x26, 0xB2, 0x56, 0x73, 0x2E, 0x0B, 0x8D, 0xA5, 0xA7, 0x2C, 0x50, 
    0x7C, 0xD4, 0x8D, 0xB7, 0x87, 0xC1, 0x33, 0xDA, 0xCC, 0x41, 0x5C, 0xC5, 0xF4, 0x0C, 0x12, 0x99, 
    0x1E, 0xB3, 0x7F, 0x91, 0x07, 0xEB, 0xAF, 0x6A, 0x3C, 0xE0, 0x0B, 0x06, 0x5D, 0xED, 0xD4, 0x3D, 
    0x6C, 0x09, 0x36, 0x9A, 0x01, 0xD7, 0x51, 0xB3, 0x64, 0xD1, 0x8F, 0x19, 0xEE, 0xF6, 0x07, 0x14, 
    0x84, 0x99, 0xEB, 0xF2, 0xE0, 0xD8, 0xDD, 0x11, 0xBC, 0xC7, 0x1C, 0x1C, 0xDA, 0xCC, 0x7D, 0x6C, 
    0xBD, 0xAC, 0xCC, 0xEF, 0x76, 0xE6, 0x30, 0xFF, 0x41, 0x90, 0x83, 0x89, 0x7F, 0xE8, 0x56, 0x7F, 
    0x2F, 0x38, 0xCF, 0x1A, 0x58, 0x9C, 0xB5, 0x47, 0xDA, 0xBF, 0x51, 0xC8, 0x6B, 0x25, 0x25, 0x84, 
    0x15, 0x01, 0xAB, 0x0E, 0x29, 0xC8, 0xDC, 0x02, 0xC2, 0x0D, 0x36, 0xE0, 0xE9, 0xA9, 0xFA, 0xC3, 
    0x4F, 0xE3, 0xA6, 0xFE, 0x1C, 0xA2, 0x8C, 0x3D, 0x3E, 0x65, 0xB6, 0xA3, 0x1E, 0xA8, 0x08, 0x01, 
    0x65, 0x28, 0xE4, 0x91, 0x8C, 0x81, 0xEE, 0xED, 0xCE, 0x1F, 0x09, 0xFF, 0xAB, 0xED, 0x39, 0x69, 
    0xFD, 0xBE, 0x66, 0x8F, 0x88, 0x37, 0xAB, 0x9D, 0x83, 0xCE, 0x15, 0xD8, 0x24, 0x90, 0xC2, 0x99, 
    0x26, 0x28, 0xB9, 0x6B, 0xDB, 0x58, 0x3E, 0x50, 0xAD, 0x32, 0x18, 0xD8, 0x2C, 0xD3, 0xCC, 0x15, 
    0x66, 0xE7, 0x15, 0xA6, 0xEC, 0x2A, 0xA9, 0x8C, 0xBA, 0x4A, 0x5E, 0x95, 0xBB, 0xE6, 0x15, 0xC9, 
    0x10, 0x5C, 0xDD, 0x27, 0xF8, 0x78, 0xD7, 0xB4, 0x9D, 0x05, 0x1A, 0xA8, 0xEF, 0xCB, 0x79, 0x8F, 
    0x1C, 0x89, 0x0B, 0x93, 0x7A, 0x29, 0xBA, 0x45, 0xDB, 0x04, 0x41, 0x5C, 0xD0, 0xB1, 0x9C, 0xDF, 
    0x0F, 0x91, 0x22, 0x6A, 0xC2, 0xE6, 0x11, 0x78, 0x97, 0x97, 0xCC, 0x50, 0x68, 0x5A, 0x38, 0xEB, 
    0xBC, 0xEF, 0xA5, 0x67, 0x72, 0x13, 0x27, 0x03, 0x81, 0x3C, 0x3D, 0x26, 0x0C, 0x78, 0x14, 0xAA, 
    0xB6, 0x39, 0x48, 0x30, 0xC3, 0x5B, 0xA3, 0x8F, 0xEF, 0x8C, 0xB3, 0x47, 0xB6, 0xF7, 0x9D, 0x42, 
    0x31, 0x2C, 0x42, 0x41, 0xE2, 0x17, 0x6A, 0x52, 0x7F, 0x4C, 0x84, 0x06, 0xB2, 0xDA, 0x34, 0xBE, 
    0x7B, 0x75, 0x95, 0xB7, 0x04, 0xB5, 0xBC, 0x66, 0x00, 0x8B, 0xA8, 0x3E, 0x1E, 0x90, 0xF9, 0x90, 
    0x6E, 0xF6, 0xAD, 0x82, 0xDC, 0x42, 0xCF, 0x7A, 0x68, 0x73, 0xF8, 0xE9, 0xDA, 0x75, 0xB6, 0xBD, 
    0xA5, 0x49, 0xE9, 0x8B, 0x2E, 0xB1, 0xB4, 0x45, 0xB7, 0x05, 0xA8, 0xF6, 0x42, 0x07, 0xDC, 0x79, 
    0x9F, 0xFA, 0x81, 0xD2, 0xEB, 0x3C, 0x76, 0xE9, 0x56, 0x47, 0xCB, 0x33, 0x4B, 0x12, 0xDB, 0x8C, 
    0xF2, 0x5F, 0x0E, 0x17, 0x7F, 0x17, 0xAE, 0xA3, 0xD1, 0x05, 0x64, 0x89, 0x7D, 0x00, 0x3A, 0x29, 
    0xC3, 0x42, 0xC5, 0x1F, 0x4F, 0x10, 0x45, 0xBD, 0x1E, 0x86, 0x18, 0x2F, 0x64, 0x52, 0xF9, 0x14, 
    0x0F, 0xCE, 0xC5, 0xAE, 0x6F, 0xB2, 0x36, 0xA7, 0xF7, 0x3D, 0xD0, 0x63, 0x4E, 0x1F, 0xB4, 0xC8, 
    0xAC, 0x8E, 0x0A, 0xD5, 0x05, 0x58, 0x13, 0xEF, 0x43, 0xF2, 0x9C, 0xF6, 0xFE, 0x94, 0xB2, 0x5D, 
    0x97, 0x06, 0x03, 0xB0, 0x39, 0xB0, 0x7D, 0xFC, 0xC8, 0xCE, 0x7E, 0xC9, 0x01, 0x0F, 0xAA, 0x21, 
    0xCE, 0xA1, 0x5F, 0x68, 0xE5, 0x24, 0xAD, 0x5D, 0x52, 0x78, 0x71, 0x11, 0x33, 0xE6, 0x14, 0x4E, 
    0xC3, 0xDE, 0x77, 0x9A, 0x17, 0xFA, 0x4D, 0x4F, 0x33, 0xF9, 0x19, 0x90, 0x0B, 0x89, 0x6B, 0x3B, 
    0x14, 0x9C, 0x6D, 0x60, 0xB2, 0xC6, 0x3A, 0x73, 0xBE, 0x2C, 0xA1, 0x32, 0x7A, 0x50, 0x12, 0x77, 
    0x3C, 0x64, 0xF5, 0x2B, 0x45, 0xAD, 0xF5, 0x58, 0x26, 0xBD, 0x18, 0x36, 0xF5, 0x5D, 0x0C, 0x38, 
    0xC9, 0x0E, 0xDF, 0x82, 0x51, 0x92, 0x6D, 0xC6, 0x4D, 0x82, 0x24, 0x2B, 0x5B, 0x47, 0xF9, 0x60, 
    0x8D, 0xDF, 0xD2, 0x24, 0x2F, 0x4C, 0x44, 0xB6, 0x53, 0x06, 0xCE, 0x99, 0xF9, 0x3B, 0x27, 0xA9, 
    0x9D, 0x93, 0xB1, 0x92, 0x34, 0x5D, 0xEE, 0xA1, 0x35, 0x2E, 0x64, 0xC3, 0x1A, 0x28, 0x7B, 0x9D, 
    0x3C, 0x48, 0xFB, 0x02, 0xE6, 0x5E, 0x40, 0x02, 0x57, 0x72, 0xF9, 0x58, 0xCF, 0x16, 0x6B, 0x5F };


unsigned char sc_secret_GO_tabl[0x400] = 
{   0x1A, 0x52, 0x1B, 0xDE, 0x7A, 0xDB, 0x8D, 0xDF, 0xF6, 0x07, 0x9F, 0xCC, 0x0F, 0x0B, 0x67, 0x14, 
    0x8C, 0x8F, 0x46, 0x24, 0xFA, 0xE0, 0x2C, 0x2C, 0x7F, 0xF5, 0x71, 0x1C, 0x93, 0x9A, 0xA7, 0x02, 
    0xAB, 0xE2, 0x8F, 0xE7, 0xDA, 0x89, 0x08, 0x27, 0x3D, 0xEF, 0x6E, 0x42, 0x07, 0x95, 0xB3, 0x30, 
    0x87, 0x37, 0x1B, 0x17, 0x50, 0x11, 0x36, 0xEE, 0xBD, 0x00, 0x8B, 0x27, 0x8C, 0xD6, 0xD1, 0x89, 
    0x75, 0xD1, 0x06, 0x61, 0x44, 0x83, 0xBF, 0x64, 0x7A, 0x16, 0xEE, 0x67, 0xFE, 0x81, 0xAB, 0xB5, 
    0xD2, 0x65, 0x10, 0x66, 0xFE, 0x74, 0x9F, 0x19, 0x1A, 0xD4, 0xB1, 0x15, 0x74, 0x00, 0x61, 0x79, 
    0xAE, 0xFA, 0xBA, 0xCF, 0x1C, 0x5F, 0x88, 0x7E, 0xF1, 0x5D, 0xE4, 0xAF, 0xE1, 0xAB, 0x51, 0xF6, 
    0xD6, 0xD0, 0xC0, 0x26, 0x56, 0x0E, 0x34, 0x11, 0x43, 0xFF, 0x51, 0xC4, 0x23, 0x36, 0x3A, 0xAE, 
    0xCE, 0x89, 0x52, 0xE2, 0xD2, 0xB5, 0x9D, 0xF5, 0x0A, 0xFC, 0x17, 0x6F, 0x25, 0xE8, 0x84, 0xD6, 
    0x22, 0x4E, 0x4B, 0x4E, 0x13, 0x6B, 0x3D, 0xB6, 0x73, 0xD2, 0x1C, 0xFC, 0xD1, 0x64, 0xD9, 0xFE, 
    0x97, 0xD7, 0xED, 0x0E, 0x60, 0xEC, 0x47, 0x21, 0x28, 0x86, 0xDE, 0xB9, 0xA6, 0x8D, 0xE1, 0x85, 
    0x23, 0xD3, 0x19, 0xD1, 0xF0, 0x7D, 0x42, 0xAE, 0x26, 0xDD, 0xDF, 0x87, 0x1E, 0x1F, 0xDE, 0x18, 
    0x43, 0x45, 0xF7, 0x12, 0xD9, 0xF0, 0xC7, 0x80, 0xC8, 0x39, 0x02, 0x52, 0xCD, 0xC9, 0x90, 0x9F, 
    0x48, 0x66, 0x99, 0x2D, 0xAE, 0x61, 0xDC, 0x88, 0xD2, 0x2C, 0x84, 0x1D, 0x6A, 0x31, 0x94, 0x35, 
    0x7E, 0xC9, 0x9C, 0x2F, 0x9B, 0xBC, 0xB4, 0x51, 0xD5, 0x01, 0x06, 0x1E, 0x3C, 0xC6, 0xD0, 0x8B, 
    0x7A, 0x24, 0x75, 0x0B, 0x6E, 0x66, 0x09, 0xF5, 0x0B, 0xBA, 0xD6, 0x3F, 0x5A, 0xEC, 0x70, 0xC8, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x65, 0xBE, 0xF7, 0xFF, 0x94, 0x7B, 0xF9, 0xE5, 0x4C, 0x5A, 0x0A, 0xDF, 0xB3, 0x2A, 0xFB, 0x47, 
    0xB4, 0x6A, 0x54, 0x70, 0x94, 0x5F, 0xCA, 0x9E, 0xF4, 0xCF, 0x6E, 0x85, 0xF3, 0x48, 0xDC, 0x2E, 
    0xC5, 0x7F, 0x8B, 0x02, 0xD2, 0x63, 0x29, 0xB5, 0x87, 0xF2, 0xE8, 0xDC, 0x5C, 0x8A, 0x75, 0xC8, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


unsigned char *tablemap[8] =
{   0,
    sc_secret_01_tabl,
    sc_secret_02_tabl,
    sc_secret_03_tabl,
    sc_secret_GO_tabl,
    sc_secret_03_tabl,
    sc_secret_03_tabl,
    sc_secret_03_tabl};

int modelmap[13] = 
{   0, // 00g -hah
    0, // 01g
    1, // 02g
    2, // 03g
    3, // 04g
    4, // 05g -GO
    0, // 06g - doesn't exist
    5, // 07g
    0, // 08g - doesn't exist
    6, // 09g
    0, // 10g - doesn't exist
    7, // 11g
    0, // 12g - doesn't exist
    };




unsigned char ipl02_1[0x18] = { 0x61, 0x7A, 0x56, 0x42, 0xF8, 0xED, 0xC5, 0xE4, 0xDB, 0xB1, 0x1E, 0x20, 0x48, 0x83, 0xB1, 0x6F, 0x04, 0xF4, 0x69, 0x8A, 0x8C, 0xAA, 0x95, 0x30};

unsigned char ipl04_1[0x18] = { 0x8D, 0x5D, 0xA6, 0x08, 0xF2, 0xBB, 0xC6, 0xCC, 0x34, 0xDB, 0x81, 0x24, 0x1D, 0x6F, 0x40, 0x57, 0xE0, 0xDC, 0x41, 0xAF, 0xC2, 0xCD, 0x1C, 0x2D};

unsigned char iplXX_1[0x18] = { 0x79, 0x7B, 0xF6, 0xF3, 0xE3, 0x3B, 0x37, 0x56, 0xE0, 0xE8, 0x6A, 0xDA, 0x60, 0x95, 0x3A, 0x0F, 0xDC, 0xBF, 0x3C, 0xEB, 0x9D, 0xD4, 0x41, 0x4E};

unsigned char  sc_key[0x10] = { 0xF1, 0x07, 0x30, 0xC3, 0x11, 0xE0, 0x26, 0xFC, 0xF8, 0x7B, 0x50, 0xAE, 0xA3, 0xD1, 0x7B, 0xA0 };




int getSysconIndex(unsigned char * data) {
    AES_ctx scindexkey;
    unsigned char result[0x10];
    AES_set_key(&scindexkey,sc_key,128);
    AES_decrypt(&scindexkey,data,result);
    return result[8]&0x3F;
        
}

void getSysconIPLKey(int type, unsigned char * indata, unsigned char * outdata) {
    int index = getSysconIndex(indata);
    unsigned char * table;
    if(type <13) {
        table = tablemap[modelmap[type]];
    } else {
        memset(outdata,0,0x10);
        return;
    }
        
    if (table) {
        memcpy(outdata,&table[index*0x10],0x10);    
    } else {
        memset(outdata,0,0x10);
    }        
    return;
}


int findStage2Keys(unsigned char * stage2, int length) {
    int i;
    for(i=0;i<length-0x18;i++) {
        if((memcmp(&stage2[i],ipl02_1,0x18) == 0) ||
            (memcmp(&stage2[i],ipl04_1,0x18) == 0) ||
            (memcmp(&stage2[i],iplXX_1,0x18) == 0))
            return i +0x18;
    }
    return -1;
}
