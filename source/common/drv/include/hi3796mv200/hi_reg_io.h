//******************************************************************************
// Copyright     :  Copyright (C) 2016, Hisilicon Technologies Co. Ltd.
// File name     :  hi_reg_io.h
// Author        :
// Version       :  1
// Date          :  2016/9/24
// Description   :  The description of xxx project
// Others        :  Generated automatically by nManager V4.1
//******************************************************************************

#ifndef __HI_REG_IO_H__
#define __HI_REG_IO_H__

/* Define the union U_ioshare_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_0             : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    ioctrl_0_DS           : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_0_SR           : 1   ; /* [8]  */
        unsigned int    reserved_2            : 4   ; /* [12..9]  */
        unsigned int    ioctrl_0_OPD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_0;

/* Define the union U_ioshare_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_1             : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    ioctrl_1_DS1          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_1_SR           : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_1_PU           : 1   ; /* [12]  */
        unsigned int    ioctrl_1_PD           : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_1;

/* Define the union U_ioshare_2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_2             : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    ioctrl_2_DS           : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_2_SR           : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_2_OPU          : 1   ; /* [12]  */
        unsigned int    reserved_3            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_2;

/* Define the union U_ioshare_3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_3             : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    ioctrl_3_DS           : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_3_SR           : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_3_OPU          : 1   ; /* [12]  */
        unsigned int    reserved_3            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_3;

/* Define the union U_ioshare_4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_4             : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    ioctrl_4_DS           : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_4_SR           : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_4_PU           : 1   ; /* [12]  */
        unsigned int    ioctrl_4_PD           : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_4;

/* Define the union U_ioshare_5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_5             : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    ioctrl_5_DS           : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_5_SR           : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_5_PU           : 1   ; /* [12]  */
        unsigned int    ioctrl_5_PD           : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_5;

/* Define the union U_ioshare_6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_6             : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    ioctrl_6_DS           : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_6_SR           : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_6_OPU          : 1   ; /* [12]  */
        unsigned int    reserved_3            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_6;

/* Define the union U_ioshare_7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_7             : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    ioctrl_7_DS           : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_7_SR           : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_7_OPU          : 1   ; /* [12]  */
        unsigned int    reserved_3            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_7;

/* Define the union U_ioshare_8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_8             : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    ioctrl_8_DS           : 4   ; /* [7..4]  */
        unsigned int    ioctrl_8_SR           : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_8_PU           : 1   ; /* [12]  */
        unsigned int    ioctrl_8_PD           : 1   ; /* [13]  */
        unsigned int    reserved_2            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_8;

/* Define the union U_ioshare_9 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_9             : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    ioctrl_9_DS           : 4   ; /* [7..4]  */
        unsigned int    ioctrl_9_SR           : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_9_PU           : 1   ; /* [12]  */
        unsigned int    ioctrl_9_PD           : 1   ; /* [13]  */
        unsigned int    reserved_2            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_9;

/* Define the union U_ioshare_10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_10            : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    ioctrl_10_DS          : 4   ; /* [7..4]  */
        unsigned int    ioctrl_10_SR          : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_10_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_10_PD          : 1   ; /* [13]  */
        unsigned int    reserved_2            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_10;

/* Define the union U_ioshare_11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_11            : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    ioctrl_11_DS          : 4   ; /* [7..4]  */
        unsigned int    ioctrl_11_SR          : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_11_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_11_PD          : 1   ; /* [13]  */
        unsigned int    reserved_2            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_11;

/* Define the union U_ioshare_12 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_12            : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    ioctrl_12_DS          : 4   ; /* [7..4]  */
        unsigned int    ioctrl_12_SR          : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_12_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_12_PD          : 1   ; /* [13]  */
        unsigned int    reserved_2            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_12;

/* Define the union U_ioshare_13 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_13            : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    ioctrl_13_DS          : 4   ; /* [7..4]  */
        unsigned int    ioctrl_13_SR          : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_13_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_13_PD          : 1   ; /* [13]  */
        unsigned int    reserved_2            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_13;

