//	rs274ngc.h - just changed to #pragma once

#pragma once

#define AA
#define BB
#define CC
/*
  rs274ngc.hh

  Declarations for the rs274abc translator.

*/

/**********************/
/* INCLUDE DIRECTIVES */
/**********************/

#include <stdio.h>
#include "canon.h"

/**********************/
/*   COMPILER MACROS  */
/**********************/

#define AND              &&
#define IS               ==
#define ISNT             !=
#define MAX(x, y)        ((x) > (y) ? (x) : (y))
#define NOT              !
#define OR               ||
#define SET_TO           =

#ifndef TRUE
#define TRUE             1
#endif

#ifndef FALSE
#define FALSE            0
#endif

#define RS274NGC_TEXT_SIZE 256

/* numerical constants */
#define TOLERANCE_INCH 0.5
#define TOLERANCE_MM 12.5
#define TOLERANCE_CONCAVE_CORNER 0.2 /* angle threshold for concavity for
                                         cutter compensation, in radians */
#define TINY 1e-12 /* for arc_data_r */
#define UNKNOWN 1e-20
#define TWO_PI  6.2831853071795864

#ifndef PI
#define PI      3.1415926535897932
#endif

#ifndef PI2
#define PI2     1.5707963267948966
#endif

// array sizes
#define RS274NGC_ACTIVE_G_CODES 13
#define RS274NGC_ACTIVE_M_CODES 7
#define RS274NGC_ACTIVE_SETTINGS 3

// name of parameter file for saving/restoring interpreter variables
#define RS274NGC_PARAMETER_FILE_NAME_DEFAULT "rs274ngc.var"
#define RS274NGC_PARAMETER_FILE_BACKUP_SUFFIX ".bak"

// max number of m codes on one line
#define MAX_EMS  4

// English - Metric conversion (long number keeps error buildup down)
#define MM_PER_INCH 25.4
#define INCH_PER_MM 0.039370078740157477

// on-off switch settings
#define OFF 0
#define ON 1

// feed_mode
#define UNITS_PER_MINUTE 0
#define INVERSE_TIME 1
#define UNITS_PER_REV 2

// cutter radius compensation mode, OFF already defined to 0
// not using CANON_SIDE since interpreter handles cutter radius comp
#define RIGHT 1
#define LEFT 2

// number of parameters in parameter table
#define RS274NGC_MAX_PARAMETERS 15000

// unary operations
// These are not enums because the "&" operator is used in
// reading the operation names and is illegal with an enum

#define ABS 1
#define ACOS 2
#define ASIN 3
#define ATAN 4
#define COS 5
#define EXP 6
#define FIX 7
#define FUP 8
#define LN 9
#define ROUND 10
#define SIN 11
#define SQRT 12
#define TAN 13


// binary operations
#define NO_OPERATION 0
#define DIVIDED_BY 1
#define MODULO 2
#define POWER 3
#define TIMES 4
#define AND2 5
#define EXCLUSIVE_OR 6
#define MINUS 7
#define NON_EXCLUSIVE_OR 8
#define PLUS 9
#define RIGHT_BRACKET 10

// G Codes are symbolic to be dialect-independent in source code
#define G_0      0
#define G_1     10
#define G_2     20
#define G_3     30
#define G_4     40
#define G_8     80
#define G_9     90
#define G_10   100
#define G_12   120
#define G_13   130
#define G_15   150
#define G_16   160
#define G_17   170
#define G_18   180
#define G_19   190
#define G_20   200
#define G_21   210
#define G_28   280
#define G_28_1 281
#define G_30   300
#define G_31   310
#define G_32   320
#define G_38_2 382
#define G_40   400
#define G_40_1 401
#define G_40_2 402
#define G_41   410
#define G_42   420
#define G_43   430
#define G_44   440
#define G_48   480
#define G_49   490
#define G_50   500
#define G_51   510
#define G_52   520
#define G_53   530
#define G_54   540
#define G_55   550
#define G_56   560
#define G_57   570
#define G_58   580
#define G_59   590
#define G_59_1 591
#define G_59_2 592
#define G_59_3 593
#define G_61   610
#define G_61_1 611
#define G_64   640
#define G_65   650
#define G_68   680
#define G_69   690
#define G_70   700
#define G_71   710
#define G_73   730
#define G_76   760
#define G_77   770
#define G_78   780
#define G_80   800
#define G_801  801
#define G_802  802
#define G_81   810
#define G_82   820
#define G_83   830
#define G_831  831
#define G_832  832
#define G_84   840
#define G_85   850
#define G_86   860
#define G_87   870
#define G_88   880
#define G_89   890
#define G_90   900
#define G_901  901
#define G_91   910
#define G_911  911
#define G_92   920
#define G_92_1 921
#define G_92_2 922
#define G_92_3 923
#define G_93   930
#define G_94   940
#define G_95   950
#define G_96   960
#define G_97   970
#define G_98   980
#define G_99   990


