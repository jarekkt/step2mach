#ifndef DMCDRCO_H
	#define DMCDRCO_H

// Data Record Access constants provided for backwards
// compatibility

// General offsets for firmware without coordinated motion T axis
enum DMCDataRecordGeneralOffsets
{
   DRGeneralOffsetsSampleNumber = 0,
	DRGeneralOffsetsGeneralInput0 = 2,
	DRGeneralOffsetsGeneralInput1 = 3,
	DRGeneralOffsetsGeneralInput2 = 4,
	DRGeneralOffsetsGeneralInput3 = 5,
	DRGeneralOffsetsGeneralInput4 = 6,
	DRGeneralOffsetsGeneralInput5 = 7,
	DRGeneralOffsetsGeneralInput6 = 8,
	DRGeneralOffsetsGeneralInput7 = 9,
	DRGeneralOffsetsGeneralInput8 = 10,
	DRGeneralOffsetsGeneralInput9 = 11,
	DRGeneralOffsetsGeneralOutput0 = 12,
	DRGeneralOffsetsGeneralOutput1 = 13,
	DRGeneralOffsetsGeneralOutput2 = 14,
	DRGeneralOffsetsGeneralOutput3 = 15,
	DRGeneralOffsetsGeneralOutput4 = 16,
	DRGeneralOffsetsGeneralOutput5 = 17,
	DRGeneralOffsetsGeneralOutput6 = 18,
	DRGeneralOffsetsGeneralOutput7 = 19,
	DRGeneralOffsetsGeneralOutput8 = 20,
	DRGeneralOffsetsGeneralOutput9 = 21,
	DRGeneralOffsetsErrorCode = 22,
	DRGeneralOffsetsGeneralStatus = 23,
	DRGeneralOffsetsSegmentCount = 24,
	DRGeneralOffsetsCoordinatedMoveStatus = 26,
	DRGeneralOffsetsCoordinatedMoveDistance = 28,
	DRGeneralOffsetsAxis1 = 32,
	DRGeneralOffsetsAxis2 = 58,
	DRGeneralOffsetsAxis3 = 84,
	DRGeneralOffsetsAxis4 = 110,
	DRGeneralOffsetsAxis5 = 136,
	DRGeneralOffsetsAxis6 = 162,
	DRGeneralOffsetsAxis7 = 188,
	DRGeneralOffsetsAxis8 = 214,
	DRGeneralOffsetsEnd = 240
};

// General offsets for firmware with coordinated motion T axis
enum DMCDataRecordwTDRGeneralOffsets
{
   wTDRGeneralOffsetsSampleNumber = 0,
	wTDRGeneralOffsetsGeneralInput0 = 2,
	wTDRGeneralOffsetsGeneralInput1 = 3,
	wTDRGeneralOffsetsGeneralInput2 = 4,
	wTDRGeneralOffsetsGeneralInput3 = 5,
	wTDRGeneralOffsetsGeneralInput4 = 6,
	wTDRGeneralOffsetsGeneralInput5 = 7,
	wTDRGeneralOffsetsGeneralInput6 = 8,
	wTDRGeneralOffsetsGeneralInput7 = 9,
	wTDRGeneralOffsetsGeneralInput8 = 10,
	wTDRGeneralOffsetsGeneralInput9 = 11,
	wTDRGeneralOffsetsGeneralOutput0 = 12,
	wTDRGeneralOffsetsGeneralOutput1 = 13,
	wTDRGeneralOffsetsGeneralOutput2 = 14,
	wTDRGeneralOffsetsGeneralOutput3 = 15,
	wTDRGeneralOffsetsGeneralOutput4 = 16,
	wTDRGeneralOffsetsGeneralOutput5 = 17,
	wTDRGeneralOffsetsGeneralOutput6 = 18,
	wTDRGeneralOffsetsGeneralOutput7 = 19,
	wTDRGeneralOffsetsGeneralOutput8 = 20,
	wTDRGeneralOffsetsGeneralOutput9 = 21,
	wTDRGeneralOffsetsErrorCode = 22,
	wTDRGeneralOffsetsGeneralStatus = 23,
	wTDRGeneralOffsetsSegmentCountS = 24,
	wTDRGeneralOffsetsCoordinatedMoveStatusS = 26,
	wTDRGeneralOffsetsCoordinatedMoveDistanceS = 28,
	wTDRGeneralOffsetsSegmentCountT = 32,
	wTDRGeneralOffsetsCoordinatedMoveStatusT = 34,
	wTDRGeneralOffsetsCoordinatedMoveDistanceT = 36,
	wTDRGeneralOffsetsAxis1 = 40,
	wTDRGeneralOffsetsAxis2 = 66,
	wTDRGeneralOffsetsAxis3 = 92,
	wTDRGeneralOffsetsAxis4 = 118,
	wTDRGeneralOffsetsAxis5 = 144,
	wTDRGeneralOffsetsAxis6 = 170,
	wTDRGeneralOffsetsAxis7 = 196,
	wTDRGeneralOffsetsAxis8 = 222,
	wTDRGeneralOffsetsEnd = 248
};

// Constant values for data record axis data item offsets
enum DMCDataRecordAxisOffsets
{
	DRAxisOffsetsNoAxis = 0,
	DRAxisOffsetsAxisStatus = 0,
	DRAxisOffsetsAxisSwitches = 2,
	DRAxisOffsetsAxisStopCode = 3,
	DRAxisOffsetsAxisReferencePosition = 4,
	DRAxisOffsetsAxisMotorPosition = 8,
	DRAxisOffsetsAxisPositionError = 12,
	DRAxisOffsetsAxisAuxillaryPosition = 16,
	DRAxisOffsetsAxisVelocity = 20,
	DRAxisOffsetsAxisTorque = 24,
	DRAxisOffsetsEnd = 26
};

#endif // DMCDRCO_H