/* Define the union U_ioshare_14 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_14            : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    ioctrl_14_DS          : 4   ; /* [7..4]  */
        unsigned int    ioctrl_14_SR          : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_14_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_14_PD          : 1   ; /* [13]  */
        unsigned int    reserved_2            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_14;

/* Define the union U_ioshare_15 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_15            : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    ioctrl_15_DS          : 4   ; /* [7..4]  */
        unsigned int    ioctrl_15_SR          : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_15_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_15_PD          : 1   ; /* [13]  */
        unsigned int    reserved_2            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_15;

/* Define the union U_ioshare_16 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_16            : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    ioctrl_16_DS          : 4   ; /* [7..4]  */
        unsigned int    ioctrl_16_SR          : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_16_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_16_PD          : 1   ; /* [13]  */
        unsigned int    reserved_2            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_16;

/* Define the union U_ioshare_17 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_17            : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    ioctrl_17_DS          : 4   ; /* [7..4]  */
        unsigned int    ioctrl_17_SR          : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_17_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_17_PD          : 1   ; /* [13]  */
        unsigned int    reserved_2            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_17;

/* Define the union U_ioshare_18 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_18            : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    ioctrl_18_DS          : 4   ; /* [7..4]  */
        unsigned int    ioctrl_18_SR          : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_18_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_18_PD          : 1   ; /* [13]  */
        unsigned int    reserved_2            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_18;

/* Define the union U_ioshare_19 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_19            : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    ioctrl_19_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_19_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_19_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_19_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_19;

/* Define the union U_ioshare_20 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_20            : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    ioctrl_20_DS          : 4   ; /* [7..4]  */
        unsigned int    ioctrl_20_SR          : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_20_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_20_PD          : 1   ; /* [13]  */
        unsigned int    reserved_2            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_20;

/* Define the union U_ioshare_21 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_21            : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    ioctrl_21_DS          : 4   ; /* [7..4]  */
        unsigned int    ioctrl_21_SR          : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_21_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_21_PD          : 1   ; /* [13]  */
        unsigned int    reserved_2            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_21;

/* Define the union U_ioshare_22 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_22            : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    ioctrl_22_DS          : 4   ; /* [7..4]  */
        unsigned int    ioctrl_22_SR          : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_22_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_22_PD          : 1   ; /* [13]  */
        unsigned int    reserved_2            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_22;

/* Define the union U_ioshare_23 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_23            : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    ioctrl_23_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_23_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_23_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_23_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_23;

/* Define the union U_ioshare_24 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_24            : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    ioctrl_24_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_24_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_24_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_24_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_24;

/* Define the union U_ioshare_25 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_25            : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    ioctrl_25_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_25_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_25_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_25_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_25;

/* Define the union U_ioshare_26 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_26            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_26_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_26_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_26_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_26_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_26;

/* Define the union U_ioshare_27 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_27            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_27_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_27_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_27_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_27_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_27;

/* Define the union U_ioshare_28 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_28            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_28_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_28_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_28_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_28_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_28;

/* Define the union U_ioshare_31 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_31            : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    ioctrl_31_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_31;

/* Define the union U_ioshare_32 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_32            : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    ioctrl_32_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_32;

/* Define the union U_ioshare_33 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_33            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_33_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_33_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_33_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_33_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_33;

/* Define the union U_ioshare_34 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_34            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_34_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_34_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_34_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_34_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_34;

/* Define the union U_ioshare_35 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_35            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_35_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_35_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_35_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_35_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_35;

/* Define the union U_ioshare_36 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_36            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_36_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_36_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_36_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_36_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_36;

/* Define the union U_ioshare_37 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_37            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_37_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_37_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_37_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_37_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_37;

/* Define the union U_ioshare_38 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_38            : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    ioctrl_38_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_38_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_38_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_38_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_38;

/* Define the union U_ioshare_39 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_39            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_39_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_39_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_39_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_39_PD          : 1   ; /* [13]  */
        unsigned int    ioctrl_39_SMT         : 1   ; /* [14]  */
        unsigned int    reserved_3            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_39;