#define RS274NGC_OK 0
#define RS274NGC_EXIT 1
#define RS274NGC_EXECUTE_FINISH 2
#define RS274NGC_ENDFILE 3
#define NCE_A_FILE_IS_ALREADY_OPEN 4
#define NCE_ALL_AXES_MISSING_WITH_G92 5
#define NCE_ALL_AXES_MISSING_WITH_MOTION_CODE 6
#define NCE_ARC_RADIUS_TOO_SMALL_TO_REACH_END_POINT 7
#define NCE_ARGUMENT_TO_ACOS_OUT_OF_RANGE 8
#define NCE_ARGUMENT_TO_ASIN_OUT_OF_RANGE 9
#define NCE_ATTEMPT_TO_DIVIDE_BY_ZERO 10
#define NCE_ATTEMPT_TO_RAISE_NEGATIVE_TO_NON_INTEGER_POWER 11
#define NCE_BAD_CHARACTER_USED 12
#define NCE_BAD_FORMAT_UNSIGNED_INTEGER 13
#define NCE_BAD_NUMBER_FORMAT 14
#define NCE_BUG_BAD_G_CODE_MODAL_GROUP_0 15
#define NCE_BUG_CODE_NOT_G0_OR_G1 16
#define NCE_BUG_CODE_NOT_G17_G18_OR_G19 17
#define NCE_BUG_CODE_NOT_G20_OR_G21 18
#define NCE_BUG_CODE_NOT_G28_OR_G30 19
#define NCE_BUG_CODE_NOT_G2_OR_G3 20
#define NCE_BUG_CODE_NOT_G40_G41_OR_G42 21
#define NCE_BUG_CODE_NOT_G43_OR_G49 22
#define NCE_BUG_CODE_NOT_G4_G10_G28_G30_G53_OR_G92_SERIES 23
#define NCE_BUG_CODE_NOT_G61_G61_1_OR_G64 24
#define NCE_BUG_CODE_NOT_G90_OR_G91 25
#define NCE_BUG_CODE_NOT_G93_OR_G94 26
#define NCE_BUG_CODE_NOT_G98_OR_G99 27
#define NCE_BUG_CODE_NOT_IN_G92_SERIES 28
#define NCE_BUG_CODE_NOT_IN_RANGE_G54_TO_G593 29
#define NCE_BUG_CODE_NOT_M0_M1_M2_M30_M60 30
#define NCE_BUG_DISTANCE_MODE_NOT_G90_OR_G91 31
#define NCE_BUG_FUNCTION_SHOULD_NOT_HAVE_BEEN_CALLED 32
#define NCE_BUG_IN_TOOL_RADIUS_COMP 33
#define NCE_BUG_PLANE_NOT_XY_YZ_OR_XZ 34
#define NCE_BUG_SIDE_NOT_RIGHT_OR_LEFT 35
#define NCE_BUG_UNKNOWN_MOTION_CODE 36
#define NCE_BUG_UNKNOWN_OPERATION 37
#define NCE_CANNOT_CHANGE_AXIS_OFFSETS_WITH_CUTTER_RADIUS_COMP 38
#define NCE_CANNOT_CHANGE_UNITS_WITH_CUTTER_RADIUS_COMP 39
#define NCE_CANNOT_CREATE_BACKUP_FILE 40
#define NCE_CANNOT_DO_G1_WITH_ZERO_FEED_RATE 41
#define NCE_CANNOT_DO_ZERO_REPEATS_OF_CYCLE 42
#define NCE_CANNOT_MAKE_ARC_WITH_ZERO_FEED_RATE 43
#define NCE_CANNOT_MOVE_ROTARY_AXES_DURING_PROBING 44
#define NCE_CANNOT_OPEN_BACKUP_FILE 45
#define NCE_CANNOT_OPEN_VARIABLE_FILE 46
#define NCE_CANNOT_PROBE_IN_INVERSE_TIME_FEED_MODE 47
#define NCE_CANNOT_PROBE_WITH_CUTTER_RADIUS_COMP_ON 48
#define NCE_CANNOT_PROBE_WITH_ZERO_FEED_RATE 49
#define NCE_CANNOT_PUT_A_B_IN_CANNED_CYCLE 50
#define NCE_CANNOT_PUT_A_C_IN_CANNED_CYCLE 51
#define NCE_CANNOT_PUT_AN_A_IN_CANNED_CYCLE 52
#define NCE_CANNOT_TURN_CUTTER_RADIUS_COMP_ON_OUT_OF_XY_PLANE 53
#define NCE_CANNOT_TURN_CUTTER_RADIUS_COMP_ON_WHEN_ON 54
#define NCE_CANNOT_USE_A_WORD 55
#define NCE_CANNOT_USE_AXIS_VALUES_WITH_G80 56
#define NCE_CANNOT_USE_AXIS_VALUES_WITHOUT_A_G_CODE_THAT_USES_THEM 57
#define NCE_CANNOT_USE_B_WORD 58
#define NCE_CANNOT_USE_C_WORD 59
#define NCE_CANNOT_USE_G28_OR_G30_WITH_CUTTER_RADIUS_COMP 60
#define NCE_CANNOT_USE_G53_INCREMENTAL 61
#define NCE_CANNOT_USE_G53_WITH_CUTTER_RADIUS_COMP 62
#define NCE_CANNOT_USE_TWO_G_CODES_THAT_BOTH_USE_AXIS_VALUES 63
#define NCE_CANNOT_USE_XZ_PLANE_WITH_CUTTER_RADIUS_COMP 64
#define NCE_CANNOT_USE_YZ_PLANE_WITH_CUTTER_RADIUS_COMP 65
#define NCE_COMMAND_TOO_LONG 66
#define NCE_CONCAVE_CORNER_WITH_CUTTER_RADIUS_COMP 67
#define NCE_COORDINATE_SYSTEM_INDEX_PARAMETER_5220_OUT_OF_RANGE 68
#define NCE_CURRENT_POINT_SAME_AS_END_POINT_OF_ARC 69
#define NCE_CUTTER_GOUGING_WITH_CUTTER_RADIUS_COMP 70
#define NCE_D_WORD_WITH_NO_G41_OR_G42 71
#define NCE_DWELL_TIME_MISSING_WITH_G4 72
#define NCE_DWELL_TIME_P_WORD_MISSING_WITH_G82 73
#define NCE_DWELL_TIME_P_WORD_MISSING_WITH_G86 74
#define NCE_DWELL_TIME_P_WORD_MISSING_WITH_G88 75
#define NCE_DWELL_TIME_P_WORD_MISSING_WITH_G89 76
#define NCE_EQUAL_SIGN_MISSING_IN_PARAMETER_SETTING 77
#define NCE_F_WORD_MISSING_WITH_INVERSE_TIME_ARC_MOVE 78
#define NCE_F_WORD_MISSING_WITH_INVERSE_TIME_G1_MOVE 79
#define NCE_FILE_ENDED_WITH_NO_PERCENT_SIGN 80
#define NCE_FILE_ENDED_WITH_NO_PERCENT_SIGN_OR_PROGRAM_END 81
#define NCE_FILE_NAME_TOO_LONG 82
#define NCE_FILE_NOT_OPEN 83
#define NCE_G_CODE_OUT_OF_RANGE 84
#define NCE_H_WORD_WITH_NO_G43 85
#define NCE_I_WORD_GIVEN_FOR_ARC_IN_YZ_PLANE 86
#define NCE_I_WORD_MISSING_WITH_G87 87
#define NCE_I_WORD_WITH_NO_G2_OR_G3_OR_G87_TO_USE_IT 88
#define NCE_J_WORD_GIVEN_FOR_ARC_IN_XZ_PLANE 89
#define NCE_J_WORD_MISSING_WITH_G87 90
#define NCE_J_WORD_WITH_NO_G2_OR_G3_OR_G87_TO_USE_IT 91
#define NCE_K_WORD_GIVEN_FOR_ARC_IN_XY_PLANE 92
#define NCE_K_WORD_MISSING_WITH_G87 93
#define NCE_K_WORD_WITH_NO_G2_OR_G3_OR_G87_TO_USE_IT 94
#define NCE_L_WORD_WITH_NO_CANNED_CYCLE_OR_G10 95
#define NCE_LEFT_BRACKET_MISSING_AFTER_SLASH_WITH_ATAN 96
#define NCE_LEFT_BRACKET_MISSING_AFTER_UNARY_OPERATION_NAME 97
#define NCE_LINE_NUMBER_GREATER_THAN_99999 98
#define NCE_LINE_WITH_G10_DOES_NOT_HAVE_L2 99
#define NCE_M_CODE_GREATER_THAN_99 100
#define NCE_MIXED_RADIUS_IJK_FORMAT_FOR_ARC 101
#define NCE_MULTIPLE_A_WORDS_ON_ONE_LINE 102
#define NCE_MULTIPLE_B_WORDS_ON_ONE_LINE 103
#define NCE_MULTIPLE_C_WORDS_ON_ONE_LINE 104
#define NCE_MULTIPLE_D_WORDS_ON_ONE_LINE 105
#define NCE_MULTIPLE_F_WORDS_ON_ONE_LINE 106
#define NCE_MULTIPLE_H_WORDS_ON_ONE_LINE 107
#define NCE_MULTIPLE_I_WORDS_ON_ONE_LINE 108
#define NCE_MULTIPLE_J_WORDS_ON_ONE_LINE 109
#define NCE_MULTIPLE_K_WORDS_ON_ONE_LINE 110
#define NCE_MULTIPLE_L_WORDS_ON_ONE_LINE 111
#define NCE_MULTIPLE_P_WORDS_ON_ONE_LINE 112
#define NCE_MULTIPLE_Q_WORDS_ON_ONE_LINE 113
#define NCE_MULTIPLE_R_WORDS_ON_ONE_LINE 114
#define NCE_MULTIPLE_S_WORDS_ON_ONE_LINE 115
#define NCE_MULTIPLE_T_WORDS_ON_ONE_LINE 116
#define NCE_MULTIPLE_X_WORDS_ON_ONE_LINE 117
#define NCE_MULTIPLE_Y_WORDS_ON_ONE_LINE 118
#define NCE_MULTIPLE_Z_WORDS_ON_ONE_LINE 119
#define NCE_MUST_USE_G0_OR_G1_WITH_G53 120
#define NCE_NEGATIVE_ARGUMENT_TO_SQRT 121
#define NCE_NEGATIVE_D_WORD_TOOL_RADIUS_INDEX_USED 122
#define NCE_NEGATIVE_F_WORD_USED 123
#define NCE_NEGATIVE_G_CODE_USED 124
#define NCE_NEGATIVE_H_WORD_TOOL_LENGTH_OFFSET_INDEX_USED 125
#define NCE_NEGATIVE_L_WORD_USED 126
#define NCE_NEGATIVE_M_CODE_USED 127
#define NCE_NEGATIVE_OR_ZERO_Q_VALUE_USED 128
#define NCE_NEGATIVE_P_WORD_USED 129
#define NCE_NEGATIVE_SPINDLE_SPEED_USED 130
#define NCE_NEGATIVE_TOOL_ID_USED 131
#define NCE_NESTED_COMMENT_FOUND 132
#define NCE_NO_CHARACTERS_FOUND_IN_READING_REAL_VALUE 133
#define NCE_NO_DIGITS_FOUND_WHERE_REAL_NUMBER_SHOULD_BE 134
#define NCE_NON_INTEGER_VALUE_FOR_INTEGER 135
#define NCE_NULL_MISSING_AFTER_NEWLINE 136
#define NCE_OFFSET_INDEX_MISSING 137
#define NCE_P_VALUE_NOT_AN_INTEGER_WITH_G10_L2 138
#define NCE_P_VALUE_OUT_OF_RANGE_WITH_G10_L2 139
#define NCE_P_WORD_WITH_NO_G4_G10_G82_G86_G88_G89 140
#define NCE_PARAMETER_FILE_OUT_OF_ORDER 141
#define NCE_PARAMETER_NUMBER_OUT_OF_RANGE 142
#define NCE_Q_WORD_MISSING_WITH_G83 143
#define NCE_Q_WORD_WITH_NO_G83 144
#define NCE_QUEUE_IS_NOT_EMPTY_AFTER_PROBING 145
#define NCE_R_CLEARANCE_PLANE_UNSPECIFIED_IN_CYCLE 146
#define NCE_R_I_J_K_WORDS_ALL_MISSING_FOR_ARC 147
#define NCE_R_LESS_THAN_X_IN_CYCLE_IN_YZ_PLANE 148
#define NCE_R_LESS_THAN_Y_IN_CYCLE_IN_XZ_PLANE 149
#define NCE_R_LESS_THAN_Z_IN_CYCLE_IN_XY_PLANE 150
#define NCE_R_WORD_WITH_NO_G_CODE_THAT_USES_IT 151
#define NCE_RADIUS_TO_END_OF_ARC_DIFFERS_FROM_RADIUS_TO_START 152
#define NCE_RADIUS_TOO_SMALL_TO_REACH_END_POINT 153
#define NCE_REQUIRED_PARAMETER_MISSING 154
#define NCE_SELECTED_TOOL_SLOT_NUMBER_TOO_LARGE 155
#define NCE_SLASH_MISSING_AFTER_FIRST_ATAN_ARGUMENT 156
#define NCE_SPINDLE_NOT_TURNING_CLOCKWISE_IN_G84 157
#define NCE_SPINDLE_NOT_TURNING_IN_G86 158
#define NCE_SPINDLE_NOT_TURNING_IN_G87 159
#define NCE_SPINDLE_NOT_TURNING_IN_G88 160
#define NCE_SSCANF_FAILED 161
#define NCE_START_POINT_TOO_CLOSE_TO_PROBE_POINT 162
#define NCE_TOO_MANY_M_CODES_ON_LINE 163
#define NCE_TOOL_LENGTH_OFFSET_INDEX_TOO_BIG 164
#define NCE_TOOL_MAX_TOO_LARGE 165
#define NCE_TOOL_RADIUS_INDEX_TOO_BIG 166
#define NCE_TOOL_RADIUS_NOT_LESS_THAN_ARC_RADIUS_WITH_COMP 167
#define NCE_TWO_G_CODES_USED_FROM_SAME_MODAL_GROUP 168
#define NCE_TWO_M_CODES_USED_FROM_SAME_MODAL_GROUP 169
#define NCE_UNABLE_TO_OPEN_FILE 170
#define NCE_UNCLOSED_COMMENT_FOUND 171
#define NCE_UNCLOSED_EXPRESSION 172
#define NCE_UNKNOWN_G_CODE_USED 173
#define NCE_UNKNOWN_M_CODE_USED 174
#define NCE_UNKNOWN_OPERATION 175
#define NCE_UNKNOWN_OPERATION_NAME_STARTING_WITH_A 176
#define NCE_UNKNOWN_OPERATION_NAME_STARTING_WITH_M 177
#define NCE_UNKNOWN_OPERATION_NAME_STARTING_WITH_O 178
#define NCE_UNKNOWN_OPERATION_NAME_STARTING_WITH_X 179
#define NCE_UNKNOWN_WORD_STARTING_WITH_A 180
#define NCE_UNKNOWN_WORD_STARTING_WITH_C 181
#define NCE_UNKNOWN_WORD_STARTING_WITH_E 182
#define NCE_UNKNOWN_WORD_STARTING_WITH_F 183
#define NCE_UNKNOWN_WORD_STARTING_WITH_L 184
#define NCE_UNKNOWN_WORD_STARTING_WITH_R 185
#define NCE_UNKNOWN_WORD_STARTING_WITH_S 186
#define NCE_UNKNOWN_WORD_STARTING_WITH_T 187
#define NCE_UNKNOWN_WORD_WHERE_UNARY_OPERATION_COULD_BE 188
#define NCE_X_AND_Y_WORDS_MISSING_FOR_ARC_IN_XY_PLANE 189
#define NCE_X_AND_Z_WORDS_MISSING_FOR_ARC_IN_XZ_PLANE 190
#define NCE_X_VALUE_UNSPECIFIED_IN_YZ_PLANE_CANNED_CYCLE 191
#define NCE_X_Y_AND_Z_WORDS_ALL_MISSING_WITH_G38_2 192
#define NCE_Y_AND_Z_WORDS_MISSING_FOR_ARC_IN_YZ_PLANE 193
#define NCE_Y_VALUE_UNSPECIFIED_IN_XZ_PLANE_CANNED_CYCLE 194
#define NCE_Z_VALUE_UNSPECIFIED_IN_XY_PLANE_CANNED_CYCLE 195
#define NCE_ZERO_OR_NEGATIVE_ARGUMENT_TO_LN 196
#define NCE_ZERO_RADIUS_ARC 197
#define NCE_F_WORD_MISSING_WITH_THREADING 198
#define NCE_NO_SUBROUTINE_SPECIFIED 199
#define NCE_NO_SPINDLE_SPEED_WITH_G96 200
#define NCE_NO_SPINDLE_SPEED_WITH_G97 201
#define NCE_NO_R_WITH_ROTATION 202
#define NCE_NO_A_OR_B_WITH_ROTATION 203
#define NCE_NOG43INTURN  204
#define NCE_MULTIPLE_E_WORDS_ON_ONE_LINE 205

#define RS274NGC_MIN_ERROR 3
#define RS274NGC_MAX_ERROR 199
#define SEMI_COLON  999;

/**********************/
/*      TYPEDEFS      */
/**********************/

/* distance_mode */
typedef enum {MODE_ABSOLUTE, MODE_INCREMENTAL} DISTANCE_MODE;

/* retract_mode for cycles */
typedef enum {R_PLANE, OLD_Z} RETRACT_MODE;

typedef int ON_OFF;

typedef struct block_struct {
#ifdef AA
  ON_OFF   a_flag;
  double   a_number;
#endif
#ifdef BB
  ON_OFF   b_flag;
  double   b_number;
#endif
#ifdef CC
  ON_OFF   c_flag;
  double   c_number;
#endif
  char     comment[256];
  int      d_number;
  int      e_number;
  double   f_number;
  int      g_modes[14];
  
  int      h_number;
  double   h_double;
  ON_OFF   h_flag;

  ON_OFF   i_flag;
  double   i_number;
  ON_OFF   j_flag;
  double   j_number;
  ON_OFF   k_flag;
  double   k_number;
  int      l_number;
  double   l_double;
  ON_OFF   l_flag;
  int      line_number;
  int      motion_to_be;
  int      m_count;
  int      m_modes[10];
  double   p_number;
  double   q_number;
  ON_OFF   q_flag;
  ON_OFF   r_flag;
  double   r_number;
  double   s_number;
  double   t_number;
  ON_OFF   x_flag;
  double   x_number;
  ON_OFF   y_flag;
  double   y_number;
  ON_OFF   z_flag;
  double   z_number;
} block;