/* Define the union U_ioshare_40 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_40            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_40_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_40_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_40_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_40_PD          : 1   ; /* [13]  */
        unsigned int    ioctrl_40_SMT         : 1   ; /* [14]  */
        unsigned int    reserved_3            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_40;

/* Define the union U_ioshare_41 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_41            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_41_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_41_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_41_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_41_PD          : 1   ; /* [13]  */
        unsigned int    ioctrl_41_SMT         : 1   ; /* [14]  */
        unsigned int    reserved_3            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_41;

/* Define the union U_ioshare_42 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_42            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_42_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_42_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_42_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_42_PD          : 1   ; /* [13]  */
        unsigned int    ioctrl_42_SMT         : 1   ; /* [14]  */
        unsigned int    reserved_3            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_42;

/* Define the union U_ioshare_43 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_43            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_43_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_43_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_43_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_43_PD          : 1   ; /* [13]  */
        unsigned int    ioctrl_43_SMT         : 1   ; /* [14]  */
        unsigned int    reserved_3            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_43;

/* Define the union U_ioshare_44 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_44            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_44_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_44_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_44_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_44_PD          : 1   ; /* [13]  */
        unsigned int    ioctrl_44_SMT         : 1   ; /* [14]  */
        unsigned int    reserved_3            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_44;

/* Define the union U_ioshare_45 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_45            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_45_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_45_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_45_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_45_PD          : 1   ; /* [13]  */
        unsigned int    ioctrl_45_SMT         : 1   ; /* [14]  */
        unsigned int    reserved_3            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_45;

/* Define the union U_ioshare_46 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_46            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_46_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_46_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_46_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_46_PD          : 1   ; /* [13]  */
        unsigned int    ioctrl_46_SMT         : 1   ; /* [14]  */
        unsigned int    reserved_3            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_46;

/* Define the union U_ioshare_47 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_47            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_47_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_47_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_47_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_47_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_47;

/* Define the union U_ioshare_48 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_48            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_48_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_48_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_48_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_48_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_48;

/* Define the union U_ioshare_49 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_49            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_49_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_49_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_49_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_49_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_49;

/* Define the union U_ioshare_50 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_50            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_50_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_50_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_50_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_50_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_50;

/* Define the union U_ioshare_51 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_51            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_51_DS          : 4   ; /* [7..4]  */
        unsigned int    ioctrl_51_SR          : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_51_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_51_PD          : 1   ; /* [13]  */
        unsigned int    reserved_2            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_51;

/* Define the union U_ioshare_52 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_52            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_52_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_52_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_52_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_52_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_52;

/* Define the union U_ioshare_53 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_53            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_53_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_53_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_53_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_53_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_53;

/* Define the union U_ioshare_54 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_54            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_54_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_54_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_54_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_54_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_54;

/* Define the union U_ioshare_55 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_55            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_55_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_55_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_55_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_55_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_55;

/* Define the union U_ioshare_56 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_56            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_56_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_56_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_56_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_56_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_56;

/* Define the union U_ioshare_57 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_57            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_57_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_57_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_57_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_57_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_57;

/* Define the union U_ioshare_58 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_58            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_58_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_58_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_58_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_58_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_58;

/* Define the union U_ioshare_59 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_59            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_59_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_59_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_59_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_59_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_59;

/* Define the union U_ioshare_60 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_60            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_60_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_60_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_60_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_60_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_60;

/* Define the union U_ioshare_61 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_61            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_61_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_61_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_61_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_61_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_61;

/* Define the union U_ioshare_62 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_62            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_62_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_62_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_62_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_62_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_62;

/* Define the union U_ioshare_63 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_63            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_63_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_63_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_63_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_63_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_63;

/* Define the union U_ioshare_64 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_64            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_64_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_64_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_64_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_64_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_64;

/* Define the union U_ioshare_65 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_65            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_65_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_65_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_65_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_65_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_65;

/* Define the union U_ioshare_66 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_66            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_66_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_66_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_66_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_66_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_66;

/* Define the union U_ioshare_67 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_67            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_67_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_67_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_67_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_67_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_67;

/* Define the union U_ioshare_68 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_68            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_68_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_68_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_68_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_68_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_68;

/* Define the union U_ioshare_69 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_69            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_69_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_69_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_69_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_69_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_69;

/* Define the union U_ioshare_70 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_70            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_70_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_70_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_70_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_70_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_70;

/* Define the union U_ioshare_71 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_71            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_71_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_71_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_71_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_71_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_71;

/* Define the union U_ioshare_72 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_72            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_72_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_72_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_72_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_72_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_72;

/* Define the union U_ioshare_73 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_73            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_73_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_73_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_73_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_73_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_73;

/* Define the union U_ioshare_74 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_74            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_74_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_74_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_74_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_74_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_74;

/* Define the union U_ioshare_75 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_75            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_75_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_75_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_75_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_75_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_75;

/* Define the union U_ioshare_76 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_76            : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    ioctrl_76_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_76_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_76_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_76_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_76;

/* Define the union U_ioshare_77 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_77            : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    ioctrl_77_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_77_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_77_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_77_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_77;

/* Define the union U_ioshare_82 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_82            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_82_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_82_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_82_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_82_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_82;

/* Define the union U_ioshare_83 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_83            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_83_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_83_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_83_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_83_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_83;

/* Define the union U_ioshare_84 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_84            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_84_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_84_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_84_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_84_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_84;

/* Define the union U_ioshare_85 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_85            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_85_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_85_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_85_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_85_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_85;

/* Define the union U_ioshare_86 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_86            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_86_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_86_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_86_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_86_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_86;

/* Define the union U_ioshare_87 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_87            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_87_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_87_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_87_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_87_PD          : 1   ; /* [13]  */
        unsigned int    ioctrl_87_SMT         : 1   ; /* [14]  */
        unsigned int    reserved_3            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_87;

/* Define the union U_ioshare_88 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_88            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_88_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_88_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_88_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_88_PD          : 1   ; /* [13]  */
        unsigned int    ioctrl_88_SMT         : 1   ; /* [14]  */
        unsigned int    reserved_3            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_88;

/* Define the union U_ioshare_89 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_89            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_89_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_89_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_89_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_89_PD          : 1   ; /* [13]  */
        unsigned int    ioctrl_89_SMT         : 1   ; /* [14]  */
        unsigned int    reserved_3            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_89;

/* Define the union U_ioshare_90 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_90            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_90_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_90_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_90_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_90_PD          : 1   ; /* [13]  */
        unsigned int    ioctrl_90_SMT         : 1   ; /* [14]  */
        unsigned int    reserved_3            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_90;

/* Define the union U_ioshare_91 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_91            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_91_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_91_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_91_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_91_PD          : 1   ; /* [13]  */
        unsigned int    ioctrl_91_SMT         : 1   ; /* [14]  */
        unsigned int    reserved_3            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_91;

/* Define the union U_ioshare_92 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_92            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_92_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_92_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_92_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_92_PD          : 1   ; /* [13]  */
        unsigned int    ioctrl_92_SMT         : 1   ; /* [14]  */
        unsigned int    reserved_3            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_92;

/* Define the union U_ioshare_93 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_93            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_93_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_93_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_93_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_93_PD          : 1   ; /* [13]  */
        unsigned int    ioctrl_93_SMT         : 1   ; /* [14]  */
        unsigned int    reserved_3            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_93;