typedef block * block_pointer;




/*The current_x, current_y, and current_z are the location of the tool
in the current coordinate system. current_x and current_y differ from
program_x and program_y when cutter radius compensation is on.
current_z is the position of the tool tip in program coordinates when
tool length compensation is using the actual tool length; it is the
position of the spindle when tool length is zero.

In a setup, the axis_offset values are set by g92 and the origin_offset
values are set by g54 - g59.3. The net origin offset uses both values
and is not represented here

*/

typedef struct setup_struct {
 
  double AA_axis_offset;             // A-axis g92 offset
  double AA_current;                 // current A-axis position
  double AA_origin_offset;           // A-axis origin offset
 
  double BB_axis_offset;             // B-axis g92offset
  double BB_current;                 // current B-axis position
  double BB_origin_offset;           // B-axis origin offset
 
  double CC_axis_offset;             // C-axis g92offset
  double CC_current;                 // current C-axis position
  double CC_origin_offset;           // C-axis origin offset
 
  int active_g_codes
      [RS274NGC_ACTIVE_G_CODES];     // array of active G codes
  int active_m_codes
      [RS274NGC_ACTIVE_M_CODES];     // array of active M codes
  double active_settings
      [RS274NGC_ACTIVE_SETTINGS];    // array of feed, speed, etc.
  double axis_offset_x;              // X-axis g92 offset
  double axis_offset_y;              // Y-axis g92 offset
  double axis_offset_z;              // Z-axis g92 offset
  block block1;                      // parsed next block
  char blocktext[RS274NGC_TEXT_SIZE];// linetext downcased, white space gone
  CANON_MOTION_MODE control_mode;    // exact path or cutting mode
  int current_slot;                  // carousel slot number of current tool
  int current_offset_slot;           //for turn offsets, current slot in use.  
  int current_tip;                   //current tip direction.
  double cutter_tip_radius;          //for turn offsets
 // bool   cutter_tip_on;              // lathe tip radisu on/off
  double current_x;                  // current X-axis position
  double current_y;                  // current Y-axis position
  double current_z;                  // current Z-axis position
  double cutter_comp_radius;         // current cutter compensation radius
  int cutter_comp_side;              // current cutter compensation side
  double cycle_cc;                   // cc-value (normal) for canned cycles
  double cycle_i;                    // i-value for canned cycles
  double cycle_j;                    // j-value for canned cycles
  double cycle_k;                    // k-value for canned cycles
  int cycle_l;                       // l-value for canned cycles
  double cycle_p;                    // p-value (dwell) for canned cycles
  double cycle_q;                    // q-value for canned cycles
  double cycle_r;                    // r-value for canned cycles
  DISTANCE_MODE distance_mode;       // absolute or incremental
  int feed_mode;                     // G_93 (inverse time) or G_94 units/min
  int spindle_mode;
  ON_OFF feed_override;              // whether feed override is enabled
  double feed_rate;                  // feed rate in current units/min
  char filename[RS274NGC_TEXT_SIZE]; // name of currently open NC code file
  FILE * file_pointer;               // file pointer for open NC code file
  ON_OFF flood;                      // whether flood coolant is on
  int length_offset_index;           // for use with tool length offsets
  int length_units;          // millimeters or inches
  int line_length;                   // length of line last read
  char linetext[RS274NGC_TEXT_SIZE]; // text of most recent line read
  ON_OFF mist;                       // whether mist coolant is on
  int motion_mode;                   // active G-code for motion
  int origin_index;                  // active origin (1=G54 to 9=G59.3)
  double origin_offset_x;            // origin offset x
  double origin_offset_y;            // origin offset y
  double origin_offset_z;            // origin offset z
  double parameters
      [RS274NGC_MAX_PARAMETERS];     // system parameters
  int parameter_occurrence;          // parameter buffer index
  int parameter_numbers[50];         // parameter number buffer
  double parameter_values[50];       // parameter value buffer
  ON_OFF percent_flag;               // ON means first line was percent sign
  CANON_PLANE plane;                 // active plane, XY-, YZ-, or XZ-plane
  ON_OFF probe_flag;                 // flag indicating probing done
  double program_x;                  // program x, used when cutter comp on
  double program_y;                  // program y, used when cutter comp on
  double program_z;                  // used in tnc
  RETRACT_MODE retract_mode;         // for cycles, old_z or r_plane
  int selected_tool_slot;            // tool slot selected but not active
  int sequence_number;               // sequence number of line last read
  double speed;                      // current spindle speed in rpm
  CANON_SPEED_FEED_MODE speed_feed_mode;   // independent or synched
  ON_OFF speed_override;             // whether speed override is enabled
  CANON_DIRECTION spindle_turning;   // direction spindle is turning
  int stack_index;                   // index into the stack
  double tool_length_offset;         // current tool length offset
  double tool_xoffset;
  int dummy;
  int tool_max;                      // highest number tool slot in carousel
  int tool_table_index;              // tool index used with cutter comp
  double traverse_rate;              // rate for traverse motions
  int IJMode;
  double CurrentOrigins[6];
  bool  AutoTurnOff;
  bool  AutoEStop;
  bool  RadiusCompOff;
  bool  AutoToolOff;
  int   OverRideTime;
  bool  OptionalStop;
  bool  Rewind;
  bool  ProgramSafety;
  bool  HotKeyCheck;
  double JogPercent;
  int    ColorUnRef;
  int    ColorRef;
  int    ColorBac;
  bool   GougeCheck;
  double xscale,yscale,zscale,ascale,bscale,cscale;
  bool   xmirror,ymirror,zmirror,amirror,bmirror,cmirror;
  double Diameters[3];
  bool   startagain;
  bool   drawtocenter;
  bool   G92Off;
  bool   OriginsOff;
  int    LightLine;
  bool   ForceRefresh;
  char stack[50][80];                // stack of calls for error reporting
  bool Threading;
  double  Cylinder;
  bool    MillMode;

  //threading variables...
  double XStart;
  double ZStart;
  double XEnd;
  double ZEnd;
  int    Spring;
  double Pitch;
  double Passes;
  double DepthCut;
  double Infeed;
  double Chamfer;
  double ClearanceX;
  double ClearanceZ;
  double DepthLastPass;
  double MinPerPass;
  double Taper;
  double Tapers[256];
  double ThreadDepths[256];
  double InFeeds[256];
  double IncludedAngle;
  block  MacroBlock;
  bool   polar;
  double polarx;
  double polary;
  double polAngle;
  double polRadius;
  double G73PullOff;
  int    LastMotionMode;
  bool   Diameter;
  bool   Redraw;
  int    CutType;
  int    InFeedType;
  double tempspeed;
  double Rotation;
  double RotationX;
  double RotationY;
  double PausedAt[6];
  double CSSLimit;
  double peck;
  bool  CompInUse;
} setup;

typedef setup * setup_pointer;

// pointer to function that reads
typedef int (*read_function_pointer) (char *, int *, block_pointer, double *);


/*************************************************************************/
/*

Interface functions to call to tell the interpreter what to do.
Return values indicate status of execution.
These functions may change the state of the interpreter.

*/

// close the currently open NC code file
extern int rs274ngc_close();

// execute a line of NC code
#ifndef NOT_OLD_EMC_INTERP_COMPATIBLE
extern int rs274ngc_execute(const char *command=0);
#else
extern int rs274ngc_execute();
#endif

// stop running
extern int rs274ngc_exit();

// get ready to run
extern int rs274ngc_init();

// load a tool table
extern int rs274ngc_load_tool_table();

// open a file of NC code
extern int rs274ngc_open(const char *filename);

// read the mdi or the next line of the open NC code file
extern int rs274ngc_read(const char * mdi = 0);

// reset yourself
extern int rs274ngc_reset();

// restore interpreter variables from a file
extern int rs274ngc_restore_parameters(const char * filename);

// save interpreter variables to file
extern int rs274ngc_save_parameters(const char * filename,
                                    const double parameters[]);

// synchronize your internal model with the external world
extern int rs274ngc_synch();


/*************************************************************************/
/*

Interface functions to call to get information from the interpreter.
If a function has a return value, the return value contains the information.
If a function returns nothing, information is copied into one of the
arguments to the function. These functions do not change the state of
the interpreter.

*/
 