/* Define the union U_ioshare_94 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_94            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_94_DS          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_94_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_94_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_94_PD          : 1   ; /* [13]  */
        unsigned int    ioctrl_94_SMT         : 1   ; /* [14]  */
        unsigned int    reserved_3            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_94;

/* Define the union U_ioshare_95 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_95            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_95_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_95_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_95_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_95_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_95;

/* Define the union U_ioshare_96 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_96            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_96_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_96_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_96_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_96_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_96;

/* Define the union U_ioshare_97 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_97            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_97_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_97_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_97_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_97_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_97;

/* Define the union U_ioshare_98 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_98            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_98_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_98_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_98_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_98_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_98;

/* Define the union U_ioshare_99 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_99            : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    ioctrl_99_DS          : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_99_SR          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_99_PU          : 1   ; /* [12]  */
        unsigned int    ioctrl_99_PD          : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_99;

/* Define the union U_ioshare_100 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    ioctrl_100_DS         : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_100_SR         : 1   ; /* [8]  */
        unsigned int    reserved_2            : 4   ; /* [12..9]  */
        unsigned int    ioctrl_100_OPD        : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_100;

/* Define the union U_ioshare_101 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    ioctrl_101_DS         : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_101_SR         : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_101_PU         : 1   ; /* [12]  */
        unsigned int    ioctrl_101_PD         : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_101;

/* Define the union U_ioshare_102 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    ioctrl_102_DS         : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_102_SR         : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_102_PU         : 1   ; /* [12]  */
        unsigned int    ioctrl_102_PD         : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_102;

/* Define the union U_ioshare_103 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    ioctrl_103_DS         : 4   ; /* [7..4]  */
        unsigned int    ioctrl_103_SR         : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_103_PU         : 1   ; /* [12]  */
        unsigned int    ioctrl_103_PD         : 1   ; /* [13]  */
        unsigned int    reserved_2            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_103;

/* Define the union U_ioshare_104 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    ioctrl_104_DS         : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_104_SR         : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_104_PU         : 1   ; /* [12]  */
        unsigned int    ioctrl_104_PD         : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_104;

/* Define the union U_ioshare_105 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    ioctrl_105_DS         : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_105_SR         : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_105_PU         : 1   ; /* [12]  */
        unsigned int    ioctrl_105_PD         : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_105;

/* Define the union U_ioshare_106 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    ioctrl_106_DS         : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ioctrl_106_SR         : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_106_PU         : 1   ; /* [12]  */
        unsigned int    ioctrl_106_PD         : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_106;

/* Define the union U_ioshare_107 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    ioctrl_107_DS         : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    ioctrl_107_SR         : 1   ; /* [8]  */
        unsigned int    reserved_2            : 3   ; /* [11..9]  */
        unsigned int    ioctrl_107_PU         : 1   ; /* [12]  */
        unsigned int    ioctrl_107_PD         : 1   ; /* [13]  */
        unsigned int    reserved_3            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_107;