// copy active G codes into array [0]..[11]
extern void rs274ngc_active_g_codes(int * codes);

// copy active M codes into array [0]..[6]
extern void rs274ngc_active_m_codes(int * codes);

// copy active F, S settings into array [0]..[2]
extern void rs274ngc_active_settings(double * settings);

// copy the text of the error message whose number is error_code into the
// error_text array, but stop at max_size if the text is longer.
extern void rs274ngc_error_text(int error_code, char * error_text,
                                int max_size);

// copy the name of the currently open file into the file_name array,
// but stop at max_size if the name is longer
extern void rs274ngc_file_name(char * file_name, int max_size);

// return the length of the most recently read line
extern int rs274ngc_line_length();

// copy the text of the most recently read line into the line_text array,
// but stop at max_size if the text is longer
extern void rs274ngc_line_text(char * line_text, int max_size);

// return the current sequence number (how many lines read)
extern int rs274ngc_sequence_number();

// copy the function name from the stack_index'th position of the
// function call stack at the time of the most recent error into
// the function name string, but stop at max_size if the name is longer
extern void rs274ngc_stack_name(int stack_index, char * function_name,
                                int max_size);


#ifndef NOT_OLD_EMC_INTERP_COMPATABLE
// Get the parameter file name from the ini file.
extern int rs274ngc_ini_load(const char *filename);
static inline int rs274ngc_line() {return rs274ngc_sequence_number();}
static inline const char *rs274ngc_command() { static char buf[100]; rs274ngc_line_text(buf,100); return buf;}
static inline const char *rs274ngc_file() { static char buf[100]; rs274ngc_file_name(buf,100); return buf;}

#endif