/* Define the union U_ioshare_108 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ioshare_108           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_ioshare_108;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_ioshare_0            ioshare_0                         ; /* 0x0 */
    volatile U_ioshare_1            ioshare_1                         ; /* 0x4 */
    volatile U_ioshare_2            ioshare_2                         ; /* 0x8 */
    volatile U_ioshare_3            ioshare_3                         ; /* 0xc */
    volatile U_ioshare_4            ioshare_4                         ; /* 0x10 */
    volatile U_ioshare_5            ioshare_5                         ; /* 0x14 */
    volatile U_ioshare_6            ioshare_6                         ; /* 0x18 */
    volatile U_ioshare_7            ioshare_7                         ; /* 0x1c */
    volatile U_ioshare_8            ioshare_8                         ; /* 0x20 */
    volatile U_ioshare_9            ioshare_9                         ; /* 0x24 */
    volatile U_ioshare_10           ioshare_10                        ; /* 0x28 */
    volatile U_ioshare_11           ioshare_11                        ; /* 0x2c */
    volatile U_ioshare_12           ioshare_12                        ; /* 0x30 */
    volatile U_ioshare_13           ioshare_13                        ; /* 0x34 */
    volatile U_ioshare_14           ioshare_14                        ; /* 0x38 */
    volatile U_ioshare_15           ioshare_15                        ; /* 0x3c */
    volatile U_ioshare_16           ioshare_16                        ; /* 0x40 */
    volatile U_ioshare_17           ioshare_17                        ; /* 0x44 */
    volatile U_ioshare_18           ioshare_18                        ; /* 0x48 */
    volatile U_ioshare_19           ioshare_19                        ; /* 0x4c */
    volatile U_ioshare_20           ioshare_20                        ; /* 0x50 */
    volatile U_ioshare_21           ioshare_21                        ; /* 0x54 */
    volatile U_ioshare_22           ioshare_22                        ; /* 0x58 */
    volatile U_ioshare_23           ioshare_23                        ; /* 0x5c */
    volatile U_ioshare_24           ioshare_24                        ; /* 0x60 */
    volatile U_ioshare_25           ioshare_25                        ; /* 0x64 */
    volatile U_ioshare_26           ioshare_26                        ; /* 0x68 */
    volatile U_ioshare_27           ioshare_27                        ; /* 0x6c */
    volatile U_ioshare_28           ioshare_28                        ; /* 0x70 */
    volatile unsigned int           reserved_0[2]                     ; /* 0x74~0x78 */
    volatile U_ioshare_31           ioshare_31                        ; /* 0x7c */
    volatile U_ioshare_32           ioshare_32                        ; /* 0x80 */
    volatile U_ioshare_33           ioshare_33                        ; /* 0x84 */
    volatile U_ioshare_34           ioshare_34                        ; /* 0x88 */
    volatile U_ioshare_35           ioshare_35                        ; /* 0x8c */
    volatile U_ioshare_36           ioshare_36                        ; /* 0x90 */
    volatile U_ioshare_37           ioshare_37                        ; /* 0x94 */
    volatile U_ioshare_38           ioshare_38                        ; /* 0x98 */
    volatile U_ioshare_39           ioshare_39                        ; /* 0x9c */
    volatile U_ioshare_40           ioshare_40                        ; /* 0xa0 */
    volatile U_ioshare_41           ioshare_41                        ; /* 0xa4 */
    volatile U_ioshare_42           ioshare_42                        ; /* 0xa8 */
    volatile U_ioshare_43           ioshare_43                        ; /* 0xac */
    volatile U_ioshare_44           ioshare_44                        ; /* 0xb0 */
    volatile U_ioshare_45           ioshare_45                        ; /* 0xb4 */
    volatile U_ioshare_46           ioshare_46                        ; /* 0xb8 */
    volatile U_ioshare_47           ioshare_47                        ; /* 0xbc */
    volatile U_ioshare_48           ioshare_48                        ; /* 0xc0 */
    volatile U_ioshare_49           ioshare_49                        ; /* 0xc4 */
    volatile U_ioshare_50           ioshare_50                        ; /* 0xc8 */
    volatile U_ioshare_51           ioshare_51                        ; /* 0xcc */
    volatile U_ioshare_52           ioshare_52                        ; /* 0xd0 */
    volatile U_ioshare_53           ioshare_53                        ; /* 0xd4 */
    volatile U_ioshare_54           ioshare_54                        ; /* 0xd8 */
    volatile U_ioshare_55           ioshare_55                        ; /* 0xdc */
    volatile U_ioshare_56           ioshare_56                        ; /* 0xe0 */
    volatile U_ioshare_57           ioshare_57                        ; /* 0xe4 */
    volatile U_ioshare_58           ioshare_58                        ; /* 0xe8 */
    volatile U_ioshare_59           ioshare_59                        ; /* 0xec */
    volatile U_ioshare_60           ioshare_60                        ; /* 0xf0 */
    volatile U_ioshare_61           ioshare_61                        ; /* 0xf4 */
    volatile U_ioshare_62           ioshare_62                        ; /* 0xf8 */
    volatile U_ioshare_63           ioshare_63                        ; /* 0xfc */
    volatile U_ioshare_64           ioshare_64                        ; /* 0x100 */
    volatile U_ioshare_65           ioshare_65                        ; /* 0x104 */
    volatile U_ioshare_66           ioshare_66                        ; /* 0x108 */
    volatile U_ioshare_67           ioshare_67                        ; /* 0x10c */
    volatile U_ioshare_68           ioshare_68                        ; /* 0x110 */
    volatile U_ioshare_69           ioshare_69                        ; /* 0x114 */
    volatile U_ioshare_70           ioshare_70                        ; /* 0x118 */
    volatile U_ioshare_71           ioshare_71                        ; /* 0x11c */
    volatile U_ioshare_72           ioshare_72                        ; /* 0x120 */
    volatile U_ioshare_73           ioshare_73                        ; /* 0x124 */
    volatile U_ioshare_74           ioshare_74                        ; /* 0x128 */
    volatile U_ioshare_75           ioshare_75                        ; /* 0x12c */
    volatile U_ioshare_76           ioshare_76                        ; /* 0x130 */
    volatile U_ioshare_77           ioshare_77                        ; /* 0x134 */
    volatile unsigned int           reserved_1[4]                     ; /* 0x138~0x144 */
    volatile U_ioshare_82           ioshare_82                        ; /* 0x148 */
    volatile U_ioshare_83           ioshare_83                        ; /* 0x14c */
    volatile U_ioshare_84           ioshare_84                        ; /* 0x150 */
    volatile U_ioshare_85           ioshare_85                        ; /* 0x154 */
    volatile U_ioshare_86           ioshare_86                        ; /* 0x158 */
    volatile U_ioshare_87           ioshare_87                        ; /* 0x15c */
    volatile U_ioshare_88           ioshare_88                        ; /* 0x160 */
    volatile U_ioshare_89           ioshare_89                        ; /* 0x164 */
    volatile U_ioshare_90           ioshare_90                        ; /* 0x168 */
    volatile U_ioshare_91           ioshare_91                        ; /* 0x16c */
    volatile U_ioshare_92           ioshare_92                        ; /* 0x170 */
    volatile U_ioshare_93           ioshare_93                        ; /* 0x174 */
    volatile U_ioshare_94           ioshare_94                        ; /* 0x178 */
    volatile U_ioshare_95           ioshare_95                        ; /* 0x17c */
    volatile U_ioshare_96           ioshare_96                        ; /* 0x180 */
    volatile U_ioshare_97           ioshare_97                        ; /* 0x184 */
    volatile U_ioshare_98           ioshare_98                        ; /* 0x188 */
    volatile U_ioshare_99           ioshare_99                        ; /* 0x18c */
    volatile U_ioshare_100          ioshare_100                       ; /* 0x190 */
    volatile U_ioshare_101          ioshare_101                       ; /* 0x194 */
    volatile U_ioshare_102          ioshare_102                       ; /* 0x198 */
    volatile U_ioshare_103          ioshare_103                       ; /* 0x19c */
    volatile U_ioshare_104          ioshare_104                       ; /* 0x1a0 */
    volatile U_ioshare_105          ioshare_105                       ; /* 0x1a4 */
    volatile U_ioshare_106          ioshare_106                       ; /* 0x1a8 */
    volatile unsigned int           reserved_2[512]                   ; /* 0x1ac~0x9a8 */
    volatile U_ioshare_107          ioshare_107                       ; /* 0x9ac */
    volatile U_ioshare_108          ioshare_108                       ; /* 0x1b0 */

} S_IO_REGS_TYPE;

#endif /* __HI_REG_IO_H__ */
