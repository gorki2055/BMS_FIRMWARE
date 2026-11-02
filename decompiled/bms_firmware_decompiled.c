// ===========================================================================
// BMS Firmware Decompiled Output (Ghidra Headless Decompiler)
// Target: Nations N32G452 (ARM Cortex-M4F @ 144MHz)
// Firmware: 21S 70Ah NCM Battery Management System
// ===========================================================================

// ---------------------------------------------------------------------------
// Function: __main at 0x08008198
// ---------------------------------------------------------------------------

void __main(void)

{
  __scatterload();
  (*DAT_080081a4)();
  return;
}



// ---------------------------------------------------------------------------
// Function: main at 0x080081a0
// ---------------------------------------------------------------------------

void main(void)

{
  (*DAT_080081a4)();
  return;
}



// ---------------------------------------------------------------------------
// Function: Reset_Handler at 0x080081b0
// ---------------------------------------------------------------------------

void Reset_Handler(void)

{
  (*DAT_080081cc)();
                    /* WARNING: Could not recover jumptable at 0x080081b6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_080081d0)();
  return;
}



// ---------------------------------------------------------------------------
// Function: PendSV_Handler at 0x080081c6
// ---------------------------------------------------------------------------

void PendSV_Handler(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ---------------------------------------------------------------------------
// Function: FUN_080081d4 at 0x080081d4
// ---------------------------------------------------------------------------

longlong FUN_080081d4(uint param_1,int param_2,uint param_3)

{
  if ((int)param_3 < 0x20) {
    return CONCAT44(param_2 << (param_3 & 0xff) | param_1 >> (0x20 - param_3 & 0xff),
                    param_1 << (param_3 & 0xff));
  }
  return (ulonglong)(param_1 << (param_3 - 0x20 & 0xff)) << 0x20;
}



// ---------------------------------------------------------------------------
// Function: FUN_080081f2 at 0x080081f2
// ---------------------------------------------------------------------------

void FUN_080081f2(undefined1 *param_1,int param_2,undefined1 param_3)

{
  bool bVar1;
  
  while (bVar1 = param_2 != 0, param_2 = param_2 + -1, bVar1) {
    *param_1 = param_3;
    param_1 = param_1 + 1;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08008200 at 0x08008200
// ---------------------------------------------------------------------------

void FUN_08008200(undefined4 param_1,undefined4 param_2)

{
  FUN_080081f2(param_1,param_2,0);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08008204 at 0x08008204
// ---------------------------------------------------------------------------

undefined4 FUN_08008204(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_080081f2(param_1,param_3,param_2);
  return param_1;
}



// ---------------------------------------------------------------------------
// Function: FUN_08008216 at 0x08008216
// ---------------------------------------------------------------------------

uint FUN_08008216(uint param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  bool bVar10;
  ulonglong uVar11;
  longlong lVar12;
  
  iVar1 = (int)(param_2 ^ param_4) >> 0x1f;
  iVar2 = -iVar1;
  uVar7 = param_3;
  uVar9 = param_4;
  if ((param_2 & 0x7fffffff) <= (param_4 & 0x7fffffff) &&
      (uint)(param_3 <= param_1) <= (param_2 & 0x7fffffff) - (param_4 & 0x7fffffff)) {
    uVar7 = param_1;
    uVar9 = param_2;
    param_2 = param_4;
    param_1 = param_3;
  }
  if ((uVar9 & 0x7fffffff) == 0 && uVar7 == 0) {
    return param_1;
  }
  uVar8 = param_2 >> 0x14;
  uVar3 = uVar8 & 0x7ff;
  iVar4 = uVar3 - ((uVar9 & 0x7fffffff) >> 0x14);
  if (iVar4 < 0x40) {
    uVar9 = uVar9 & 0xfffff | 0x100000;
    if (iVar2 != 0) {
      bVar10 = uVar7 != 0;
      uVar7 = -uVar7;
      uVar9 = -(uint)bVar10 - uVar9;
    }
    uVar11 = FUN_080081d4(uVar7,uVar9,0x40 - iVar4);
    uVar6 = (uint)(uVar11 >> 0x20);
    uVar5 = (uint)uVar11;
    lVar12 = FUN_080086b0(uVar7,uVar9,iVar4);
    lVar12 = lVar12 + CONCAT44(param_2,param_1);
    param_1 = (uint)lVar12;
    uVar7 = (uint)((ulonglong)lVar12 >> 0x20);
    if ((param_2 ^ uVar7) >> 0x14 != 0) {
      if (iVar2 == 0) {
        uVar11 = CONCAT44(uVar6 >> 1 | param_1 * -0x80000000,
                          (uint)((uVar11 & 0x100000000) != 0) << 0x1f | uVar5 >> 1);
        param_1 = (uint)((uVar7 + 0x100000 & 1) != 0) << 0x1f | param_1 >> 1;
      }
      else {
        if (iVar4 < 2) {
          uVar7 = FUN_08008760(param_1,uVar7 + uVar8 * -0x100000 + 0x100000,uVar5,uVar6,0,
                               (uVar8 & 0x800) << 0x14,uVar3);
          return uVar7;
        }
        param_1 = param_1 * 2 | uVar6 >> 0x1f;
        uVar11 = CONCAT44(uVar6 * 2 + (uint)CARRY4(uVar5,uVar5),uVar5 * 2);
      }
    }
  }
  else {
    uVar11 = CONCAT44(-(uint)(1 < (uint)(iVar1 * -2)),iVar1 * 2 + 1);
    param_1 = param_1 + iVar1;
  }
  if (((longlong)uVar11 < 0) &&
     (param_1 = param_1 + 1,
     (uVar11 & 0x7fffffff) == 0 &&
     (int)(uVar11 >> 0x20) * 2 + (uint)CARRY4((uint)uVar11,(uint)uVar11) == 0)) {
    param_1 = param_1 & 0xfffffffe;
  }
  return param_1;
}



// ---------------------------------------------------------------------------
// Function: FUN_08008358 at 0x08008358
// ---------------------------------------------------------------------------

void FUN_08008358(void)

{
  FUN_08008216();
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800835e at 0x0800835e
// ---------------------------------------------------------------------------

void FUN_0800835e(undefined4 param_1,uint param_2)

{
  FUN_08008216(param_1,param_2 ^ 0x80000000);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08008364 at 0x08008364
// ---------------------------------------------------------------------------

void FUN_08008364(uint param_1,uint param_2,uint param_3,uint param_4)

{
  longlong lVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  
  if ((param_1 != 0 || (param_2 & 0x7fffffff) != 0) && (param_3 != 0 || (param_4 & 0x7fffffff) != 0)
     ) {
    uVar6 = (uint)((ulonglong)param_1 * (ulonglong)param_3);
    uVar2 = param_2 & 0xfffff | 0x100000;
    uVar3 = param_4 & 0xfffff | 0x100000;
    uVar4 = param_1 >> 10 | param_2 << 0x16;
    uVar8 = param_3 >> 10 | param_4 << 0x16;
    lVar1 = (ulonglong)uVar4 * (ulonglong)uVar8;
    uVar7 = (uint)lVar1;
    iVar5 = uVar4 * (uVar3 >> 10) + (uVar2 >> 10) * uVar8 + (int)((ulonglong)lVar1 >> 0x20);
    uVar8 = ((param_1 * uVar3 +
             uVar2 * param_3 + (int)((ulonglong)param_1 * (ulonglong)param_3 >> 0x20)) -
            (iVar5 * 0x100000 | uVar7 >> 0xc)) - (uint)(uVar6 < uVar7 * 0x100000);
    uVar4 = param_1 >> 0x1a | uVar2 << 6;
    uVar2 = param_3 >> 0x1a | uVar3 << 6;
    uVar3 = uVar6 + uVar7 * -0x100000 >> 0x14 | uVar8 * 0x1000;
    lVar1 = (ulonglong)uVar4 * (ulonglong)uVar2 +
            (ulonglong)((iVar5 - uVar4 * uVar2) + (uVar8 >> 0x14) + (uint)CARRY4(uVar3,uVar7));
    FUN_08008760((int)lVar1,(int)((ulonglong)lVar1 >> 0x20),uVar6 * 0x1000,uVar3 + uVar7,0,
                 (param_2 ^ param_4) & 0x80000000,
                 ((param_4 & 0x7fffffff) >> 0x14) + ((param_2 & 0x7fffffff) >> 0x14) + -0x3ff);
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08008448 at 0x08008448
// ---------------------------------------------------------------------------

undefined8 FUN_08008448(uint param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  bool bVar10;
  
  if ((param_1 != 0 || (param_2 & 0x7fffffff) != 0) && (param_3 != 0 || (param_4 & 0x7fffffff) != 0)
     ) {
    uVar5 = param_4 & 0xfffff | 0x100000;
    uVar4 = param_2 & 0xfffff | 0x100000;
    iVar7 = ((param_2 & 0x7fffffff) >> 0x14) - ((param_4 & 0x7fffffff) >> 0x14);
    iVar8 = iVar7 + 0x3fd;
    if (uVar5 < uVar4 || uVar4 - uVar5 < (uint)(param_3 <= param_1)) {
      iVar8 = iVar7 + 0x3fe;
    }
    else {
      bVar10 = CARRY4(param_1,param_1);
      param_1 = param_1 * 2;
      uVar4 = uVar4 * 2 + (uint)bVar10;
    }
    if (-1 < iVar8) {
      uVar3 = 0x100000;
      uVar6 = 0;
      uVar9 = 0;
      for (uVar2 = 0; uVar2 != 0 || uVar3 != 0; uVar2 = (uint)(uVar1 != 0) << 0x1f | uVar2 >> 1) {
        if (uVar5 < uVar4 || uVar4 - uVar5 < (uint)(param_3 <= param_1)) {
          bVar10 = param_1 < param_3;
          param_1 = param_1 - param_3;
          uVar4 = (uVar4 - uVar5) - (uint)bVar10;
          uVar6 = uVar6 | uVar2;
          uVar9 = uVar9 | uVar3;
        }
        uVar1 = uVar3 & 1;
        uVar3 = uVar3 >> 1;
        bVar10 = CARRY4(param_1,param_1);
        param_1 = param_1 * 2;
        uVar4 = uVar4 * 2 + (uint)bVar10;
      }
      if (param_1 != 0 || uVar4 != 0) {
        if (param_1 == param_3 && uVar4 == uVar5) {
          param_1 = 0;
          uVar4 = 0x80000000;
        }
        else if (uVar5 < uVar4 || uVar4 - uVar5 < (uint)(param_3 <= param_1)) {
          param_1 = 0xfffffffe;
          uVar4 = 0xffffffff;
        }
        else {
          param_1 = 1;
          uVar4 = 0;
        }
      }
      iVar7 = uVar9 + iVar8 * 0x100000 + ((param_2 ^ param_4) & 0x80000000);
      if ((int)uVar4 < 0) {
        bVar10 = 0xfffffffe < uVar6;
        uVar6 = uVar6 + 1;
        iVar7 = iVar7 + (uint)bVar10;
        if ((param_1 & 0x7fffffff) == 0 && uVar4 * 2 + (uint)CARRY4(param_1,param_1) == 0) {
          uVar6 = uVar6 & 0xfffffffe;
        }
      }
      return CONCAT44(iVar7,uVar6);
    }
  }
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_08008526 at 0x08008526
// ---------------------------------------------------------------------------

void FUN_08008526(uint param_1)

{
  uint uVar1;
  
  uVar1 = (int)param_1 >> 0x1f;
  FUN_08008760((param_1 ^ uVar1) - uVar1,0,0,0,0,uVar1 * -0x80000000,0x433);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08008548 at 0x08008548
// ---------------------------------------------------------------------------

void FUN_08008548(undefined4 param_1)

{
  FUN_08008760(param_1,0,0,0,0,0,0x433);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08008562 at 0x08008562
// ---------------------------------------------------------------------------

int FUN_08008562(int param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = (param_2 & 0x7fffffff) >> 0x14;
  if (uVar1 < 0x3ff) {
    param_1 = 0;
  }
  else {
    if (uVar1 < 0x434) {
      param_1 = FUN_08008690(param_1,param_2 & 0xfffff | 0x100000,-(uVar1 - 0x433));
    }
    else {
      param_1 = param_1 << (uVar1 - 0x433 & 0xff);
    }
    if ((param_2 & 0x80000000) != 0) {
      return -param_1;
    }
  }
  return param_1;
}



// ---------------------------------------------------------------------------
// Function: FUN_080085a0 at 0x080085a0
// ---------------------------------------------------------------------------

int FUN_080085a0(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = (param_2 & 0x7fffffff) >> 0x14;
  if (uVar2 < 0x3ff) {
    return 0;
  }
  if (uVar2 < 0x434) {
    iVar1 = FUN_08008690(param_1,param_2 & 0xfffff | 0x100000,-(uVar2 - 0x433));
    return iVar1;
  }
  return param_1 << (uVar2 - 0x433 & 0xff);
}



// ---------------------------------------------------------------------------
// Function: FUN_080085d2 at 0x080085d2
// ---------------------------------------------------------------------------

undefined8 FUN_080085d2(uint param_1)

{
  if ((param_1 & 0x7fffffff) == 0) {
    return 0;
  }
  return CONCAT44(param_1 & 0x80000000 | (((param_1 & 0x7fffffff) >> 0x17) + 0x380) * 0x100000 |
                  (param_1 & 0x7fffff) >> 3,param_1 << 0x1d);
}



// ---------------------------------------------------------------------------
// Function: FUN_080085f8 at 0x080085f8
// ---------------------------------------------------------------------------

int FUN_080085f8(int param_1,int param_2)

{
  if (-1 < param_2) {
    param_1 = -param_1;
  }
  return param_1;
}



// ---------------------------------------------------------------------------
// Function: FUN_08008628 at 0x08008628
// ---------------------------------------------------------------------------

int FUN_08008628(int param_1,int param_2)

{
  if (-1 < param_2) {
    param_1 = -param_1;
  }
  return param_1;
}



// ---------------------------------------------------------------------------
// Function: FUN_08008658 at 0x08008658
// ---------------------------------------------------------------------------

uint FUN_08008658(uint param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  
  if (param_1 != 0 || (param_2 & 0x7fffffff) != 0) {
    iVar2 = ((param_2 & 0x7fffffff) >> 0x14) - 0x380;
    if (0 < iVar2) {
      uVar1 = (param_1 >> 0x1d | (param_2 & 0xfffff) << 3) + (param_2 & 0x80000000) +
              iVar2 * 0x800000;
      if (-1 < (int)(param_1 * 8)) {
        return uVar1;
      }
      uVar1 = uVar1 + 1;
      if ((param_1 & 0xfffffff) == 0) {
        uVar1 = uVar1 & 0xfffffffe;
      }
      return uVar1;
    }
  }
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_08008690 at 0x08008690
// ---------------------------------------------------------------------------

ulonglong FUN_08008690(uint param_1,uint param_2,uint param_3)

{
  if ((int)param_3 < 0x20) {
    return CONCAT44(param_2 >> (param_3 & 0xff),
                    param_1 >> (param_3 & 0xff) | param_2 << (0x20 - param_3 & 0xff));
  }
  return (ulonglong)(param_2 >> (param_3 - 0x20 & 0xff));
}



// ---------------------------------------------------------------------------
// Function: FUN_080086b0 at 0x080086b0
// ---------------------------------------------------------------------------

undefined8 FUN_080086b0(uint param_1,uint param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  
  if ((int)param_3 < 0x20) {
    iVar2 = (int)param_2 >> (param_3 & 0xff);
    uVar1 = param_1 >> (param_3 & 0xff) | param_2 << (0x20 - param_3 & 0xff);
  }
  else {
    uVar1 = (int)param_2 >> (param_3 - 0x20 & 0xff);
    iVar2 = (int)(param_2 | uVar1) >> 0x1f;
  }
  return CONCAT44(iVar2,uVar1);
}



// ---------------------------------------------------------------------------
// Function: FUN_080086e6 at 0x080086e6
// ---------------------------------------------------------------------------

uint FUN_080086e6(int param_1,uint param_2,int param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = LZCOUNT(param_1);
  uVar1 = param_1 << iVar3;
  if (uVar1 == 0 && param_2 == 0) {
    return uVar1;
  }
  if (param_2 != 0) {
    uVar1 = uVar1 | (uint)(param_2 << iVar3 != 0) | param_2 >> (0x20U - iVar3 & 0xff);
  }
  iVar3 = (param_4 - iVar3) + 7;
  if (iVar3 < 0) {
    return 0;
  }
  uVar2 = (uVar1 >> 8) + iVar3 * 0x800000 + param_3;
  if (-1 < (int)(uVar1 * 0x1000000)) {
    return uVar2;
  }
  uVar2 = uVar2 + 1;
  if ((uVar1 & 0x7f) == 0) {
    uVar2 = uVar2 & 0xfffffffe;
  }
  return uVar2;
}



// ---------------------------------------------------------------------------
// Function: FUN_08008760 at 0x08008760
// ---------------------------------------------------------------------------

ulonglong FUN_08008760(undefined4 param_1,int param_2,int param_3,int param_4,uint param_5,
                      int param_6,int param_7)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  ulonglong uVar5;
  undefined8 uVar6;
  longlong lVar7;
  
  if (param_2 == 0) {
    iVar2 = LZCOUNT(param_1) + 0x20;
  }
  else {
    iVar2 = LZCOUNT(param_2);
  }
  uVar5 = FUN_080081d4();
  uVar3 = (uint)(uVar5 >> 0x20);
  if (((uint)uVar5 != 0 || param_3 != 0) || (uVar3 != 0 || param_4 != 0)) {
    if (param_3 != 0 || param_4 != 0) {
      uVar6 = FUN_08008690(param_3,param_4,0x40 - iVar2);
      lVar7 = FUN_080081d4(param_3,param_4,iVar2);
      uVar5 = CONCAT44(uVar3 | (uint)((ulonglong)uVar6 >> 0x20),
                       (uint)uVar5 | (uint)uVar6 | (uint)(lVar7 != 0));
    }
    uVar3 = (uint)(uVar5 >> 0xb);
    iVar2 = (param_7 - iVar2) + 10;
    if (-1 < iVar2) {
      uVar1 = uVar3 + param_5;
      iVar2 = iVar2 * 0x100000 + (int)((uVar5 >> 0xb) >> 0x20) + param_6 +
              (uint)CARRY4(uVar3,param_5);
      if ((int)uVar5 * 0x200000 < 0) {
        bVar4 = 0xfffffffe < uVar1;
        uVar1 = uVar1 + 1;
        iVar2 = iVar2 + (uint)bVar4;
        if ((uVar5 & 0x3ff) == 0) {
          uVar1 = uVar1 & 0xfffffffe;
        }
      }
      return CONCAT44(iVar2,uVar1);
    }
    uVar5 = 0;
  }
  return uVar5;
}



// ---------------------------------------------------------------------------
// Function: __scatterload at 0x080087fc
// ---------------------------------------------------------------------------

undefined4 __scatterload(void)

{
  undefined4 *puVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte *pbVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  undefined4 *puVar9;
  uint uVar10;
  undefined8 uVar11;
  
  puVar1 = puRam0800881c;
  for (puVar9 = puRam08008818; puVar9 < puVar1; puVar9 = puVar9 + 4) {
    (*(code *)puVar9[3])(*puVar9,puVar9[1],puVar9[2]);
  }
  uVar11 = main();
  pbVar3 = (byte *)uVar11;
  pbVar4 = (byte *)((int)((ulonglong)uVar11 >> 0x20) + 0xd8);
  pbVar5 = pbVar4;
  do {
    uVar10 = (uint)*pbVar3;
    uVar8 = uVar10 & 7;
    pbVar2 = pbVar3 + 1;
    if ((*pbVar3 & 7) == 0) {
      pbVar2 = pbVar3 + 2;
      uVar8 = (uint)pbVar3[1];
    }
    uVar6 = (int)uVar10 >> 4;
    if (uVar6 == 0) {
      uVar6 = (uint)*pbVar2;
      pbVar2 = pbVar2 + 1;
    }
    while (uVar8 = uVar8 - 1, uVar8 != 0) {
      *pbVar5 = *pbVar2;
      pbVar2 = pbVar2 + 1;
      pbVar5 = pbVar5 + 1;
    }
    if ((int)(uVar10 << 0x1c) < 0) {
      pbVar3 = pbVar2 + 1;
      iVar7 = uVar6 + 2;
      pbVar2 = pbVar5 + -(uint)*pbVar2;
      while (iVar7 = iVar7 + -1, -1 < iVar7) {
        *pbVar5 = *pbVar2;
        pbVar5 = pbVar5 + 1;
        pbVar2 = pbVar2 + 1;
      }
    }
    else {
      while (uVar6 = uVar6 - 1, pbVar3 = pbVar2, -1 < (int)uVar6) {
        *pbVar5 = 0;
        pbVar5 = pbVar5 + 1;
      }
    }
  } while (pbVar5 < pbVar4);
  return 0;
}



// ---------------------------------------------------------------------------
// Function: __decompress_keil at 0x08008820
// ---------------------------------------------------------------------------

undefined4 __decompress_keil(byte *param_1,byte *param_2,int param_3)

{
  byte *pbVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  uint uVar6;
  
  pbVar5 = param_2 + param_3;
  do {
    uVar6 = (uint)*param_1;
    uVar4 = uVar6 & 7;
    pbVar1 = param_1 + 1;
    if ((*param_1 & 7) == 0) {
      pbVar1 = param_1 + 2;
      uVar4 = (uint)param_1[1];
    }
    uVar2 = (int)uVar6 >> 4;
    if (uVar2 == 0) {
      uVar2 = (uint)*pbVar1;
      pbVar1 = pbVar1 + 1;
    }
    while (uVar4 = uVar4 - 1, uVar4 != 0) {
      *param_2 = *pbVar1;
      pbVar1 = pbVar1 + 1;
      param_2 = param_2 + 1;
    }
    if ((int)(uVar6 << 0x1c) < 0) {
      param_1 = pbVar1 + 1;
      iVar3 = uVar2 + 2;
      pbVar1 = param_2 + -(uint)*pbVar1;
      while (iVar3 = iVar3 + -1, -1 < iVar3) {
        *param_2 = *pbVar1;
        param_2 = param_2 + 1;
        pbVar1 = pbVar1 + 1;
      }
    }
    else {
      while (uVar2 = uVar2 - 1, param_1 = pbVar1, -1 < (int)uVar2) {
        *param_2 = 0;
        param_2 = param_2 + 1;
      }
    }
  } while (param_2 < pbVar5);
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_08008876 at 0x08008876
// ---------------------------------------------------------------------------

void FUN_08008876(int param_1,uint param_2)

{
  if (param_1 == 0) {
    FUN_08017bc8(0x100,0);
  }
  else {
    FUN_08017bc8(param_2,1);
    param_2 = 0;
  }
  *(uint *)(DAT_08017bc4 + 0x2c) = *(uint *)(DAT_08017bc4 + 0x2c) & 0xfffffff0 | param_2;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800889c at 0x0800889c
// ---------------------------------------------------------------------------

void FUN_0800889c(int param_1,int param_2)

{
  uint uVar1;
  
  if (param_2 == 0) {
    uVar1 = *(uint *)(param_1 + 8) & 0xfffffffe;
  }
  else {
    uVar1 = *(uint *)(param_1 + 8) | 1;
  }
  *(uint *)(param_1 + 8) = uVar1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080088b0 at 0x080088b0
// ---------------------------------------------------------------------------

bool FUN_080088b0(int param_1)

{
  return *(int *)(param_1 + 8) << 0x1d < 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_080088be at 0x080088be
// ---------------------------------------------------------------------------

bool FUN_080088be(int param_1,uint param_2)

{
  return (*(uint *)(param_1 + 0x58) & param_2) != 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_080088cc at 0x080088cc
// ---------------------------------------------------------------------------

void FUN_080088cc(int param_1,uint *param_2)

{
  *(uint *)(param_1 + 4) =
       *param_2 | *(uint *)(param_1 + 4) & DAT_0800890c | (uint)(byte)param_2[1] << 8;
  *(uint *)(param_1 + 8) =
       param_2[3] | param_2[2] |
       *(uint *)(param_1 + 8) & DAT_08008910 | (uint)*(byte *)((int)param_2 + 5) << 1;
  *(uint *)(param_1 + 0x2c) =
       *(uint *)(param_1 + 0x2c) & 0xff0fffff | (uint)(byte)((char)param_2[4] - 1) << 0x14;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08008914 at 0x08008914
// ---------------------------------------------------------------------------

void FUN_08008914(int param_1)

{
  int iVar1;
  undefined4 local_20;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined4 local_18;
  undefined4 uStack_14;
  undefined1 local_10;
  
  iVar1 = DAT_080089b0;
  if (param_1 == DAT_080089a4) {
    iVar1 = DAT_080089ac >> 0x12;
  }
  else {
    if (param_1 == DAT_080089a8) {
      FUN_08017c68(0x2000);
    }
    else if (param_1 == DAT_080089ac) {
      iVar1 = 0x4000;
      goto LAB_08008942;
    }
    if (param_1 != iVar1) goto LAB_08008952;
    iVar1 = 0x8000;
  }
LAB_08008942:
  FUN_08017c68(iVar1,1);
LAB_08008952:
  FUN_08008876(0);
  local_18 = 0xe0000;
  uStack_14 = 0;
  local_1c = 0;
  local_20 = 0;
  local_1b = 0;
  local_10 = 1;
  FUN_080088cc(param_1,&local_20);
  FUN_0800889c(param_1,1);
  do {
    iVar1 = FUN_080088be(param_1,0x20);
  } while (iVar1 == 0);
  FUN_080089b4(param_1);
  do {
    iVar1 = FUN_080088b0(param_1);
  } while (iVar1 != 0);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080089b4 at 0x080089b4
// ---------------------------------------------------------------------------

void FUN_080089b4(int param_1)

{
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 4;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080089c0 at 0x080089c0
// ---------------------------------------------------------------------------

uint FUN_080089c0(byte param_1)

{
  uint *puVar1;
  bool bVar2;
  uint local_1c;
  short local_c;
  
  puVar1 = DAT_08008ae4;
  if (param_1 >> 4 != 1) {
    if (param_1 >> 4 == 2) {
      puVar1 = DAT_08008ae8;
    }
    else if (param_1 >> 4 == 3) {
      puVar1 = DAT_08008aec;
    }
    else if (param_1 >> 4 == 4) {
      puVar1 = DAT_08008af0;
    }
  }
  param_1 = param_1 & 0xf;
  if ((puVar1[2] & 1) == 0) {
    puVar1[2] = puVar1[2] | 1;
  }
  if (param_1 == 0x12) {
    puVar1[0x17] = puVar1[0x17] & 0xfffffff8;
  }
  else if (param_1 < 10) {
    puVar1[4] = puVar1[4] & ~(7 << param_1 * '\x03');
  }
  else {
    puVar1[3] = puVar1[3] & ~(7 << ((param_1 - 10) * 3 & 0xff));
  }
  puVar1[0xd] = puVar1[0xd] & 0xffffffe0 | (uint)param_1;
  puVar1[2] = puVar1[2] | 0x500000;
  local_c = 0xfff;
  do {
    if ((int)(*puVar1 << 0x1e) < 0) break;
    bVar2 = local_c != 0;
    local_c = local_c + -1;
  } while (bVar2);
  *puVar1 = *puVar1 & 0xffffffed;
  local_1c = puVar1[0x13] & 0xffff;
  return local_1c;
}



// ---------------------------------------------------------------------------
// Function: FUN_08008af4 at 0x08008af4
// ---------------------------------------------------------------------------

void FUN_08008af4(undefined4 param_1,uint param_2,uint param_3,uint param_4)

{
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  int iVar8;
  ushort *puVar9;
  ushort *puVar10;
  ushort *puVar11;
  char cVar12;
  uint uVar13;
  uint unaff_r4;
  byte bVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  
  iVar8 = DAT_08008c30;
  pcVar7 = DAT_08008c2c;
  pcVar6 = DAT_08008c28;
  pcVar5 = DAT_08008c20;
  if (*(char *)(DAT_08008c1c + 0x3f) != '\x01') {
    return;
  }
  if (*DAT_08008c20 != '\0') {
    return;
  }
  if (*DAT_08008c24 == '\0') {
    if (*(ushort *)(DAT_08008c30 + 0x20) < 0x14) {
      return;
    }
    *(undefined2 *)(DAT_08008c30 + 0x20) = 0;
    if ((*pcVar6 == '\x01') && (*pcVar7 == '\0')) {
      param_2 = *(uint *)(iVar8 + 8);
      goto LAB_08008b98;
    }
    param_2 = *(uint *)(iVar8 + 8);
  }
  else {
    if (*(ushort *)(DAT_08008c30 + 0x20) < 0x32) {
      return;
    }
    *(undefined2 *)(DAT_08008c30 + 0x20) = 0;
    puVar11 = DAT_08008c3c;
    puVar10 = DAT_08008c38;
    puVar9 = DAT_08008c34;
    if ((*pcVar6 == '\x01') && (*pcVar7 == '\0')) {
      param_2 = *(uint *)(iVar8 + 8);
      if ((*(uint *)(iVar8 + 8) & (uint)*DAT_08008c38) == 0) {
        uVar13 = param_2 & *DAT_08008c3c;
        param_2 = *(uint *)(iVar8 + 8);
        if (uVar13 == 0) {
          uVar13 = (uint)*DAT_08008c34;
        }
        else {
          uVar13 = (uint)*DAT_08008c3c;
        }
      }
      else {
        uVar13 = (uint)*DAT_08008c38;
      }
      param_2 = param_2 & uVar13;
LAB_08008b98:
      if (param_2 == 0) {
        return;
      }
    }
    else {
      pcVar5[0xc] = pcVar5[0xc] + '\x01';
      uVar2 = (ushort)*(undefined4 *)(iVar8 + 8) & *puVar10;
      uVar3 = (ushort)*(undefined4 *)(iVar8 + 8) & *puVar11;
      param_3 = CONCAT22(uVar3,uVar2);
      uVar4 = (ushort)*(undefined4 *)(iVar8 + 8) & *puVar9;
      param_4 = CONCAT22((short)(param_4 >> 0x10),uVar4);
      if (pcVar5[0xc] == '\x01') {
        if (uVar2 == 0) {
          pcVar5[0xc] = pcVar5[0xc] + '\x01';
        }
        else {
          param_2 = (uint)uVar2;
        }
      }
      if (pcVar5[0xc] == '\x02') {
        if (uVar3 == 0) {
          pcVar5[0xc] = pcVar5[0xc] + '\x01';
        }
        else {
          param_2 = (uint)uVar3;
        }
      }
      if ((byte)pcVar5[0xc] < 3) goto LAB_08008b9e;
      if (uVar4 == 0) {
        if (uVar2 == 0) {
          if (uVar3 == 0) {
            param_2 = 0;
            goto LAB_08008c0e;
          }
          cVar12 = '\x02';
        }
        else {
          cVar12 = '\x01';
          uVar3 = uVar2;
        }
        param_2 = (uint)uVar3;
        pcVar5[0xc] = cVar12;
      }
      else {
        param_2 = (uint)uVar4;
LAB_08008c0e:
        pcVar5[0xc] = '\0';
      }
    }
  }
LAB_08008b9e:
  uVar13 = param_4 & 0xffffff00;
  uVar17 = unaff_r4 & 0xffffff00;
  if (*DAT_08009bd4 == 0x464) {
    FUN_08012720(0x69,param_2 & 0xff,1,param_4,param_2 & 0xffffff00,param_3 & 0xffffff00,uVar13,
                 uVar17);
    FUN_08012720(0x68,(param_2 & 0xffff) >> 8,1);
    uVar13 = (param_2 & 0xffffff) >> 0x10;
  }
  else {
    bVar1 = (byte)(param_2 >> 8);
    if (*DAT_08009bd4 == 0x45d) {
      FUN_08012720(0x69,param_2 & 0xff,1,param_4,param_2 & 0xffffff00,param_3 & 0xffffff00,uVar13,
                   uVar17);
      uVar17 = (uint)bVar1;
      bVar14 = bVar1 & 3;
      if ((int)((uint)bVar1 << 0x1d) < 0) {
        bVar14 = bVar14 | 8;
      }
      if ((int)((uint)bVar1 << 0x1c) < 0) {
        bVar14 = bVar14 | 0x20;
      }
      if ((int)((uint)bVar1 << 0x1b) < 0) {
        bVar14 = bVar14 | 0x80;
      }
      FUN_08012720(0x68,bVar14,1);
      uVar13 = 0;
      if ((int)(uVar17 << 0x1a) < 0) {
        uVar13 = 2;
      }
      if ((int)(uVar17 << 0x19) < 0) {
        uVar13 = uVar13 | 8;
      }
      if ((int)(uVar17 << 0x18) < 0) {
        uVar13 = uVar13 | 0x20;
      }
      if ((param_2 & 0x10000) == 0) goto LAB_08009bc6;
    }
    else {
      uVar16 = param_2 & 0xff;
      uVar15 = param_2 & 0xffffff0f;
      if ((int)(param_2 << 0x1b) < 0) {
        uVar15 = uVar15 | 0x20;
      }
      if ((int)(param_2 << 0x1a) < 0) {
        uVar15 = uVar15 | 0x80;
      }
      FUN_08012720(0x69,uVar15 & 0xff,1,param_4,uVar15,uVar16,uVar13,uVar17);
      uVar17 = (uint)bVar1;
      uVar13 = 0;
      if ((int)(uVar16 << 0x19) < 0) {
        uVar13 = 2;
      }
      if ((int)(uVar16 << 0x18) < 0) {
        uVar13 = uVar13 | 8;
      }
      if ((param_2 & 0x100) != 0) {
        uVar13 = uVar13 | 0x20;
      }
      if ((int)((uint)bVar1 << 0x1e) < 0) {
        uVar13 = uVar13 | 0x80;
      }
      FUN_08012720(0x68,uVar13,1);
      uVar13 = 0;
      if ((int)(uVar17 << 0x1d) < 0) {
        uVar13 = 2;
      }
      if ((int)(uVar17 << 0x1c) < 0) {
        uVar13 = uVar13 | 8;
      }
      if ((int)(uVar17 << 0x1b) < 0) {
        uVar13 = uVar13 | 0x20;
      }
      if (-1 < (int)(uVar17 << 0x1a)) goto LAB_08009bc6;
    }
    uVar13 = uVar13 | 0x80;
  }
LAB_08009bc6:
  FUN_08012720(0x67,uVar13,1);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08008c40 at 0x08008c40
// ---------------------------------------------------------------------------

void FUN_08008c40(void)

{
  *DAT_08008c54 = 0;
  if (*DAT_08008c58 == '\0') {
    FUN_08012720(0x67,0,1);
    FUN_08012720(0x68,0,1);
    FUN_08012720(0x69,0,1);
    return;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: thunk_FUN_0800cd3c at 0x08008c5c
// ---------------------------------------------------------------------------

longlong thunk_FUN_0800cd3c(undefined4 param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uStack_18;
  uint uStack_14;
  uint uStack_10;
  
  uStack_18 = param_2 & 0xffffff00;
  uStack_10 = param_4 & 0xffffff00;
  uStack_14 = param_3;
  iVar1 = FUN_080122f0(0x51,&uStack_18,1);
  uVar2 = 0;
  if (iVar1 != 0) {
    if ((~(uStack_18 & 0xff) & 3) == 0) {
      uStack_14 = uStack_14 & 0xffffff00;
      while ((byte)uStack_14 < 10) {
        FUN_08012720(0x51,uStack_18 & 0xfc,1);
        FUN_0800db18(5);
        iVar1 = FUN_080122f0(0x51,&uStack_18,1);
        if ((iVar1 != 0) && ((uStack_18 & 3) == 0)) break;
        uStack_14 = CONCAT31(uStack_14._1_3_,(byte)uStack_14 + '\x01');
      }
      if ((byte)uStack_14 == '\n') {
        return (ulonglong)uStack_18 << 0x20;
      }
    }
    uVar2 = 1;
  }
  return CONCAT44(uStack_18,uVar2);
}



// ---------------------------------------------------------------------------
// Function: thunk_FUN_0800cdb4 at 0x08008c60
// ---------------------------------------------------------------------------

longlong thunk_FUN_0800cdb4(undefined4 param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  uint uStack_18;
  uint uStack_14;
  uint uStack_10;
  
  uStack_18 = param_2 & 0xffffff00;
  uStack_14 = param_3 & 0xffffff00;
  uStack_10 = param_4;
  iVar3 = FUN_080122f0(6,&uStack_18,1);
  uVar4 = 0;
  if (iVar3 != 0) {
    if ((uStack_18 & 1) == 0) {
      FUN_080122f0(0,&uStack_14,1);
      if ((uStack_14 & 0x4a) != 0) {
        bVar2 = (byte)uStack_14 & ~((byte)uStack_14 & 0x4a);
        uStack_14 = CONCAT31(uStack_14._1_3_,bVar2);
        FUN_08012720(0,bVar2);
      }
      uStack_10 = uStack_10 & 0xffffff00;
      while ((byte)uStack_10 < 10) {
        iVar3 = FUN_080122f0(0x51,&uStack_18,1);
        uVar1 = uStack_18;
        if (iVar3 != 0) {
          uStack_18 = uStack_18 & 0xffffff9c;
          FUN_08012720(0x51,uVar1 & 0x9c | 3,1);
        }
        FUN_0800db18(5);
        iVar3 = FUN_080122f0(6,&uStack_18,1);
        if ((iVar3 != 0) && ((uStack_18 & 1) != 0)) break;
        uStack_10 = CONCAT31(uStack_10._1_3_,(byte)uStack_10 + '\x01');
      }
      if ((byte)uStack_10 == '\n') {
        return (ulonglong)uStack_18 << 0x20;
      }
    }
    uVar4 = 1;
  }
  return CONCAT44(uStack_18,uVar4);
}



// ---------------------------------------------------------------------------
// Function: thunk_FUN_0800ce70 at 0x08008c64
// ---------------------------------------------------------------------------

longlong thunk_FUN_0800ce70(undefined4 param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uStack_18;
  uint uStack_14;
  uint uStack_10;
  
  uStack_18 = param_2 & 0xffffff00;
  uStack_10 = param_4 & 0xffffff00;
  uStack_14 = param_3;
  iVar1 = FUN_080122f0(0x51,&uStack_18,1);
  uVar2 = 0;
  if (iVar1 != 0) {
    if ((uStack_18 & 0xf) >> 2 == 3) {
      uStack_14 = uStack_14 & 0xffffff00;
      while ((byte)uStack_14 < 10) {
        FUN_08012720(0x51,uStack_18 & 0xf3,1);
        FUN_0800db18(5);
        iVar1 = FUN_080122f0(0x51,&uStack_18,1);
        if ((iVar1 != 0) && ((uStack_18 & 0xc) == 0)) break;
        uStack_14 = CONCAT31(uStack_14._1_3_,(byte)uStack_14 + '\x01');
      }
      if ((byte)uStack_14 == '\n') {
        return (ulonglong)uStack_18 << 0x20;
      }
    }
    uVar2 = 1;
  }
  return CONCAT44(uStack_18,uVar2);
}



// ---------------------------------------------------------------------------
// Function: thunk_FUN_0800ceec at 0x08008c68
// ---------------------------------------------------------------------------

longlong thunk_FUN_0800ceec(undefined4 param_1,uint param_2,uint param_3,uint param_4)

{
  char *pcVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  uint uStack_18;
  uint uStack_14;
  uint uStack_10;
  
  uStack_18 = param_2 & 0xffffff00;
  uStack_14 = param_3 & 0xffffff00;
  uStack_10 = param_4;
  iVar3 = FUN_080122f0(6,&uStack_18,1);
  uVar4 = 0;
  if (iVar3 != 0) {
    if (-1 < (int)(uStack_18 << 0x1e)) {
      FUN_080122f0(0,&uStack_14,1);
      if ((uStack_14 & 0x35) != 0) {
        bVar2 = (byte)uStack_14 & ~((byte)uStack_14 & 0x35);
        uStack_14 = CONCAT31(uStack_14._1_3_,bVar2);
        FUN_08012720(0,bVar2);
      }
      pcVar1 = DAT_0800cfbc;
      uStack_10 = uStack_10 & 0xffffff00;
      while ((byte)uStack_10 < 10) {
        iVar3 = FUN_080122f0(0x51,&uStack_18,1);
        if (iVar3 != 0) {
          uStack_18 = uStack_18 & 0xffffff83;
          if (*pcVar1 == '\0') {
            uStack_18 = uStack_18 | 0x10;
          }
          FUN_08012720(0x51,uStack_18 & 0xff | 0xc,1);
        }
        FUN_0800db18(5);
        iVar3 = FUN_080122f0(6,&uStack_18,1);
        if ((iVar3 != 0) && ((int)(uStack_18 << 0x1e) < 0)) break;
        uStack_10 = CONCAT31(uStack_10._1_3_,(byte)uStack_10 + '\x01');
      }
      if ((byte)uStack_10 == '\n') {
        return (ulonglong)uStack_18 << 0x20;
      }
    }
    uVar4 = 1;
  }
  return CONCAT44(uStack_18,uVar4);
}



// ---------------------------------------------------------------------------
// Function: FUN_08008c6c at 0x08008c6c
// ---------------------------------------------------------------------------

void FUN_08008c6c(void)

{
  char *pcVar1;
  undefined4 uVar2;
  int iVar3;
  char cVar4;
  
  uVar2 = DAT_08008d34;
  pcVar1 = DAT_08008d30;
  if (*(char *)(DAT_08008d2c + 0x3e) == '\0') {
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    *(undefined4 *)(pcVar1 + 0x14) = uVar2;
    *(undefined4 *)(pcVar1 + 0x18) = uVar2;
  }
  else if (*DAT_08008d30 != '\0') {
    *DAT_08008d30 = '\0';
    cVar4 = FUN_08018574(pcVar1 + 0x14);
    *(float *)(pcVar1 + 0x18) = *(float *)(pcVar1 + 0x18) + *(float *)(pcVar1 + 0x14);
    *(short *)(pcVar1 + 2) = *(short *)(pcVar1 + 2) + 1;
    iVar3 = DAT_08008d38;
    if (9 < *(ushort *)(pcVar1 + 2)) {
      *(float *)(pcVar1 + 0x18) = *(float *)(pcVar1 + 0x18) / 10.0;
      if (0.0 <= *(float *)(pcVar1 + 0x18)) {
        *(float *)(iVar3 + 0x14) = *(float *)(pcVar1 + 0x18);
        *(undefined4 *)(iVar3 + 0x10) = uVar2;
      }
      else {
        *(float *)(iVar3 + 0x10) = -*(float *)(pcVar1 + 0x18);
        *(undefined4 *)(iVar3 + 0x14) = uVar2;
      }
      pcVar1[2] = '\0';
      pcVar1[3] = '\0';
      *(undefined4 *)(pcVar1 + 0x18) = uVar2;
      if (cVar4 == '\x01') {
        FUN_08018bf0(DAT_08008d38 + 0x14);
      }
      FUN_0800b460();
      return;
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: thunk_FUN_080098f8 at 0x08008d3c
// ---------------------------------------------------------------------------

void thunk_FUN_080098f8(void)

{
  FUN_08012720(1,0xf,0);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08008d40 at 0x08008d40
// ---------------------------------------------------------------------------

void FUN_08008d40(void)

{
  char *pcVar1;
  char *pcVar2;
  byte *pbVar3;
  byte *pbVar4;
  ushort uVar5;
  int iVar6;
  uint in_r3;
  uint local_20;
  
  pcVar1 = DAT_08009010;
  local_20 = in_r3 & 0xffff0000;
  if ((*DAT_08009010 == '\0') &&
     (iVar6 = FUN_08009c64(&local_20), pbVar3 = DAT_08009018, pcVar2 = DAT_08009014, iVar6 != 0)) {
    if ((local_20 & 1) == 0) {
      pcVar1[1] = '\0';
    }
    else {
      pcVar1[1] = '\x01';
      if ((-1 < (int)((uint)pbVar3[0x39] << 0x1e)) || (*pcVar2 != '\0')) {
        pbVar3[0x39] = pbVar3[0x39] | 2;
        *pcVar2 = '\0';
        if ((int)(local_20 << 0x1d) < 0) {
          *DAT_0800901c = 1;
        }
        else {
          *DAT_0800901c = 2;
        }
        FUN_0800c8f4();
        uVar5 = (ushort)local_20 & ~((ushort)local_20 & 0x14);
        local_20 = CONCAT22(local_20._2_2_,uVar5);
        FUN_08012720(0,(char)uVar5);
        FUN_08019844(10,8);
        FUN_080196d0(0x1e0);
      }
    }
    if ((int)(local_20 << 0x1e) < 0) {
      pcVar1[6] = '\x01';
      if (-1 < (int)((uint)pbVar3[0x39] << 0x1d)) {
        pbVar3[0x39] = pbVar3[0x39] | 4;
        FUN_0800ac9c();
        uVar5 = (ushort)local_20 & ~((ushort)local_20 & 10);
        local_20 = CONCAT22(local_20._2_2_,uVar5);
        FUN_08012720(0,(char)uVar5);
        FUN_08019844(9);
        FUN_080196d0(0x1dc);
      }
    }
    else {
      pcVar1[6] = '\0';
    }
    if ((int)(local_20 << 0x1d) < 0) {
      pcVar1[2] = '\x01';
      if ((pbVar3[0x39] & 1) == 0) {
        pbVar3[0x39] = pbVar3[0x39] & 0xfd;
        pbVar3[0x39] = pbVar3[0x39] | 1;
        *pcVar2 = '\0';
        FUN_0800c8f4();
        uVar5 = (ushort)local_20 & ~((ushort)local_20 & 1);
        local_20 = CONCAT22(local_20._2_2_,uVar5);
        FUN_08012720(0,(char)uVar5);
        FUN_08019844(0xb,8);
        FUN_080196d0(0x1e2);
      }
    }
    else {
      pcVar1[2] = '\0';
    }
    if ((int)(local_20 << 0x1c) < 0) {
      pcVar1[3] = '\x01';
      if (pbVar3[0x12] == 0) {
        pbVar3[0x12] = pbVar3[0x12] | 1;
        FUN_0800ac9c();
        FUN_08019844(1,9);
        FUN_080196d0(0x1d8);
      }
    }
    else {
      pcVar1[3] = '\0';
    }
    pbVar4 = DAT_08009020;
    if ((int)(local_20 << 0x1b) < 0) {
      pcVar1[4] = '\x01';
      if (pbVar3[0x1b] == 0) {
        pbVar3[0x1b] = pbVar3[0x1b] | 1;
        FUN_0800c8f4();
        FUN_08019844(3,8);
        FUN_080196d0(0x1da);
      }
      *pbVar4 = *pbVar4 | 1;
    }
    else {
      *DAT_08009020 = *DAT_08009020 & 0xfe;
      pcVar1[4] = '\0';
    }
    if ((int)(local_20 << 0x1a) < 0) {
      pcVar1[5] = '\x01';
      if ((*pbVar3 & 0x11) == 0) {
        FUN_08019844(0xf,9);
        FUN_080196d0(0x1c4);
      }
      *pbVar3 = *pbVar3 | 0x11;
      FUN_0800ac9c();
    }
    else {
      pcVar1[5] = '\0';
    }
    if ((int)(local_20 << 0x19) < 0) {
      pcVar1[7] = '\x01';
      if ((*pbVar3 & 0x21) == 0) {
        FUN_08019844(0xf,9);
        FUN_080196d0(0x1c6);
      }
      *pbVar3 = *pbVar3 | 0x21;
      FUN_0800ac9c();
    }
    else {
      pcVar1[7] = '\0';
    }
    if ((int)(local_20 << 0x18) < 0) {
      pcVar1[8] = '\x01';
      if ((*pbVar3 & 0x12) == 0) {
        FUN_08019844(0x10,8);
        FUN_080196d0(0x1c8);
      }
      *pbVar3 = *pbVar3 | 0x12;
      FUN_0800c8f4();
    }
    else {
      pcVar1[8] = '\0';
    }
    if ((int)(local_20 << 0x17) < 0) {
      pcVar1[9] = '\x01';
      if ((*pbVar3 & 0x22) == 0) {
        FUN_08019844(0x10,8);
        FUN_080196d0(0x1ca);
      }
      *pbVar3 = *pbVar3 | 0x22;
      FUN_0800c8f4();
    }
    else {
      pcVar1[9] = '\0';
    }
    if ((int)(local_20 << 0x11) < 0) {
      if (pbVar3[0x4c] == 0) {
        thunk_FUN_0800ce70();
      }
    }
    else {
      pbVar3[0x4c] = 0;
    }
    if ((int)(local_20 << 0x10) < 0) {
      if (pbVar3[0x4d] == 0) {
        thunk_FUN_0800cd3c();
      }
    }
    else {
      pbVar3[0x4d] = 0;
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08009024 at 0x08009024
// ---------------------------------------------------------------------------

void FUN_08009024(void)

{
  int iVar1;
  
  iVar1 = DAT_080090a4;
  if (*(char *)(DAT_080090a4 + 1) == '\0') {
    if (*DAT_080090a8 * 0x10000 < 0) {
      *(undefined1 *)(DAT_080090a4 + 0x1e) = 0;
      return;
    }
    *(undefined1 *)(DAT_080090a4 + 0x1f) = 0;
    *(char *)(iVar1 + 0x1e) = *(char *)(iVar1 + 0x1e) + '\x01';
    if (4 < *(byte *)(iVar1 + 0x1e)) {
      *(undefined1 *)(iVar1 + 0x1e) = 0;
      *(undefined1 *)(iVar1 + 1) = 1;
      FUN_08019844(0,0xa0);
      *DAT_080090ac = 1;
      *DAT_080090b0 = 0;
      if ((*(char *)(iVar1 + 2) == '\0') && (*DAT_080090b4 == '\0')) {
        *DAT_080090b8 = 0;
      }
      FUN_08015efc();
      *DAT_080090bc = 0;
      *DAT_080090c0 = 0;
    }
  }
  else {
    if (-1 < *DAT_080090a8 * 0x10000) {
      *(undefined1 *)(DAT_080090a4 + 0x1f) = 0;
      return;
    }
    *(undefined1 *)(DAT_080090a4 + 0x1e) = 0;
    *(char *)(iVar1 + 0x1f) = *(char *)(iVar1 + 0x1f) + '\x01';
    if (4 < *(byte *)(iVar1 + 0x1f)) {
      *(undefined1 *)(iVar1 + 0x1f) = 0;
      *(undefined1 *)(iVar1 + 1) = 0;
      FUN_08019844(0,0xa1);
      return;
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080090c4 at 0x080090c4
// ---------------------------------------------------------------------------

void FUN_080090c4(void)

{
  int iVar1;
  int iVar2;
  float fVar3;
  
  fVar3 = DAT_08009140;
  iVar2 = DAT_0800913c;
  iVar1 = DAT_08009138;
  if (*DAT_08009134 != '\x01') {
    if (0.0 < *(float *)(DAT_08009138 + 0x14)) {
      *(float *)(DAT_0800913c + 8) =
           *(float *)(DAT_0800913c + 8) + *(float *)(DAT_08009138 + 0x14) * DAT_08009140;
      *(float *)(iVar2 + 0x10) = *(float *)(iVar2 + 0x10) + *(float *)(iVar1 + 0x14) * fVar3;
    }
    if (0.0 < *(float *)(iVar1 + 0x10)) {
      *(float *)(iVar2 + 0xc) = *(float *)(iVar2 + 0xc) + *(float *)(iVar1 + 0x10) * fVar3;
      *(float *)(iVar2 + 0x14) = *(float *)(iVar2 + 0x14) + *(float *)(iVar1 + 0x10) * fVar3;
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08009144 at 0x08009144
// ---------------------------------------------------------------------------

void FUN_08009144(void)

{
  char *pcVar1;
  float fVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  byte bVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  float fVar13;
  undefined4 uVar14;
  byte local_48;
  float local_44;
  byte local_40;
  float local_3c;
  byte local_38;
  float local_34;
  float local_30;
  
  iVar5 = DAT_08009560;
  pbVar4 = DAT_0800955c;
  iVar3 = DAT_08009558;
  pcVar1 = DAT_08009554;
  fVar2 = DAT_08009550;
  local_30 = DAT_08009550;
  local_34 = DAT_08009550;
  if (*DAT_08009554 == '\0') {
    pcVar1[0x10] = '\0';
    pcVar1[0x11] = '\0';
    iVar8 = FUN_08021870(&local_34,*pbVar4);
    iVar6 = DAT_08009564;
    if (iVar8 != 0) {
      if ((*(char *)(DAT_08009564 + 0x3f) != '\0') || (*(char *)(DAT_08009564 + 0x3d) != '\0')) {
        pcVar1[0x12] = '\0';
        pcVar1[0x13] = '\0';
      }
      pbVar4 = DAT_08009570;
      iVar7 = DAT_0800956c;
      iVar8 = DAT_08009568;
      iVar12 = DAT_0800956c + -0x4cc;
      iVar11 = DAT_0800956c + -0x80;
      for (local_48 = 1; local_48 <= *pbVar4; local_48 = local_48 + 1) {
        if (local_48 == *DAT_08009574) {
          if (*(char *)(iVar6 + 0x3b) == '\0') {
            if (*(char *)(iVar6 + 0x3a) == '\0') goto LAB_0800924e;
            fVar13 = *(float *)(iVar7 + (uint)local_48 * 4) -
                     *(float *)(iVar8 + 0x14) * *DAT_08009578;
          }
          else {
            fVar13 = *(float *)(iVar7 + (uint)local_48 * 4) +
                     *(float *)(iVar8 + 0x10) * *DAT_08009578;
          }
          *(float *)(iVar7 + (uint)local_48 * 4) = fVar13;
        }
LAB_0800924e:
        if (local_48 == *DAT_0800957c) {
          if (*(char *)(iVar6 + 0x3b) == '\0') {
            if (*(char *)(iVar6 + 0x3a) == '\0') goto LAB_080092a8;
            fVar13 = *(float *)(iVar7 + (uint)local_48 * 4) -
                     *(float *)(iVar8 + 0x14) * *DAT_08009580;
          }
          else {
            fVar13 = *(float *)(iVar7 + (uint)local_48 * 4) +
                     *(float *)(iVar8 + 0x10) * *DAT_08009580;
          }
          *(float *)(iVar7 + (uint)local_48 * 4) = fVar13;
        }
LAB_080092a8:
        if (local_48 == *DAT_08009584) {
          if (*(char *)(iVar6 + 0x3b) == '\0') {
            if (*(char *)(iVar6 + 0x3a) == '\0') goto LAB_08009302;
            fVar13 = *(float *)(iVar7 + (uint)local_48 * 4) -
                     *(float *)(iVar8 + 0x14) * *DAT_08009588;
          }
          else {
            fVar13 = *(float *)(iVar7 + (uint)local_48 * 4) +
                     *(float *)(iVar8 + 0x10) * *DAT_08009588;
          }
          *(float *)(iVar7 + (uint)local_48 * 4) = fVar13;
        }
LAB_08009302:
        if (local_48 == *DAT_0800958c) {
          if (*(char *)(iVar6 + 0x3b) == '\0') {
            if (*(char *)(iVar6 + 0x3a) == '\0') goto LAB_08009360;
            fVar13 = *(float *)(iVar7 + (uint)local_48 * 4) -
                     *(float *)(iVar8 + 0x14) * *DAT_08009590;
          }
          else {
            fVar13 = *(float *)(iVar7 + (uint)local_48 * 4) +
                     *(float *)(iVar8 + 0x10) * *DAT_08009590;
          }
          *(float *)(iVar7 + (uint)local_48 * 4) = fVar13;
        }
LAB_08009360:
        if (local_48 == *DAT_08009594) {
          if (*(char *)(iVar6 + 0x3b) == '\0') {
            if (*(char *)(iVar6 + 0x3a) != '\0') {
              *(float *)(iVar7 + (uint)local_48 * 4) =
                   *(float *)(iVar7 + (uint)local_48 * 4) - *(float *)(iVar8 + 0x14) * *DAT_08009598
              ;
            }
          }
          else {
            *(float *)(iVar7 + (uint)local_48 * 4) =
                 *(float *)(iVar7 + (uint)local_48 * 4) + *(float *)(iVar8 + 0x10) * *DAT_08009598;
          }
        }
        *(float *)(iVar11 + (uint)local_48 * 4) =
             *(float *)(iVar7 + (uint)local_48 * 4) / *(float *)(iVar5 + (uint)local_48 * 4);
        uVar14 = *(undefined4 *)(iVar11 + (uint)local_48 * 4);
        if (*(ushort *)(pcVar1 + 0x12) < 5) {
          *(undefined4 *)(iVar5 + (uint)local_48 * 4 + 0x7c) = uVar14;
          pcVar1[10] = '\0';
          uVar14 = *(undefined4 *)(iVar11 + (uint)local_48 * 4);
          uVar10 = (uint)*(ushort *)(pcVar1 + 0x12);
        }
        else {
          uVar10 = (uint)(byte)pcVar1[10];
        }
        *(undefined4 *)(iVar12 + (uint)local_48 * 0x2c + uVar10 * 4) = uVar14;
        local_30 = *(float *)(iVar11 + (uint)local_48 * 4) + local_30;
      }
      if (*(ushort *)(pcVar1 + 0x12) < 5) {
        *(short *)(pcVar1 + 0x12) = *(short *)(pcVar1 + 0x12) + 1;
      }
      else {
        pcVar1[10] = pcVar1[10] + '\x01';
        if (4 < (byte)pcVar1[10]) {
          pcVar1[10] = '\0';
        }
        for (local_48 = 1; local_48 <= *pbVar4; local_48 = local_48 + 1) {
          local_3c = fVar2;
          local_44 = 0.0;
          while (local_44._0_1_ < 10) {
            local_3c = *(float *)(iVar12 + (uint)local_48 * 0x2c + (int)local_44 * 4) + local_3c;
            local_44 = (float)(uint)(byte)(local_44._0_1_ + 1);
          }
          *(float *)(iVar5 + (uint)local_48 * 4 + 0x7c) = local_3c / 5.0;
        }
      }
      *(float *)(iVar5 + 0x114) = local_30;
      iVar5 = DAT_08009638;
      local_44 = *(float *)(iVar7 + -0x7c);
      local_3c = *(float *)(iVar7 + -0x7c);
      local_38 = 1;
      local_40 = 1;
      for (bVar9 = 2; bVar9 <= *pbVar4; bVar9 = bVar9 + 1) {
        if (*(float *)(iVar11 + (uint)bVar9 * 4) < local_44) {
          local_44 = *(float *)(iVar11 + (uint)bVar9 * 4);
          local_38 = bVar9;
        }
        if (local_3c < *(float *)(iVar11 + (uint)bVar9 * 4)) {
          local_3c = *(float *)(iVar11 + (uint)bVar9 * 4);
          local_40 = bVar9;
        }
      }
      *(float *)(iVar3 + 0xc) = local_44;
      *(float *)(iVar5 + 0xc) = local_3c;
      *(ushort *)(iVar3 + 0x10) = (ushort)local_38;
      *(ushort *)(iVar5 + 0x10) = (ushort)local_40;
    }
  }
  else {
    *(short *)(DAT_08009554 + 0x10) = *(short *)(DAT_08009554 + 0x10) + 1;
    if (0x13 < *(ushort *)(pcVar1 + 0x10)) {
      for (local_48 = 1; local_48 <= *pbVar4; local_48 = local_48 + 1) {
        *(float *)(iVar5 + (uint)local_48 * 4 + 0x7c) = fVar2;
      }
      *(float *)(iVar5 + 0x114) = fVar2;
      *(float *)(iVar3 + 0xc) = fVar2;
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800963c at 0x0800963c
// ---------------------------------------------------------------------------

void FUN_0800963c(void)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = DAT_080096bc;
  if (((*(char *)(DAT_080096bc + 5) == '\x02') && (*(char *)(DAT_080096bc + 2) == '\0')) &&
     (*DAT_080096c0 == '\0')) {
    if ((((DAT_080096c4[0x1b] & 3) != 0) || ((int)((uint)*DAT_080096c4 << 0x1e) < 0)) ||
       (((int)((uint)DAT_080096c4[0x51] << 0x1d) < 0 || ((DAT_080096c4[0x10] & 3) != 0)))) {
      if (*DAT_080096c8 == '\x14') {
        pcVar2 = DAT_080096d0;
      }
      else {
        if (*DAT_080096c8 != '\x1d') {
          return;
        }
        pcVar2 = DAT_080096cc;
      }
      if (*pcVar2 == '\0') {
        *(char *)(DAT_080096bc + 0x34) = *(char *)(DAT_080096bc + 0x34) + '\x01';
        if (*(byte *)(iVar1 + 0x34) < 0x1f) {
          return;
        }
        *(undefined1 *)(iVar1 + 0x34) = 0;
      }
      *(undefined1 *)(iVar1 + 0x11) = 1;
      return;
    }
    if (DAT_080096c4[0x3b] == 0) {
      return;
    }
    *(undefined1 *)(DAT_080096bc + 0x11) = 0;
  }
  else {
    *(undefined1 *)(DAT_080096bc + 0x11) = 1;
  }
  *(undefined1 *)(iVar1 + 0x34) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080097a4 at 0x080097a4
// ---------------------------------------------------------------------------

void FUN_080097a4(void)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = DAT_08009884;
  if ((((*(char *)(DAT_08009884 + 5) == '\0') && (*(char *)(DAT_08009884 + 6) == '\0')) &&
      (*(char *)(DAT_08009884 + 7) == '\0')) && (*(char *)(DAT_08009884 + 8) == '\0')) {
    *(undefined4 *)(DAT_08009884 + 0x18) = 0;
LAB_080097da:
    if (*(char *)(iVar1 + 3) == '\0') {
      *(undefined4 *)(iVar1 + 0x20) = 0;
    }
    else {
      *(int *)(iVar1 + 0x20) = *(int *)(iVar1 + 0x20) + 1;
      if (0xe < *(uint *)(iVar1 + 0x20)) {
        *(undefined4 *)(iVar1 + 0x20) = 0;
        FUN_0800b174();
      }
    }
    uVar2 = 0x5460;
    if ((*(char *)(iVar1 + 4) == '\0') && (*(char *)(iVar1 + 0xd) == '\0')) goto LAB_0800981a;
    *(int *)(iVar1 + 0x1c) = *(int *)(iVar1 + 0x1c) + 1;
    if (0x5460 < *(uint *)(iVar1 + 0x1c)) {
      FUN_08019844(0,0x32);
      *(undefined4 *)(iVar1 + 0x1c) = 0;
      goto LAB_08009816;
    }
  }
  else {
    *(int *)(DAT_08009884 + 0x18) = *(int *)(DAT_08009884 + 0x18) + 1;
    if (*(uint *)(iVar1 + 0x18) < 0xfd21) goto LAB_080097da;
    FUN_08019844(0,0x32);
    *(undefined4 *)(iVar1 + 0x18) = 0;
    *(undefined1 *)(iVar1 + 2) = 0;
LAB_08009816:
    uVar2 = FUN_08022f3c();
LAB_0800981a:
    *(undefined4 *)(iVar1 + 0x1c) = 0;
  }
  if (*(char *)(iVar1 + 9) != '\0') {
    *(int *)(iVar1 + 0x24) = *(int *)(iVar1 + 0x24) + 1;
    if (*(uint *)(iVar1 + 0x24) <= uVar2) goto LAB_0800983a;
    FUN_08019844(0,0x32);
    FUN_0800b2a8();
  }
  *(undefined4 *)(iVar1 + 0x24) = 0;
LAB_0800983a:
  if (*(char *)(iVar1 + 10) == '\0') {
    *(undefined4 *)(iVar1 + 0x28) = 0;
  }
  else {
    *(int *)(iVar1 + 0x28) = *(int *)(iVar1 + 0x28) + 1;
    if (0x13 < *(uint *)(iVar1 + 0x28)) {
      *(undefined4 *)(iVar1 + 0x28) = 0;
      FUN_0800b1a4();
    }
  }
  if (*(char *)(iVar1 + 0xb) == '\0') {
    *(undefined4 *)(iVar1 + 0x10) = 0;
  }
  else {
    *(int *)(iVar1 + 0x10) = *(int *)(iVar1 + 0x10) + 1;
    if (3 < *(uint *)(iVar1 + 0x10)) {
      *(undefined4 *)(iVar1 + 0x10) = 0;
      *(undefined1 *)(iVar1 + 0xb) = 0;
      FUN_0800b1a4();
    }
  }
  if ((*(char *)(iVar1 + 0xc) == '\0') ||
     (*(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + 1, 2 < *(uint *)(iVar1 + 0x14))) {
    *(undefined4 *)(iVar1 + 0x14) = 0;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08009888 at 0x08009888
// ---------------------------------------------------------------------------

void FUN_08009888(void)

{
  FUN_08017ce0(1);
  FUN_08017ce0(0);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800989c at 0x0800989c
// ---------------------------------------------------------------------------

undefined2 FUN_0800989c(int param_1)

{
  return *(undefined2 *)(param_1 + DAT_080098a8);
}



// ---------------------------------------------------------------------------
// Function: FUN_080098ac at 0x080098ac
// ---------------------------------------------------------------------------

void FUN_080098ac(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + DAT_080098b8) = param_2;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080098bc at 0x080098bc
// ---------------------------------------------------------------------------

undefined4 FUN_080098bc(void)

{
  return 1;
}



// ---------------------------------------------------------------------------
// Function: thunk_FUN_0800cd3c at 0x080098c0
// ---------------------------------------------------------------------------

longlong thunk_FUN_0800cd3c(undefined4 param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uStack_18;
  uint uStack_14;
  uint uStack_10;
  
  uStack_18 = param_2 & 0xffffff00;
  uStack_10 = param_4 & 0xffffff00;
  uStack_14 = param_3;
  iVar1 = FUN_080122f0(0x51,&uStack_18,1);
  uVar2 = 0;
  if (iVar1 != 0) {
    if ((~(uStack_18 & 0xff) & 3) == 0) {
      uStack_14 = uStack_14 & 0xffffff00;
      while ((byte)uStack_14 < 10) {
        FUN_08012720(0x51,uStack_18 & 0xfc,1);
        FUN_0800db18(5);
        iVar1 = FUN_080122f0(0x51,&uStack_18,1);
        if ((iVar1 != 0) && ((uStack_18 & 3) == 0)) break;
        uStack_14 = CONCAT31(uStack_14._1_3_,(byte)uStack_14 + '\x01');
      }
      if ((byte)uStack_14 == '\n') {
        return (ulonglong)uStack_18 << 0x20;
      }
    }
    uVar2 = 1;
  }
  return CONCAT44(uStack_18,uVar2);
}



// ---------------------------------------------------------------------------
// Function: thunk_FUN_0800cdb4 at 0x080098c4
// ---------------------------------------------------------------------------

longlong thunk_FUN_0800cdb4(undefined4 param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  uint uStack_18;
  uint uStack_14;
  uint uStack_10;
  
  uStack_18 = param_2 & 0xffffff00;
  uStack_14 = param_3 & 0xffffff00;
  uStack_10 = param_4;
  iVar3 = FUN_080122f0(6,&uStack_18,1);
  uVar4 = 0;
  if (iVar3 != 0) {
    if ((uStack_18 & 1) == 0) {
      FUN_080122f0(0,&uStack_14,1);
      if ((uStack_14 & 0x4a) != 0) {
        bVar2 = (byte)uStack_14 & ~((byte)uStack_14 & 0x4a);
        uStack_14 = CONCAT31(uStack_14._1_3_,bVar2);
        FUN_08012720(0,bVar2);
      }
      uStack_10 = uStack_10 & 0xffffff00;
      while ((byte)uStack_10 < 10) {
        iVar3 = FUN_080122f0(0x51,&uStack_18,1);
        uVar1 = uStack_18;
        if (iVar3 != 0) {
          uStack_18 = uStack_18 & 0xffffff9c;
          FUN_08012720(0x51,uVar1 & 0x9c | 3,1);
        }
        FUN_0800db18(5);
        iVar3 = FUN_080122f0(6,&uStack_18,1);
        if ((iVar3 != 0) && ((uStack_18 & 1) != 0)) break;
        uStack_10 = CONCAT31(uStack_10._1_3_,(byte)uStack_10 + '\x01');
      }
      if ((byte)uStack_10 == '\n') {
        return (ulonglong)uStack_18 << 0x20;
      }
    }
    uVar4 = 1;
  }
  return CONCAT44(uStack_18,uVar4);
}



// ---------------------------------------------------------------------------
// Function: thunk_FUN_0800ce70 at 0x080098ec
// ---------------------------------------------------------------------------

longlong thunk_FUN_0800ce70(undefined4 param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uStack_18;
  uint uStack_14;
  uint uStack_10;
  
  uStack_18 = param_2 & 0xffffff00;
  uStack_10 = param_4 & 0xffffff00;
  uStack_14 = param_3;
  iVar1 = FUN_080122f0(0x51,&uStack_18,1);
  uVar2 = 0;
  if (iVar1 != 0) {
    if ((uStack_18 & 0xf) >> 2 == 3) {
      uStack_14 = uStack_14 & 0xffffff00;
      while ((byte)uStack_14 < 10) {
        FUN_08012720(0x51,uStack_18 & 0xf3,1);
        FUN_0800db18(5);
        iVar1 = FUN_080122f0(0x51,&uStack_18,1);
        if ((iVar1 != 0) && ((uStack_18 & 0xc) == 0)) break;
        uStack_14 = CONCAT31(uStack_14._1_3_,(byte)uStack_14 + '\x01');
      }
      if ((byte)uStack_14 == '\n') {
        return (ulonglong)uStack_18 << 0x20;
      }
    }
    uVar2 = 1;
  }
  return CONCAT44(uStack_18,uVar2);
}



// ---------------------------------------------------------------------------
// Function: thunk_FUN_0800ceec at 0x080098f0
// ---------------------------------------------------------------------------

longlong thunk_FUN_0800ceec(undefined4 param_1,uint param_2,uint param_3,uint param_4)

{
  char *pcVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  uint uStack_18;
  uint uStack_14;
  uint uStack_10;
  
  uStack_18 = param_2 & 0xffffff00;
  uStack_14 = param_3 & 0xffffff00;
  uStack_10 = param_4;
  iVar3 = FUN_080122f0(6,&uStack_18,1);
  uVar4 = 0;
  if (iVar3 != 0) {
    if (-1 < (int)(uStack_18 << 0x1e)) {
      FUN_080122f0(0,&uStack_14,1);
      if ((uStack_14 & 0x35) != 0) {
        bVar2 = (byte)uStack_14 & ~((byte)uStack_14 & 0x35);
        uStack_14 = CONCAT31(uStack_14._1_3_,bVar2);
        FUN_08012720(0,bVar2);
      }
      pcVar1 = DAT_0800cfbc;
      uStack_10 = uStack_10 & 0xffffff00;
      while ((byte)uStack_10 < 10) {
        iVar3 = FUN_080122f0(0x51,&uStack_18,1);
        if (iVar3 != 0) {
          uStack_18 = uStack_18 & 0xffffff83;
          if (*pcVar1 == '\0') {
            uStack_18 = uStack_18 | 0x10;
          }
          FUN_08012720(0x51,uStack_18 & 0xff | 0xc,1);
        }
        FUN_0800db18(5);
        iVar3 = FUN_080122f0(6,&uStack_18,1);
        if ((iVar3 != 0) && ((int)(uStack_18 << 0x1e) < 0)) break;
        uStack_10 = CONCAT31(uStack_10._1_3_,(byte)uStack_10 + '\x01');
      }
      if ((byte)uStack_10 == '\n') {
        return (ulonglong)uStack_18 << 0x20;
      }
    }
    uVar4 = 1;
  }
  return CONCAT44(uStack_18,uVar4);
}



// ---------------------------------------------------------------------------
// Function: FUN_080098f4 at 0x080098f4
// ---------------------------------------------------------------------------

undefined4 FUN_080098f4(void)

{
  return 1;
}



// ---------------------------------------------------------------------------
// Function: FUN_080098f8 at 0x080098f8
// ---------------------------------------------------------------------------

void FUN_080098f8(void)

{
  FUN_08012720(1,0xf,0);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08009902 at 0x08009902
// ---------------------------------------------------------------------------

void FUN_08009902(void)

{
  uint in_r3;
  uint local_8;
  
  local_8 = in_r3 & 0xffffff00;
  FUN_080122f0(0x6e,&local_8,1);
  if ((char)local_8 != -0x73) {
    FUN_08012720(0x6e,0x8d,1);
  }
  FUN_08012720(1,0xe,0);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08009934 at 0x08009934
// ---------------------------------------------------------------------------

undefined4 FUN_08009934(void)

{
  int iVar1;
  
  iVar1 = DAT_080099a8;
  FUN_08012720(0x5e,(*(char *)(DAT_080099a8 + 8) + '\x01') * '\x04' | 0x40,1);
  FUN_08012720(0x5f,((*(byte *)(iVar1 + 0x1f) >> 4) + 1) * '\x04' | 0x40,1);
  FUN_08012720(0x60,(*(byte *)(iVar1 + 9) + 1 & 0x3f) << 2,1);
  FUN_08012720(0x61,((*(byte *)(iVar1 + 0x1f) & 0xf) + 1) * '\x04',1);
  FUN_08012720(0x62,(*(char *)(iVar1 + 0x17) + '\x01') * '\x04' | 0x40,1);
  FUN_08012720(99,(*(byte *)(iVar1 + 0x18) + 1 & 0x3f) << 2,1);
  return 1;
}



// ---------------------------------------------------------------------------
// Function: thunk_FUN_0800d5fc at 0x080099ac
// ---------------------------------------------------------------------------

undefined4 thunk_FUN_0800d5fc(void)

{
  char *pcVar1;
  char *pcVar2;
  float *pfVar3;
  float *pfVar4;
  float *pfVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  bool bVar10;
  undefined1 uStack_50;
  undefined1 uStack_4f;
  undefined1 uStack_4e;
  undefined1 uStack_4d;
  undefined1 auStack_4c [3];
  undefined1 uStack_49;
  undefined1 uStack_48;
  undefined1 uStack_47;
  undefined1 uStack_46;
  byte bStack_44;
  byte bStack_43;
  char cStack_42;
  char cStack_41;
  byte bStack_40;
  char cStack_3f;
  undefined1 uStack_3d;
  undefined1 uStack_3c;
  undefined1 uStack_3b;
  undefined1 uStack_3a;
  undefined1 uStack_39;
  undefined1 uStack_38;
  undefined1 uStack_37;
  undefined1 uStack_36;
  undefined1 uStack_35;
  undefined1 uStack_34;
  undefined1 uStack_32;
  byte bStack_31;
  undefined1 uStack_30;
  byte bStack_2f;
  undefined1 uStack_2e;
  undefined1 uStack_2d;
  undefined1 uStack_2c;
  undefined1 uStack_2b;
  undefined1 uStack_2a;
  undefined1 uStack_29;
  byte abStack_28 [4];
  char acStack_24 [4];
  uint uStack_20;
  byte abStack_1c [8];
  
  uStack_20 = 0;
  acStack_24[0] = '\0';
  iVar6 = FUN_080122f0(0x5a,acStack_24,1);
  pcVar1 = DAT_0800d920;
  bVar10 = iVar6 == 0;
LAB_0800d618:
  do {
    do {
      if (bVar10) goto LAB_0800d86c;
      if ((acStack_24[0] != -2) && (*pcVar1 != '\0')) {
        iVar6 = FUN_08012720(1,0xd,0);
        bVar10 = true;
        if (iVar6 == 0) goto LAB_0800d618;
      }
      FUN_0800db18(0xfa);
      iVar6 = FUN_080122f0(0x52,&uStack_50,0x28);
      bVar10 = true;
    } while (iVar6 == 0);
    uStack_50 = 0x9e;
    uStack_4f = 0xff;
    uStack_4e = 0xff;
    iVar6 = FUN_08012760(0x52,&uStack_50,3);
    pfVar5 = DAT_0800d950;
    pfVar4 = DAT_0800d944;
    pfVar3 = DAT_0800d940;
    pcVar2 = DAT_0800d924;
    bVar10 = true;
  } while (iVar6 == 0);
  if (*DAT_0800d924 == '\0') {
    uStack_4d = 0xac;
  }
  else {
    uStack_4d = 0x2c;
  }
  auStack_4c[0] = 0xff;
  uStack_49 = 0xff;
  uStack_48 = 0xff;
  uStack_47 = 0xff;
  uStack_46 = 0xff;
  bStack_44 = (*(char *)(DAT_0800d928 + 8) + '\x01') * '\x04' | 0x40;
  bStack_43 = ((*(byte *)(DAT_0800d928 + 0x1f) >> 4) + 1) * '\x04' | 0x40;
  cStack_42 = (*(char *)(DAT_0800d928 + 9) + '\x01') * '\x04';
  cStack_41 = ((*(byte *)(DAT_0800d928 + 0x1f) & 0xf) + 1) * '\x04';
  bStack_40 = (*(char *)(DAT_0800d928 + 0x17) + '\x01') * '\x04' | 0x40;
  cStack_3f = (*(char *)(DAT_0800d928 + 0x18) + '\x01') * '\x04';
  uStack_3d = 0;
  uStack_3c = 2;
  uStack_3b = 0;
  uStack_3a = 0;
  uStack_39 = 0;
  if (*DAT_0800d92c == 0x464) {
LAB_0800d720:
    uVar7 = DAT_0800d930 >> (0x18 - *DAT_0800d934 & 0xff);
  }
  else {
    if (*DAT_0800d92c == 0x45d) {
      if (*DAT_0800d934 < 0xb) goto LAB_0800d720;
      iVar6 = 0x11 - (uint)*DAT_0800d934;
      uVar7 = DAT_0800d938 + 0x15;
    }
    else {
      iVar6 = 0xe - (uint)*DAT_0800d934;
      uVar7 = DAT_0800d938;
    }
    uVar7 = DAT_0800d930 >> (iVar6 * 2 & 0xffU) & uVar7;
  }
  uVar7 = (~uVar7 & 0xfffff) << 4;
  if (*DAT_0800d924 == '\0') {
    uVar7 = uVar7 | 0xe;
  }
  else {
    uVar7 = uVar7 | 2;
  }
  uStack_38 = (undefined1)(uVar7 >> 0x10);
  uStack_37 = (undefined1)(uVar7 >> 8);
  uStack_36 = (undefined1)uVar7;
  uStack_35 = 0x28;
  uStack_34 = 0xcd;
  if (*DAT_0800d93c == '\x01') {
    *DAT_0800d940 = *DAT_0800d948 + DAT_0800d94c;
    *pfVar4 = *pfVar5 - DAT_0800d954;
  }
  uVar7 = VectorFloatToUnsigned(*pfVar3 * DAT_0800d958 - DAT_0800d95c,3);
  uStack_32 = (undefined1)(uVar7 >> 4);
  bStack_31 = (byte)(uVar7 << 4) | 0xb;
  uStack_20 = VectorFloatToUnsigned(*pfVar4 * DAT_0800d958,3);
  uStack_30 = (undefined1)(uStack_20 >> 4);
  bStack_2f = (byte)(uStack_20 << 4) | 0xb;
  uStack_2d = 0x49;
  uStack_2e = 0x49;
  if (*pcVar2 == '\0') {
    uStack_2d = 0x7f;
  }
  uStack_2c = 0;
  uStack_2b = 0xc0;
  uStack_2a = 0;
  uStack_29 = 0xff;
  iVar6 = FUN_08012760(0x56,auStack_4c,0x24);
  if (iVar6 == 0) {
LAB_0800d86c:
    *pcVar1 = '\x01';
    uVar8 = 0;
  }
  else {
    if ((acStack_24[0] != -2) && (*pcVar1 != '\0')) {
      if (*pcVar2 == '\0') {
        uVar9 = 0xac;
        uVar8 = 0xad;
      }
      else {
        uVar9 = 0x2c;
        uVar8 = 0x2d;
      }
      FUN_080127a0(0x55,uVar8,uVar9);
      FUN_0800db18(0xf);
    }
    if (*pcVar1 == '\x01') {
      FUN_08019844(0,0x83);
    }
    *pcVar1 = '\0';
    abStack_1c[0] = 0;
    iVar6 = FUN_080122f0(0x8e,abStack_1c,1);
    if (iVar6 != 0) {
      FUN_08012720(0x8e,abStack_1c[0] | 0x80,0);
    }
    abStack_28[0] = 0;
    iVar6 = FUN_080122f0(0,abStack_28,1);
    if ((iVar6 != 0) && ((abStack_28[0] & 0x35) != 0)) {
      abStack_28[0] = abStack_28[0] & ~(abStack_28[0] & 0x35);
      FUN_08012720(0,abStack_28[0]);
    }
    iVar6 = FUN_080122f0(0,abStack_28,1);
    if ((iVar6 != 0) && ((abStack_28[0] & 0x4a) != 0)) {
      abStack_28[0] = abStack_28[0] & ~(abStack_28[0] & 0x4a);
      FUN_08012720(0,abStack_28[0]);
    }
    if ((acStack_24[0] != -2) && (*pcVar1 != '\0')) {
      FUN_08016ee8(0);
    }
    uVar8 = 1;
  }
  return uVar8;
}



// ---------------------------------------------------------------------------
// Function: FUN_08009bd8 at 0x08009bd8
// ---------------------------------------------------------------------------

undefined8 FUN_08009bd8(undefined4 param_1,uint param_2)

{
  int iVar1;
  uint local_18;
  undefined4 uStack_14;
  uint local_10;
  
  local_18 = local_18 & 0xffffff00;
  uStack_14 = param_1;
  local_10 = param_2;
  FUN_080122f0(0x6e,&local_18,1);
  if ((char)local_18 != -0x33) {
    FUN_08012720(0x6e,0xcd,1);
  }
  local_18 = local_18 & 0xffffff00;
  iVar1 = FUN_080122f0(0x62,&local_18,1);
  if ((iVar1 != 0) && ((char)local_18 == '\0')) {
    *DAT_08009c30 = 1;
  }
  iVar1 = FUN_0800cfc0(param_1,local_10 & 0xff);
  return CONCAT44(local_18,(uint)(iVar1 != 0));
}



// ---------------------------------------------------------------------------
// Function: FUN_08009c34 at 0x08009c34
// ---------------------------------------------------------------------------

undefined8 FUN_08009c34(undefined4 param_1,undefined4 param_2,undefined1 param_3)

{
  int iVar1;
  
  iVar1 = FUN_0800d218(param_2,param_3);
  return CONCAT44(param_1,(uint)(iVar1 != 0));
}



// ---------------------------------------------------------------------------
// Function: FUN_08009c48 at 0x08009c48
// ---------------------------------------------------------------------------

bool FUN_08009c48(undefined4 param_1,char param_2)

{
  int iVar1;
  
  if (param_2 == '\x01') {
    iVar1 = FUN_0800d48c();
  }
  else {
    iVar1 = FUN_0800d530();
  }
  return iVar1 != 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_08009c64 at 0x08009c64
// ---------------------------------------------------------------------------

undefined4 FUN_08009c64(ushort *param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  int iVar1;
  undefined4 uVar2;
  ushort local_10;
  uint local_c;
  
  local_10 = 0;
  local_c = param_4 & 0xffffff00;
  iVar1 = FUN_080122f0(0,&local_c,1);
  uVar2 = 0;
  if (iVar1 != 0) {
    if (((int)(local_c << 0x1b) < 0) || ((int)(local_c << 0x1d) < 0)) {
      local_10 = 1;
    }
    if (((int)(local_c << 0x1c) < 0) || ((int)(local_c << 0x1e) < 0)) {
      local_10 = local_10 | 2;
    }
    if ((local_c & 1) != 0) {
      local_10 = local_10 | 4;
    }
    if ((int)(local_c << 0x19) < 0) {
      local_10 = local_10 | 8;
    }
    if ((int)(local_c << 0x1a) < 0) {
      local_10 = local_10 | 0x10;
    }
    iVar1 = FUN_080122f0(6,&local_c,1);
    uVar2 = 0;
    if (iVar1 != 0) {
      if ((int)(local_c << 0x1e) < 0) {
        local_10 = local_10 | 0x4000;
      }
      if ((local_c & 1) != 0) {
        local_10 = local_10 | 0x8000;
      }
      *param_1 = local_10;
      uVar2 = 1;
    }
  }
  return uVar2;
}



// ---------------------------------------------------------------------------
// Function: FUN_08009d34 at 0x08009d34
// ---------------------------------------------------------------------------

void FUN_08009d34(void)

{
  byte *pbVar1;
  char *pcVar2;
  int iVar3;
  undefined2 uVar4;
  
  pbVar1 = DAT_08009e10;
  iVar3 = DAT_08009e0c;
  pcVar2 = DAT_08009e00;
  if (((*DAT_08009e00 != '\0') && (*(float *)(DAT_08009e04 + 0x10) <= *DAT_08009e08)) &&
     (*(float *)(DAT_08009e04 + 0x14) <= *DAT_08009e08)) {
    if (*(float *)(DAT_08009e0c + 0x4c) <= *(float *)(DAT_08009e0c + 0xc)) {
      pbVar1[0xc] = 0;
      pbVar1[0xd] = 0;
      pbVar1[0xe] = 0;
      pbVar1[0xf] = 0;
      pbVar1[4] = 0;
      pbVar1[5] = 0;
      return;
    }
    if ((uint)(*(int *)(DAT_08009e0c + 0x50) * 0x3c) <= *(uint *)(DAT_08009e10 + 0xc)) {
      if (DAT_08009e10[1] == 0) {
        FUN_08019844(0,0x29);
        FUN_080196d0(0x1e6);
      }
      if (*pcVar2 == '\x01') {
        FUN_08009e18();
      }
      else {
        FUN_08016e44();
        pbVar1[0xc] = 0;
        pbVar1[0xd] = 0;
        pbVar1[0xe] = 0;
        pbVar1[0xf] = 0;
      }
      pbVar1[1] = 1;
      return;
    }
    if (*(int *)(DAT_08009e10 + 0xc) == 0) {
      DAT_08009e10[1] = 0;
    }
    if (*(uint *)(pbVar1 + 0xc) < *(int *)(iVar3 + 0x50) * 0x3c - 1U) {
      uVar4 = 10;
    }
    else {
      uVar4 = 3;
    }
    *(undefined2 *)(pbVar1 + 6) = uVar4;
    if (*(char *)(DAT_08009e14 + 0x3d) == '\0') {
      *pbVar1 = *pbVar1 + 1;
      if ((ushort)*pbVar1 < *(ushort *)(pbVar1 + 6)) {
        return;
      }
      *pbVar1 = 0;
    }
    *(int *)(pbVar1 + 0xc) = *(int *)(pbVar1 + 0xc) + 1;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08009e18 at 0x08009e18
// ---------------------------------------------------------------------------

void FUN_08009e18(void)

{
  bool bVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 in_r3;
  undefined4 local_1c;
  
  iVar4 = DAT_08009ee4;
  bVar1 = false;
  *(undefined1 *)(DAT_08009ee4 + 0x3e) = 0;
  local_1c = in_r3;
  FUN_0800ac9c();
  FUN_0800c8f4();
  FUN_0800c500();
  FUN_0800c5ec();
  FUN_0802008c();
  FUN_08009efc();
  FUN_08011458();
  FUN_08021858();
  thunk_FUN_080098f8();
  FUN_08017a90();
  FUN_0800db18(100);
  puVar2 = DAT_08009ee8;
  do {
    *puVar2 = 0xaaaa;
    iVar3 = FUN_0801efb8();
    if (iVar3 == 0) {
      bVar1 = true;
      break;
    }
    FUN_080112fc();
    FUN_0800db18(1);
    iVar3 = FUN_08009fe8();
  } while (iVar3 != 1);
  FUN_080219cc();
  FUN_080218b8();
  local_1c = DAT_08009eec;
  FUN_08018574(&local_1c);
  FUN_0800db18(300);
  FUN_08018574(&local_1c);
  iVar3 = DAT_08009ef0;
  *(undefined2 *)(DAT_08009ef0 + 4) = 0;
  if (!bVar1) {
    *(undefined1 *)(iVar4 + 0x3d) = 1;
  }
  FUN_08021864();
  FUN_08011464();
  iVar4 = FUN_08009ffc();
  if (iVar4 == 0) {
    *(undefined4 *)(iVar3 + 0xc) = 0;
  }
  else {
    *(int *)(iVar3 + 0xc) = *(int *)(DAT_08009ef4 + 0x50) * 0x3c + -1;
    *DAT_08009ef8 = 0;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08009efc at 0x08009efc
// ---------------------------------------------------------------------------

void FUN_08009efc(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  FUN_0800f610(0);
  *(undefined1 *)(DAT_08009fd8 + 2) = 1;
  *DAT_08009fdc = 0x80;
  iVar1 = DAT_08009fe0;
  *(undefined4 *)(DAT_08009fe0 + 0x14) = 1;
  FUN_08019544();
  FUN_0800a508();
  FUN_0800d960();
  *(undefined4 *)(iVar1 + 0x14) = 0x80;
  *(undefined4 *)(iVar1 + 0x10) = 0x20;
  FUN_0800c8f4();
  FUN_0800ac9c();
  uVar2 = DAT_08009fe4;
  FUN_080102cc(DAT_08009fe4,1);
  puVar3 = DAT_08009fdc + -5;
  FUN_080102cc(puVar3,2);
  FUN_080102cc(uVar2,4);
  FUN_080102cc(puVar3,8);
  FUN_080102cc(iVar1,0x10);
  FUN_080102cc(uVar2,0x20);
  FUN_080102cc(uVar2,0x80);
  FUN_080102cc(uVar2,0x8000);
  FUN_0800f3d0(1);
  FUN_0800f3d0(2);
  FUN_0800f3d0(4);
  FUN_0800f3d0(8);
  FUN_0800f3d0(0x10);
  FUN_0800f3d0(0x20);
  FUN_0800f3d0(0x80);
  FUN_0800f3d0(0x8000);
  FUN_0800db18(0x14);
  FUN_0800ffa8(uVar2,1,0x48,0x10);
  FUN_0800ffa8(puVar3,2,0x48,0x10);
  FUN_0800ffa8(uVar2,4,0x48,0x10);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08009fe8 at 0x08009fe8
// ---------------------------------------------------------------------------

undefined4 FUN_08009fe8(void)

{
  if (*(char *)(DAT_08009ff8 + 2) == '\0') {
    return 1;
  }
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_08009ffc at 0x08009ffc
// ---------------------------------------------------------------------------

undefined4 FUN_08009ffc(void)

{
  int iVar1;
  
  iVar1 = DAT_0800a038;
  *(undefined4 *)(DAT_0800a038 + 0x14) = 1;
  FUN_0800a634();
  FUN_08015b28(1,0x2580);
  FUN_08015b28(2,0x2580);
  FUN_08015b28(4,0x2580);
  *(undefined4 *)(iVar1 + 0x10) = 0x20;
  *(undefined4 *)(iVar1 + 0x14) = 0x80;
  FUN_0800c8f4();
  FUN_0800ac9c();
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800a03c at 0x0800a03c
// ---------------------------------------------------------------------------

void FUN_0800a03c(void)

{
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800a040 at 0x0800a040
// ---------------------------------------------------------------------------

undefined1 FUN_0800a040(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  
  iVar3 = DAT_0800a148;
  iVar2 = DAT_0800a144;
  iVar1 = DAT_0800a140;
  if (*(char *)(DAT_0800a140 + 0x3f) == '\0') {
    return 0;
  }
  if ((((*(char *)(DAT_0800a140 + 0x12) == '\0') && (*(char *)(DAT_0800a140 + 0x13) != '\0')) ||
      (0x3f000000 < (int)(*(float *)(DAT_0800a14c + 0xc) - *(float *)(DAT_0800a150 + 0xc)))) ||
     ((*(short *)(DAT_0800a14c + 0x38) != 0 || (*(short *)(DAT_0800a14c + 0x48) != 0)))) {
    FUN_08008c40();
    *(undefined1 *)(iVar1 + 0x3f) = 0;
    *(undefined1 *)(iVar2 + 0x10) = 0;
    *(undefined2 *)(iVar3 + 0x10) = 0;
    *(undefined4 *)(iVar3 + 8) = 0;
    *(undefined4 *)(iVar3 + 0xc) = 0;
    *(undefined2 *)(iVar3 + 0x12) = 0;
    *(undefined1 *)(iVar1 + 0x41) = 0;
  }
  if ((0x96 < *(ushort *)(iVar3 + 0x10)) && (*(char *)(iVar2 + 0x10) == '\0')) {
    *(undefined1 *)(iVar2 + 0x10) = 1;
  }
  if (((0xdc < *(ushort *)(iVar3 + 0x10)) &&
      (0x4f < (int)((uint)*(ushort *)(iVar3 + 0x10) - (uint)*(ushort *)(iVar2 + 0x32)))) &&
     (*(char *)(iVar2 + 0x10) == '\x02')) {
    *(undefined1 *)(iVar2 + 0x10) = 3;
  }
  if (0x1c2 < *(ushort *)(iVar3 + 0x10)) {
    *(undefined2 *)(iVar3 + 0x10) = 0;
    *(undefined1 *)(iVar2 + 0x10) = 0;
    *(undefined2 *)(iVar2 + 0x32) = 0;
  }
  pcVar4 = DAT_0800a154;
  if (*(char *)(iVar2 + 0x10) == '\x01') {
    if (*DAT_0800a154 != '\0') {
      *(byte *)(iVar1 + 0x3f) = *(byte *)(iVar1 + 0x3f) | 0x10;
      FUN_08008c40();
    }
    *(undefined1 *)(iVar2 + 0x10) = 2;
    if (0x15e < *(ushort *)(iVar3 + 0x10)) {
      *(undefined2 *)(iVar3 + 0x10) = 0xa0;
    }
    *(undefined2 *)(iVar2 + 0x32) = *(undefined2 *)(iVar3 + 0x10);
  }
  else if (*(char *)(iVar2 + 0x10) == '\x03') {
    if (*DAT_0800a154 != '\0') {
      FUN_08009144();
    }
    *(undefined1 *)(iVar2 + 0x10) = 0;
    *(undefined2 *)(iVar3 + 0x10) = 0;
    if (*(char *)(iVar3 + 0x16) == '\0') {
      *(undefined1 *)(iVar1 + 0x3f) = 0;
      *(undefined4 *)(iVar3 + 8) = 0;
      *(undefined4 *)(iVar3 + 0xc) = 0;
      *(undefined1 *)(iVar1 + 0x41) = 0;
      *(undefined1 *)(iVar2 + 1) = 0;
      if (*pcVar4 == '\0') {
        FUN_08008c40();
      }
    }
    else {
      *(undefined1 *)(iVar1 + 0x3f) = 1;
    }
    return 0;
  }
  return 1;
}



// ---------------------------------------------------------------------------
// Function: BusFault_Handler at 0x0800a504
// ---------------------------------------------------------------------------

void BusFault_Handler(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ---------------------------------------------------------------------------
// Function: FUN_0800a508 at 0x0800a508
// ---------------------------------------------------------------------------

void FUN_0800a508(void)

{
  char *pcVar1;
  int *piVar2;
  undefined4 in_r3;
  undefined4 local_10;
  
  pcVar1 = DAT_0800a558;
  if (*DAT_0800a558 == '\0') {
    local_10 = in_r3;
    FUN_0800a6e4(DAT_0800a55c);
    piVar2 = DAT_0800a560;
    *DAT_0800a560 = 0x80;
    *DAT_0800a564 = 0x4000;
    *pcVar1 = '\x01';
    FUN_0800db18(0x14);
    local_10 = 0x10021800;
    FUN_0801031c(DAT_0800a560 + -5,&local_10);
    *piVar2 = (int)piVar2 >> 0x13;
    *piVar2 = ((int)piVar2 >> 0x13) << 1;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800a568 at 0x0800a568
// ---------------------------------------------------------------------------

void FUN_0800a568(uint *param_1)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  uint *puVar4;
  uint *puVar5;
  uint uVar6;
  
  puVar1 = DAT_0800a62c;
  uVar3 = 1 << *(sbyte *)((int)param_1 + 10);
  *DAT_0800a62c = *DAT_0800a62c | 1;
  puVar4 = DAT_0800a62c + 7;
  *puVar4 = *puVar4 & ~uVar3;
  iVar2 = DAT_0800a630;
  puVar5 = DAT_0800a62c + 3;
  if ((char)param_1[3] == '\0') {
    *puVar5 = *puVar5 & ~uVar3;
    *(uint *)(iVar2 + (uint)*(byte *)((int)param_1 + 10) * 8 + 0x640) =
         CONCAT22(*(undefined2 *)((int)param_1 + 6),*(undefined2 *)((int)param_1 + 2));
    *(uint *)(iVar2 + (uint)*(byte *)((int)param_1 + 10) * 8 + 0x644) =
         CONCAT22((short)param_1[1],(short)*param_1);
  }
  if ((char)param_1[3] == '\x01') {
    *puVar5 = *puVar5 | uVar3;
    *(uint *)(iVar2 + (uint)*(byte *)((int)param_1 + 10) * 8 + 0x640) =
         *param_1 >> 0x10 | *param_1 << 0x10;
    *(uint *)(iVar2 + (uint)*(byte *)((int)param_1 + 10) * 8 + 0x644) =
         param_1[1] >> 0x10 | param_1[1] << 0x10;
  }
  uVar6 = DAT_0800a62c[1];
  if (*(char *)((int)param_1 + 0xb) == '\0') {
    uVar6 = uVar6 & ~uVar3;
  }
  else {
    uVar6 = uVar6 | uVar3;
  }
  DAT_0800a62c[1] = uVar6;
  puVar5 = DAT_0800a62c + 5;
  if ((short)param_1[2] == 0) {
    *puVar5 = *puVar5 & ~uVar3;
  }
  if ((short)param_1[2] == 1) {
    *puVar5 = *puVar5 | uVar3;
  }
  if (*(char *)((int)param_1 + 0xd) == '\x01') {
    *puVar4 = *puVar4 | uVar3;
  }
  *puVar1 = *puVar1 & 0xfffffffe;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800a634 at 0x0800a634
// ---------------------------------------------------------------------------

void FUN_0800a634(void)

{
  undefined4 uVar1;
  undefined2 local_38;
  undefined1 local_36;
  undefined1 local_35;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined2 local_2c;
  undefined2 local_2a;
  undefined2 local_28;
  undefined2 local_26;
  undefined2 local_24;
  undefined1 local_22;
  undefined1 local_21;
  undefined1 local_20;
  undefined1 local_1f;
  short local_1c;
  undefined1 local_1a;
  undefined1 local_19;
  uint local_18;
  uint local_14;
  
  *DAT_0800a65c = 0x80;
  *DAT_0800a660 = 0x4000;
  *DAT_0800a664 = 0;
  *(undefined4 *)(DAT_0800a668 + 4) = 0;
  FUN_0800db18(0x14);
  local_14 = DAT_0800a66c;
  local_18 = 0;
  local_18 = FUN_08010920();
  if (local_18 != 0) {
    local_14 = local_18;
  }
  FUN_08017c80(0x2000000);
  uVar1 = DAT_0801335c;
  local_1c = 0x800;
  local_19 = 0x48;
  FUN_0801031c(DAT_0801335c,&local_1c);
  local_1c = (short)((int)uVar1 >> 0x12);
  local_19 = 0x18;
  local_1a = 3;
  FUN_0801031c(uVar1,&local_1c);
  uVar1 = DAT_08013360;
  FUN_0800a6e4(DAT_08013360);
  FUN_0800a808(&local_38);
  local_32 = 0;
  local_31 = 1;
  local_34 = 4;
  local_30 = 0;
  local_36 = 0;
  local_2f = 1;
  local_35 = 0;
  local_2e = 0;
  local_38 = (undefined2)(DAT_08013364 / local_14);
  local_2d = 1;
  local_33 = 1;
  FUN_0800a720(uVar1,&local_38);
  local_22 = 0;
  local_21 = 0;
  local_20 = 1;
  local_2c = 0;
  local_28 = 0;
  local_2a = 0;
  local_26 = 0;
  local_24 = 0;
  local_1f = 1;
  FUN_0800a568(&local_2c);
  FUN_0800a710(uVar1,2,1);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800a670 at 0x0800a670
// ---------------------------------------------------------------------------

bool FUN_0800a670(int param_1,byte param_2,undefined4 param_3,undefined1 param_4,undefined1 param_5)

{
  undefined4 *puVar1;
  int iVar2;
  byte bVar3;
  
  puVar1 = DAT_0800a6d8;
  *DAT_0800a6d8 = param_3;
  puVar1[1] = param_3;
  *(undefined1 *)(puVar1 + 2) = param_5;
  *(undefined1 *)((int)puVar1 + 9) = param_4;
  *(byte *)((int)puVar1 + 10) = param_2;
  bVar3 = 0;
  while( true ) {
    if (param_2 <= bVar3) break;
    *(undefined1 *)((int)puVar1 + bVar3 + 0xb) = *(undefined1 *)(param_1 + (uint)bVar3);
    bVar3 = bVar3 + 1;
  }
  iVar2 = FUN_0800a950(DAT_0800a6dc,DAT_0800a6d8);
  if (iVar2 == 4) {
    FUN_0800db18(1);
  }
  else {
    FUN_0800db18(1);
  }
  return iVar2 != 4;
}



// ---------------------------------------------------------------------------
// Function: CAN2_RX1_IRQHandler at 0x0800a6e0
// ---------------------------------------------------------------------------

void CAN2_RX1_IRQHandler(void)

{
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800a6e4 at 0x0800a6e4
// ---------------------------------------------------------------------------

void FUN_0800a6e4(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == DAT_0800a70c) {
    uVar1 = 0x2000000;
  }
  else {
    uVar1 = 0x4000000;
  }
  FUN_08017c98(uVar1);
  FUN_08017c98(uVar1,0);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800a710 at 0x0800a710
// ---------------------------------------------------------------------------

void FUN_0800a710(int param_1,uint param_2,int param_3)

{
  if (param_3 == 0) {
    param_2 = *(uint *)(param_1 + 0x14) & ~param_2;
  }
  else {
    param_2 = *(uint *)(param_1 + 0x14) | param_2;
  }
  *(uint *)(param_1 + 0x14) = param_2;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800a720 at 0x0800a720
// ---------------------------------------------------------------------------

undefined4 FUN_0800a720(uint *param_1,ushort *param_2)

{
  int iVar1;
  uint uVar2;
  
  *param_1 = *param_1 & 0xfffffffd;
  *param_1 = *param_1 | 1;
  for (iVar1 = 0; ((param_1[1] & 1) == 0 && (iVar1 != 0xffff)); iVar1 = iVar1 + 1) {
  }
  if ((param_1[1] & 1) != 0) {
    if ((char)param_2[3] == '\x01') {
      uVar2 = *param_1 | 0x80;
    }
    else {
      uVar2 = *param_1 & 0xffffff7f;
    }
    *param_1 = uVar2;
    if (*(char *)((int)param_2 + 7) == '\x01') {
      uVar2 = *param_1 | 0x40;
    }
    else {
      uVar2 = *param_1 & 0xffffffbf;
    }
    *param_1 = uVar2;
    if ((char)param_2[4] == '\x01') {
      uVar2 = *param_1 | 0x20;
    }
    else {
      uVar2 = *param_1 & 0xffffffdf;
    }
    *param_1 = uVar2;
    if (*(char *)((int)param_2 + 9) == '\x01') {
      uVar2 = *param_1 | 0x10;
    }
    else {
      uVar2 = *param_1 & 0xffffffef;
    }
    *param_1 = uVar2;
    if ((char)param_2[5] == '\x01') {
      uVar2 = *param_1 | 8;
    }
    else {
      uVar2 = *param_1 & 0xfffffff7;
    }
    *param_1 = uVar2;
    if (*(char *)((int)param_2 + 0xb) == '\x01') {
      uVar2 = *param_1 | 4;
    }
    else {
      uVar2 = *param_1 & 0xfffffffb;
    }
    *param_1 = uVar2;
    param_1[7] = (uint)(byte)param_2[1] << 0x1e | (uint)*(byte *)((int)param_2 + 3) << 0x18 |
                 (uint)(byte)param_2[2] << 0x10 | (uint)*(byte *)((int)param_2 + 5) << 0x14 |
                 *param_2 - 1;
    *param_1 = *param_1 & 0xfffffffe;
    for (iVar1 = 0; ((param_1[1] & 1) != 0 && (iVar1 != 0xffff)); iVar1 = iVar1 + 1) {
    }
    if ((param_1[1] & 1) == 0) {
      return 1;
    }
  }
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800a808 at 0x0800a808
// ---------------------------------------------------------------------------

void FUN_0800a808(undefined2 *param_1)

{
  *(undefined1 *)(param_1 + 3) = 0;
  *(undefined1 *)((int)param_1 + 7) = 0;
  *(undefined1 *)(param_1 + 4) = 0;
  *(undefined1 *)((int)param_1 + 9) = 0;
  *(undefined1 *)(param_1 + 5) = 0;
  *(undefined1 *)((int)param_1 + 0xb) = 0;
  *(undefined1 *)(param_1 + 1) = 0;
  *(undefined1 *)((int)param_1 + 3) = 0;
  *(undefined1 *)(param_1 + 2) = 3;
  *(undefined1 *)((int)param_1 + 5) = 2;
  *param_1 = 1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800a828 at 0x0800a828
// ---------------------------------------------------------------------------

void FUN_0800a828(int param_1,int param_2,uint *param_3)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = param_1 + param_2 * 0x10;
  uVar2 = *(uint *)(iVar1 + 0x1b0) & 4;
  *(char *)(param_3 + 2) = (char)uVar2;
  if (uVar2 == 0) {
    *param_3 = *(uint *)(iVar1 + 0x1b0) >> 0x15;
  }
  else {
    param_3[1] = *(uint *)(iVar1 + 0x1b0) >> 3;
  }
  *(byte *)((int)param_3 + 9) = (byte)*(undefined4 *)(iVar1 + 0x1b0) & 2;
  *(byte *)((int)param_3 + 10) = (byte)*(undefined4 *)(iVar1 + 0x1b4) & 0xf;
  *(char *)((int)param_3 + 0x13) = (char)((uint)*(undefined4 *)(iVar1 + 0x1b4) >> 8);
  *(char *)((int)param_3 + 0xb) = (char)*(undefined4 *)(iVar1 + 0x1b8);
  *(char *)(param_3 + 3) = (char)((uint)*(undefined4 *)(iVar1 + 0x1b8) >> 8);
  *(char *)((int)param_3 + 0xd) = (char)((uint)*(undefined4 *)(iVar1 + 0x1b8) >> 0x10);
  *(char *)((int)param_3 + 0xe) = (char)((uint)*(undefined4 *)(iVar1 + 0x1b8) >> 0x18);
  *(char *)((int)param_3 + 0xf) = (char)*(undefined4 *)(iVar1 + 0x1bc);
  *(char *)(param_3 + 4) = (char)((uint)*(undefined4 *)(iVar1 + 0x1bc) >> 8);
  *(char *)((int)param_3 + 0x11) = (char)((uint)*(undefined4 *)(iVar1 + 0x1bc) >> 0x10);
  *(char *)((int)param_3 + 0x12) = (char)((uint)*(undefined4 *)(iVar1 + 0x1bc) >> 0x18);
  if (param_2 == 0) {
    *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) | 0x20;
    return;
  }
  *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | 0x20;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800a8b8 at 0x0800a8b8
// ---------------------------------------------------------------------------

void FUN_0800a8b8(void)

{
  int *piVar1;
  int iVar2;
  byte local_24;
  uint local_20;
  undefined1 auStack_1c [12];
  
  piVar1 = DAT_0800a948;
  if (*(char *)(*DAT_0800a948 + 0x262) == '\x05') {
    FUN_0800a670(auStack_1c,8,1,0,0);
    local_20 = 0;
    do {
      local_24 = 0;
      iVar2 = *piVar1;
      for (; local_24 < 8; local_24 = local_24 + 1) {
        auStack_1c[local_24] = *(undefined1 *)(local_20 + local_24 + iVar2 + 0x12e);
      }
      local_20 = local_20 + 8;
      FUN_0800a670(auStack_1c,8,2,0,0);
    } while (local_20 < *(ushort *)(*piVar1 + 0x25a));
    FUN_0800a670(auStack_1c,8,3,0,0);
    *(undefined2 *)(*piVar1 + 0x25a) = 0;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: thunk_FUN_0800a8b8 at 0x0800a94c
// ---------------------------------------------------------------------------

void thunk_FUN_0800a8b8(void)

{
  int *piVar1;
  int iVar2;
  byte bStack_24;
  uint uStack_20;
  undefined1 auStack_1c [12];
  
  piVar1 = DAT_0800a948;
  if (*(char *)(*DAT_0800a948 + 0x262) == '\x05') {
    FUN_0800a670(auStack_1c,8,1,0,0);
    uStack_20 = 0;
    do {
      bStack_24 = 0;
      iVar2 = *piVar1;
      for (; bStack_24 < 8; bStack_24 = bStack_24 + 1) {
        auStack_1c[bStack_24] = *(undefined1 *)(uStack_20 + bStack_24 + iVar2 + 0x12e);
      }
      uStack_20 = uStack_20 + 8;
      FUN_0800a670(auStack_1c,8,2,0,0);
    } while (uStack_20 < *(ushort *)(*piVar1 + 0x25a));
    FUN_0800a670(auStack_1c,8,3,0,0);
    *(undefined2 *)(*piVar1 + 0x25a) = 0;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800a950 at 0x0800a950
// ---------------------------------------------------------------------------

int FUN_0800a950(int param_1,ushort *param_2)

{
  int iVar1;
  
  iVar1 = 0;
  if (-1 < *(int *)(param_1 + 8) << 5) {
    if (*(int *)(param_1 + 8) << 4 < 0) {
      iVar1 = 1;
    }
    else {
      if (-1 < *(int *)(param_1 + 8) << 3) {
        return 4;
      }
      iVar1 = 2;
    }
  }
  param_1 = param_1 + iVar1 * 0x10;
  *(uint *)(param_1 + 0x180) = *(uint *)(param_1 + 0x180) & 1;
  if ((byte)param_2[4] == 0) {
    *(uint *)(param_1 + 0x180) =
         *(uint *)(param_1 + 0x180) | (uint)*(byte *)((int)param_2 + 9) | (uint)*param_2 << 0x15;
  }
  else {
    *(uint *)(param_1 + 0x180) =
         *(uint *)(param_1 + 0x180) | (uint)(byte)param_2[4] |
         (uint)*(byte *)((int)param_2 + 9) | *(int *)(param_2 + 2) << 3;
  }
  *(byte *)(param_2 + 5) = (byte)param_2[5] & 0xf;
  *(uint *)(param_1 + 0x184) = *(uint *)(param_1 + 0x184) & 0xfffffff0;
  *(uint *)(param_1 + 0x184) = *(uint *)(param_1 + 0x184) | (uint)(byte)param_2[5];
  *(uint *)(param_1 + 0x188) =
       (uint)*(byte *)((int)param_2 + 0xb) | (uint)(byte)param_2[7] << 0x18 |
       (uint)*(byte *)((int)param_2 + 0xd) << 0x10 | (uint)(byte)param_2[6] << 8;
  *(uint *)(param_1 + 0x18c) =
       (uint)*(byte *)((int)param_2 + 0xf) | (uint)(byte)param_2[9] << 0x18 |
       (uint)*(byte *)((int)param_2 + 0x11) << 0x10 | (uint)(byte)param_2[8] << 8;
  *(uint *)(param_1 + 0x180) = *(uint *)(param_1 + 0x180) | 1;
  return iVar1;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800aa10 at 0x0800aa10
// ---------------------------------------------------------------------------

void FUN_0800aa10(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_0800aa64;
  iVar2 = DAT_0800aa60;
  if ((*(char *)(DAT_0800aa60 + 0x3a) != '\0') &&
     (*(char *)(DAT_0800aa64 + 8) = *(char *)(DAT_0800aa64 + 8) + '\x01', 0xe < *(byte *)(iVar1 + 8)
     )) {
    *(undefined1 *)(iVar1 + 8) = 0;
    FUN_08019624(0x1f0);
  }
  if (((*(char *)(iVar2 + 0x3b) == '\0') || (iVar2 = FUN_0800cb6c(), iVar2 == 0)) ||
     (*(char *)(iVar1 + 9) = *(char *)(iVar1 + 9) + '\x01', *(byte *)(iVar1 + 9) < 0xf)) {
    return;
  }
  *(undefined1 *)(iVar1 + 9) = 0;
  FUN_08019624(0x1ec);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800aa68 at 0x0800aa68
// ---------------------------------------------------------------------------

void FUN_0800aa68(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint in_fpscr;
  float fVar9;
  
  iVar3 = DAT_0800ac6c;
  iVar2 = DAT_0800ac68;
  if (*(char *)(DAT_0800ac68 + 0x3a) == '\0') {
    if (*(char *)(DAT_0800ac6c + 0x2b) == '\0') {
      *(undefined1 *)(DAT_0800ac6c + 0x27) = 0;
    }
    else {
      *(char *)(DAT_0800ac6c + 0x28) = *(char *)(DAT_0800ac6c + 0x28) + '\x01';
      if (9 < *(byte *)(iVar3 + 0x28)) {
        *(undefined1 *)(iVar3 + 0x28) = 0;
        *(undefined1 *)(iVar3 + 0x2b) = 0;
        uVar5 = 0x24;
        goto LAB_0800aae6;
      }
    }
  }
  else if (*(char *)(DAT_0800ac6c + 0x2b) == '\0') {
    *(char *)(DAT_0800ac6c + 0x27) = *(char *)(DAT_0800ac6c + 0x27) + '\x01';
    if (9 < *(byte *)(iVar3 + 0x27)) {
      *(undefined1 *)(iVar3 + 0x27) = 0;
      *(undefined1 *)(iVar3 + 0x2b) = 1;
      uVar5 = 0x23;
      goto LAB_0800aae6;
    }
  }
  else {
    *(undefined1 *)(DAT_0800ac6c + 0x28) = 0;
    *(short *)(iVar3 + 0x4e) = *(short *)(iVar3 + 0x4e) + 1;
    if (*DAT_0800ac70 < *(ushort *)(iVar3 + 0x4e)) {
      *(undefined2 *)(iVar3 + 0x4e) = 0;
      uVar5 = 0x62;
LAB_0800aae6:
      FUN_08019844(0,uVar5,param_3,param_4,0,0);
    }
  }
  if (*(char *)(iVar2 + 0x3b) == '\0') {
    if (*(char *)(iVar3 + 0x2c) == '\0') {
      *(undefined1 *)(iVar3 + 0x29) = 0;
    }
    else {
      *(char *)(iVar3 + 0x2a) = *(char *)(iVar3 + 0x2a) + '\x01';
      if (9 < *(byte *)(iVar3 + 0x2a)) {
        *(undefined1 *)(iVar3 + 0x2a) = 0;
        *(undefined1 *)(iVar3 + 0x2c) = 0;
        FUN_08019844(0,0x28);
        if (*(char *)(DAT_0800ac78 + 0x19) == '\x01') {
          *(undefined1 *)(DAT_0800ac78 + 0x19) = 2;
        }
      }
    }
  }
  else if (*(char *)(iVar3 + 0x2c) == '\0') {
    *(char *)(iVar3 + 0x29) = *(char *)(iVar3 + 0x29) + '\x01';
    if (9 < *(byte *)(iVar3 + 0x29)) {
      *(undefined1 *)(iVar3 + 0x29) = 0;
      *(undefined1 *)(iVar3 + 0x2c) = 1;
      uVar5 = 0x27;
      goto LAB_0800ab20;
    }
  }
  else {
    *(undefined1 *)(iVar3 + 0x2a) = 0;
    *(short *)(iVar3 + 0x50) = *(short *)(iVar3 + 0x50) + 1;
    if (*DAT_0800ac74 < *(ushort *)(iVar3 + 0x50)) {
      *(undefined2 *)(iVar3 + 0x50) = 0;
      uVar5 = 99;
LAB_0800ab20:
      FUN_08019844(0,uVar5);
    }
  }
  pcVar4 = DAT_0800ac7c;
  if ((*DAT_0800ac7c != '\0') && (*DAT_0800ac80 != '\0')) {
    FUN_0801806c();
    uVar5 = DAT_0800ac88;
    uVar8 = (uint)DAT_0800ac84[1] * 0x1000000 + (uint)DAT_0800ac84[2] * 0x10000;
    uVar7 = uVar8 + (uint)DAT_0800ac84[3] * 0x100;
    uVar6 = uVar7 + DAT_0800ac84[4];
    uVar7 = (uint)*DAT_0800ac84 +
            (uint)CARRY4((uint)DAT_0800ac84[1] * 0x1000000,(uint)DAT_0800ac84[2] * 0x10000) +
            (uint)CARRY4(uVar8,(uint)DAT_0800ac84[3] * 0x100) +
            (uint)CARRY4(uVar7,(uint)DAT_0800ac84[4]);
    if ((*(uint *)(pcVar4 + 0x14) < uVar7 ||
         uVar7 - *(uint *)(pcVar4 + 0x14) < (uint)(*(uint *)(pcVar4 + 0x10) <= uVar6)) &&
       (uVar7 <= *(uint *)(pcVar4 + 0x1c) &&
        (uint)(*(uint *)(pcVar4 + 0x18) <= uVar6) <= uVar7 - *(uint *)(pcVar4 + 0x1c))) {
      cVar1 = pcVar4[1];
      *(float *)(iVar3 + 0x5c) = *(float *)(iVar3 + 0x5c) + 1.0;
      if (cVar1 == '\x01') {
        fVar9 = (float)VectorUnsignedToFloat
                                 (*(undefined4 *)(pcVar4 + 0xc),(byte)(in_fpscr >> 0x16) & 3);
        if (fVar9 <= *(float *)(iVar3 + 0x5c)) {
          *(undefined4 *)(iVar3 + 0x5c) = uVar5;
LAB_0800ac3a:
          FUN_08019844(0,0x5f,uVar6,uVar7);
          return;
        }
      }
      else if (DAT_0800ac8c <= *(int *)(iVar3 + 0x5c)) {
        *(undefined4 *)(iVar3 + 0x5c) = uVar5;
        *(short *)(iVar3 + 0x52) = *(short *)(iVar3 + 0x52) + 1;
        if (*(uint *)(pcVar4 + 0xc) <= (uint)*(ushort *)(iVar3 + 0x52)) {
          *(undefined2 *)(iVar3 + 0x52) = 0;
          goto LAB_0800ac3a;
        }
      }
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800ac90 at 0x0800ac90
// ---------------------------------------------------------------------------

void FUN_0800ac90(void)

{
  *DAT_0800ac98 = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800ac9c at 0x0800ac9c
// ---------------------------------------------------------------------------

void FUN_0800ac9c(void)

{
  int iVar1;
  
  iVar1 = FUN_0800b002();
  if (iVar1 != 0) {
    if ((~*(byte *)(DAT_0800acd0 + 3) & 0x50) != 0) {
      FUN_0800f484();
      iVar1 = DAT_0800acd4;
      if (*(char *)(DAT_0800acd4 + 0x4d) != '\0') {
        thunk_FUN_0800cd3c();
      }
      *(undefined1 *)(iVar1 + 0x4d) = 0;
      return;
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800acd8 at 0x0800acd8
// ---------------------------------------------------------------------------

void FUN_0800acd8(void)

{
  byte *pbVar1;
  byte bVar2;
  int iVar3;
  uint in_r3;
  uint local_10;
  
  local_10 = in_r3 & 0xffffff00;
  iVar3 = FUN_080122f0(0,&local_10,1);
  if ((iVar3 != 0) && ((local_10 & 0x4a) != 0)) {
    bVar2 = (byte)local_10 & ~((byte)local_10 & 0x4a);
    local_10 = CONCAT31(local_10._1_3_,bVar2);
    FUN_08012720(0,bVar2);
  }
  pbVar1 = DAT_0800ad8c;
  if ((((*DAT_0800ad88 != '\0') &&
       ((DAT_0800ad8c[0x4a] == 0 || ((DAT_0800ad8c[0x4a] != 0 && (*DAT_0800ad90 != '\0')))))) &&
      (*DAT_0800ad94 == '\x02')) &&
     (((((-1 < (int)((uint)DAT_0800ad8c[0x39] << 0x1d) && ((DAT_0800ad8c[0x12] & 0x13) == 0)) &&
        ((*DAT_0800ad8c & 1) == 0)) &&
       ((-1 < (int)((uint)DAT_0800ad8c[0x51] << 0x1d) && (*DAT_0800ad98 == '\0')))) &&
      (((DAT_0800ad8c[0x10] & 3) == 0 &&
       ((iVar3 = FUN_0800b008(), iVar3 != 0 && (pbVar1[0x4b] == 0)))))))) {
    FUN_0800f490();
    thunk_FUN_0800cdb4();
    pbVar1[0x4d] = 1;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800ad9c at 0x0800ad9c
// ---------------------------------------------------------------------------

void FUN_0800ad9c(void)

{
  byte *pbVar1;
  char *pcVar2;
  byte *pbVar3;
  ushort *puVar4;
  char *pcVar5;
  byte bVar6;
  uint in_r3;
  float local_1c;
  uint local_18;
  
  pbVar3 = DAT_0800af10;
  local_1c = DAT_0800af08;
  local_18 = in_r3 & 0xffffff00;
  if ((*DAT_0800af0c == '\0') && (-1 < (int)((uint)DAT_0800af10[0x39] << 0x1d))) {
    if (*DAT_0800af14 == '\x02') {
      pbVar1 = DAT_0800af10 + 0x3d;
      local_18 = CONCAT31((int3)(in_r3 >> 8),*pbVar1);
      *pbVar1 = 1;
      FUN_08018574(&local_1c);
      *pbVar1 = (byte)local_18;
    }
    else {
      local_1c = *DAT_0800af18;
    }
    pcVar2 = DAT_0800af20;
    puVar4 = DAT_0800af1c;
    if (local_1c < *(float *)(DAT_0800af1c + 4)) {
      pcVar2[0x34] = '\0';
      pcVar2[0x35] = '\0';
      return;
    }
    *(short *)(DAT_0800af20 + 0x34) = *(short *)(DAT_0800af20 + 0x34) + 1;
    if (*puVar4 <= *(ushort *)(pcVar2 + 0x34)) {
      pcVar2[0x34] = '\0';
      pcVar2[0x35] = '\0';
      pcVar2[0x54] = '\0';
      pcVar5 = DAT_0800af24;
      pcVar2[0x55] = '\0';
      pcVar2[0x56] = '\0';
      pcVar2[0x57] = '\0';
      if (((((pbVar3[0x4a] != 0) && (*DAT_0800af24 != '\0')) && (pbVar3[0x4d] != 0)) &&
          (((pbVar3[0x12] & 0x13) == 0 && ((*pbVar3 & 1) == 0)))) &&
         ((-1 < (int)((uint)pbVar3[0x51] << 0x1d) &&
          ((*pcVar2 == '\0' && ((pbVar3[0x10] & 3) == 0)))))) {
        pbVar3[0x4b] = 1;
        *(short *)(pcVar2 + 0x2e) = *(short *)(pcVar2 + 0x2e) + 1;
        if (*DAT_0800af28 == '\x01') {
          FUN_0800ac9c();
        }
        else {
          for (bVar6 = 0; bVar6 < 0x19; bVar6 = bVar6 + 1) {
            FUN_0801ca54();
            FUN_0801f89c();
            FUN_0800db18(10);
          }
        }
        pbVar3[0x39] = pbVar3[0x39] & 0xfb;
        FUN_08019844(0,0x7f);
      }
      FUN_0800ac9c();
      if ((-1 < (int)((uint)pbVar3[0x39] << 0x1d)) && (*pcVar5 == '\0')) {
        FUN_08019844(9);
        FUN_080196d0(0x1dc);
      }
      if (pbVar3[0x4b] == 0) {
        pbVar3[0x39] = pbVar3[0x39] | 4;
        for (bVar6 = 0; bVar6 < 0x32; bVar6 = bVar6 + 1) {
          FUN_0801ca54();
          FUN_0801f89c();
          FUN_0800db18(10);
        }
      }
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800af2c at 0x0800af2c
// ---------------------------------------------------------------------------

void FUN_0800af2c(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint in_fpscr;
  float fVar4;
  float fVar5;
  
  iVar3 = DAT_0800afb8;
  iVar2 = DAT_0800afb4;
  iVar1 = DAT_0800afb0;
  if ((int)((uint)*(byte *)(DAT_0800afb0 + 0x39) << 0x1d) < 0) {
    if ((ushort)*(byte *)(DAT_0800afb4 + 0xe) < *(ushort *)(DAT_0800afb4 + 0x14)) {
      *(undefined4 *)(DAT_0800afb8 + 0x54) = 0;
    }
    else {
      *(int *)(DAT_0800afb8 + 0x54) = *(int *)(DAT_0800afb8 + 0x54) + 1;
      fVar4 = (float)VectorUnsignedToFloat
                               ((uint)*(byte *)(iVar2 + 0xd) * 0x3c,(byte)(in_fpscr >> 0x16) & 3);
      fVar5 = (float)VectorUnsignedToFloat
                               (*(undefined4 *)(iVar3 + 0x54),(byte)(in_fpscr >> 0x16) & 3);
      if (fVar4 * 0.25 <= fVar5) {
        if ((*(short *)(iVar2 + 0x14) == 0) && (*(char *)(iVar2 + 0xe) != '\0')) {
          *(undefined2 *)(iVar2 + 0x14) = 1;
        }
        if (*(char *)(iVar2 + 0xe) != '\0') {
          *(short *)(iVar2 + 0x14) = *(short *)(iVar2 + 0x14) + 1;
        }
        *(undefined4 *)(iVar3 + 0x54) = 0;
        *(byte *)(iVar1 + 0x39) = *(byte *)(iVar1 + 0x39) & 0xfb;
        FUN_0800acd8();
        FUN_08019844(0xc,0xb);
        return;
      }
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800afbc at 0x0800afbc
// ---------------------------------------------------------------------------

void FUN_0800afbc(void)

{
  int iVar1;
  
  iVar1 = DAT_0800aff8;
  if ((*DAT_0800aff0 * DAT_0800aff4 < *(float *)(DAT_0800aff8 + 0x30)) &&
     (*(char *)(DAT_0800aff8 + 4) == '\0')) {
    *(undefined4 *)(DAT_0800aff8 + 0x30) = DAT_0800affc;
    *(undefined1 *)(iVar1 + 4) = 1;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800b002 at 0x0800b002
// ---------------------------------------------------------------------------

undefined4 FUN_0800b002(void)

{
  return 1;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800b008 at 0x0800b008
// ---------------------------------------------------------------------------

undefined1 FUN_0800b008(void)

{
  char *pcVar1;
  
  if (*DAT_0800b038 != '\0') {
    return 1;
  }
  if (*DAT_0800b03c == '\0') {
    if (*DAT_0800b040 == '\x14') {
      pcVar1 = DAT_0800b048;
    }
    else {
      if (*DAT_0800b044 != '\0') {
        return 1;
      }
      pcVar1 = DAT_0800b04c;
    }
    if (*pcVar1 != '\0') {
      return 1;
    }
  }
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800b050 at 0x0800b050
// ---------------------------------------------------------------------------

void FUN_0800b050(void)

{
  int iVar1;
  char *pcVar2;
  undefined4 uVar3;
  
  pcVar2 = DAT_0800b118;
  iVar1 = DAT_0800b110;
  if (*(char *)(DAT_0800b110 + 2) == '\0') {
    if (*DAT_0800b114 * 0x40000000 < 0) {
      *(undefined1 *)(DAT_0800b110 + 0x20) = 0;
    }
    else {
      *(undefined1 *)(DAT_0800b110 + 0x21) = 0;
      *(char *)(iVar1 + 0x20) = *(char *)(iVar1 + 0x20) + '\x01';
      if (9 < *(byte *)(iVar1 + 0x20)) {
        *(undefined1 *)(iVar1 + 0x20) = 0;
        *(undefined1 *)(iVar1 + 2) = 1;
        if (*(char *)(iVar1 + 4) != '\0') {
          *(undefined1 *)(iVar1 + 4) = 0;
        }
        if ((*(char *)(iVar1 + 1) == '\0') && (*pcVar2 == '\0')) {
          *DAT_0800b11c = 0;
        }
        if (*(char *)(iVar1 + 3) == '\0') {
          *(undefined1 *)(iVar1 + 5) = 0;
          *(undefined1 *)(iVar1 + 6) = 0;
          *(undefined1 *)(iVar1 + 7) = 0;
          *(undefined1 *)(iVar1 + 8) = 0;
          *(undefined1 *)(iVar1 + 9) = 0;
          *(undefined1 *)(iVar1 + 10) = 0;
          *(undefined1 *)(iVar1 + 0xb) = 0;
        }
        *DAT_0800b120 = 0;
        *DAT_0800b124 = 0;
        if ((*pcVar2 == '\0') && (*(char *)(iVar1 + 5) != '\x02')) {
          *(undefined1 *)(iVar1 + 0x10) = 1;
        }
        uVar3 = 0xa2;
        goto LAB_0800b100;
      }
    }
  }
  else if (*DAT_0800b114 * 0x40000000 < 0) {
    *(undefined1 *)(DAT_0800b110 + 0x20) = 0;
    *(char *)(iVar1 + 0x21) = *(char *)(iVar1 + 0x21) + '\x01';
    if (9 < *(byte *)(iVar1 + 0x21)) {
      *(undefined1 *)(iVar1 + 0x21) = 0;
      *(undefined1 *)(iVar1 + 2) = 0;
      if ((*pcVar2 == '\0') && (*(undefined1 *)(iVar1 + 0x10) = 0, *DAT_0800b128 == '\x01')) {
        *DAT_0800b128 = '\0';
      }
      uVar3 = 0xa3;
LAB_0800b100:
      FUN_08019844(0,uVar3);
      return;
    }
  }
  else {
    *(undefined1 *)(DAT_0800b110 + 0x21) = 0;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800b12c at 0x0800b12c
// ---------------------------------------------------------------------------

void FUN_0800b12c(void)

{
  int iVar1;
  
  *DAT_0800b14c = 0;
  iVar1 = DAT_0800b150;
  *(undefined1 *)(DAT_0800b150 + 7) = 0;
  *(undefined1 *)(iVar1 + 0xe) = 1;
  if (*(char *)(DAT_0800b154 + 0x3b) == '\0') {
    FUN_0800ac9c();
    return;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800b158 at 0x0800b158
// ---------------------------------------------------------------------------

void FUN_0800b158(void)

{
  int iVar1;
  
  *DAT_0800b16c = 1;
  iVar1 = DAT_0800b170;
  *(undefined1 *)(DAT_0800b170 + 7) = 1;
  *(undefined1 *)(iVar1 + 0xe) = 0;
  FUN_0800acd8();
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800b174 at 0x0800b174
// ---------------------------------------------------------------------------

void FUN_0800b174(void)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = DAT_0800b19c;
  puVar1 = DAT_0800b198;
  if (DAT_0800b198[3] != '\0') {
    DAT_0800b198[3] = 0;
    *(undefined1 *)(iVar2 + 0x16) = *puVar1;
    *(ushort *)(iVar2 + 0x14) = (ushort)(byte)puVar1[1];
  }
  iVar3 = DAT_0800b1a0;
  *(undefined1 *)(DAT_0800b1a0 + 0x3f) = 0;
  *(undefined4 *)(iVar2 + 8) = 0;
  *(undefined4 *)(iVar2 + 0xc) = 0;
  *(undefined1 *)(iVar3 + 0x41) = 0;
  *(undefined2 *)(iVar2 + 0x12) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800b1a4 at 0x0800b1a4
// ---------------------------------------------------------------------------

void FUN_0800b1a4(void)

{
  *(undefined1 *)(DAT_0800b1c0 + 0xb) = 0;
  *DAT_0800b1c4 = 0x8000;
  *DAT_0800b1c8 = 8;
  *DAT_0800b1cc = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800b1d0 at 0x0800b1d0
// ---------------------------------------------------------------------------

void FUN_0800b1d0(void)

{
  *(undefined1 *)(DAT_0800b1d8 + 0xc) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800b1dc at 0x0800b1dc
// ---------------------------------------------------------------------------

void FUN_0800b1dc(void)

{
  int iVar1;
  
  iVar1 = DAT_0800b204;
  *(undefined1 *)(DAT_0800b204 + 6) = 1;
  *(undefined1 *)(iVar1 + 8) = 1;
  *DAT_0800b208 = 0;
  *DAT_0800b20c = 0;
  *(undefined1 *)(iVar1 + 0xe) = 1;
  *(undefined1 *)(iVar1 + 0xf) = 1;
  *(undefined1 *)(iVar1 + 2) = 2;
  FUN_0800c8f4();
  FUN_0800ac9c();
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800b210 at 0x0800b210
// ---------------------------------------------------------------------------

void FUN_0800b210(void)

{
  int iVar1;
  
  *DAT_0800b248 = 1;
  *DAT_0800b24c = 1;
  iVar1 = DAT_0800b250;
  *(undefined1 *)(DAT_0800b250 + 5) = 1;
  *(undefined1 *)(iVar1 + 7) = 1;
  *(undefined1 *)(iVar1 + 0xe) = 0;
  *(undefined1 *)(iVar1 + 0xf) = 0;
  *(undefined1 *)(iVar1 + 2) = 2;
  FUN_0800c940();
  FUN_0800acd8();
  if (*DAT_0800b254 == '\x01') {
    *DAT_0800b254 = '\0';
    *DAT_0800b258 = 0;
  }
  *DAT_0800b25c = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800b260 at 0x0800b260
// ---------------------------------------------------------------------------

void FUN_0800b260(void)

{
  int iVar1;
  
  *DAT_0800b280 = 0;
  iVar1 = DAT_0800b284;
  *(undefined1 *)(DAT_0800b284 + 5) = 0;
  *(undefined1 *)(iVar1 + 0xf) = 1;
  if (*(char *)(DAT_0800b288 + 0x3a) == '\0') {
    FUN_0800c8f4();
    return;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800b28c at 0x0800b28c
// ---------------------------------------------------------------------------

void FUN_0800b28c(void)

{
  int iVar1;
  
  *DAT_0800b2a0 = 1;
  iVar1 = DAT_0800b2a4;
  *(undefined1 *)(DAT_0800b2a4 + 5) = 1;
  *(undefined1 *)(iVar1 + 0xf) = 0;
  FUN_0800c940();
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800b2a8 at 0x0800b2a8
// ---------------------------------------------------------------------------

void FUN_0800b2a8(void)

{
  int iVar1;
  
  iVar1 = iRam0800b2bc;
  *(undefined1 *)(iRam0800b2bc + 9) = 0;
  *(undefined1 *)(iVar1 + 2) = 0;
  FUN_0800db18(100);
  FUN_08022f3c();
  *(undefined1 *)(DAT_0800b2c8 + 4) = 1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800b2c0 at 0x0800b2c0
// ---------------------------------------------------------------------------

void FUN_0800b2c0(void)

{
  *(undefined1 *)(DAT_0800b2c8 + 4) = 1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800b2cc at 0x0800b2cc
// ---------------------------------------------------------------------------

void FUN_0800b2cc(void)

{
  *(undefined1 *)(DAT_0800b2d4 + 4) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800b2d8 at 0x0800b2d8
// ---------------------------------------------------------------------------

void FUN_0800b2d8(void)

{
  undefined4 *puVar1;
  char *pcVar2;
  byte bVar3;
  int iVar4;
  
  bVar3 = 0;
  *(undefined1 *)(DAT_0800b38c + 0xd) = 1;
  puVar1 = DAT_0800b390;
  *DAT_0800b390 = 0xaaaa;
  FUN_08021858();
  iVar4 = DAT_0800b394;
  *(undefined4 *)(DAT_0800b394 + 0x14) = 0x1000;
  *DAT_0800b398 = 0x10;
  FUN_08011458();
  FUN_0800c500();
  *DAT_0800b39c = 0x80;
  *(undefined4 *)(iVar4 + 0x14) = 1;
  FUN_0800db18(10);
  FUN_0800c5ec();
  FUN_0801698c();
  pcVar2 = DAT_0800b3a0;
  do {
    do {
      *puVar1 = 0xaaaa;
      iVar4 = FUN_0801efb8();
    } while (iVar4 == 0);
    FUN_080112fc();
    FUN_0800db18(1);
    bVar3 = bVar3 + 1;
  } while ((bVar3 < 0x1e) && (*pcVar2 != '\0'));
  FUN_08017a20();
  FUN_080219cc();
  FUN_0801f478();
  FUN_0800a634();
  FUN_08021864();
  FUN_08011464();
  FUN_0800f46c();
  FUN_08016898();
  *(undefined4 *)(DAT_0800b3a4 + 4) = 0;
  *DAT_0800b3a8 = 0x80;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800b3ac at 0x0800b3ac
// ---------------------------------------------------------------------------

void FUN_0800b3ac(void)

{
  int iVar1;
  undefined2 *puVar2;
  
  iVar1 = DAT_0800b3c8;
  *(undefined1 *)(DAT_0800b3c8 + 9) = 1;
  *(undefined1 *)(iVar1 + 2) = 1;
  FUN_0800c940();
  FUN_0800acd8();
  iVar1 = DAT_0801fbb0;
  *(undefined2 *)(DAT_0801fbb0 + 8) = 1000;
  *(undefined2 *)(iVar1 + 10) = 1000;
  *(undefined2 *)(iVar1 + 0x20) = 1000;
  *(undefined2 *)(iVar1 + 0x22) = 1000;
  iVar1 = DAT_0801fbb4;
  *(undefined2 *)(DAT_0801fbb4 + 8) = 1000;
  *(undefined2 *)(iVar1 + 10) = 1000;
  *(undefined2 *)(iVar1 + 0x20) = 1000;
  *(undefined2 *)(iVar1 + 0x22) = 1000;
  iVar1 = DAT_0801fbb8;
  *(undefined2 *)(DAT_0801fbb8 + 0x10) = 1000;
  *(undefined2 *)(iVar1 + 0x12) = 1000;
  puVar2 = DAT_0801fbbc;
  *DAT_0801fbbc = 10;
  puVar2[1] = 500;
  *(undefined2 *)(DAT_0801fbc0 + 0x3c) = 10;
  iVar1 = DAT_0801fbc4;
  *(undefined1 *)(DAT_0801fbc4 + 8) = 0;
  *(undefined4 *)(puVar2 + 2) = DAT_0801fbc8;
  *(undefined1 *)(iVar1 + 9) = 4;
  *(undefined1 *)(iVar1 + 0x17) = 0;
  FUN_080218b8();
  FUN_0800db18(200);
  FUN_0800c940();
  FUN_0800acd8();
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800b3cc at 0x0800b3cc
// ---------------------------------------------------------------------------

void FUN_0800b3cc(void)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  
  puVar1 = DAT_0800b3f8;
  DAT_0800b3f8[3] = 1;
  iVar2 = DAT_0800b3fc;
  *puVar1 = *(undefined1 *)(DAT_0800b3fc + 0x16);
  puVar1[1] = (char)*(undefined2 *)(iVar2 + 0x14);
  iVar3 = DAT_0800b400;
  *(undefined1 *)(DAT_0800b400 + 0x3f) = 1;
  *(undefined4 *)(iVar2 + 8) = 0xffffffff;
  *(undefined4 *)(iVar2 + 0xc) = 0xffffffff;
  *(undefined1 *)(iVar2 + 0x16) = 1;
  *(undefined1 *)(iVar3 + 0x41) = 1;
  *(undefined2 *)(iVar2 + 0x12) = 0;
  *(undefined2 *)(iVar2 + 0x14) = 0x1e;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800b404 at 0x0800b404
// ---------------------------------------------------------------------------

void FUN_0800b404(void)

{
  int iVar1;
  
  iVar1 = DAT_0800b420;
  *(undefined1 *)(DAT_0800b420 + 0xb) = 1;
  *(undefined4 *)(iVar1 + 0x10) = 0;
  *DAT_0800b424 = 0x8000;
  *DAT_0800b428 = 8;
  *DAT_0800b42c = 1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800b430 at 0x0800b430
// ---------------------------------------------------------------------------

void FUN_0800b430(void)

{
  char cVar1;
  byte *pbVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  char *pcVar10;
  int iVar11;
  int iVar12;
  ushort *puVar13;
  undefined4 uVar14;
  byte local_60 [52];
  byte local_2c;
  byte local_28;
  
  iVar11 = DAT_0800b454;
  *(undefined1 *)(DAT_0800b454 + 0xc) = 1;
  *(undefined4 *)(iVar11 + 0x14) = 0;
  iVar11 = DAT_0800b45c;
  if (*DAT_0800b458 == '\0') {
    return;
  }
  *(undefined1 *)(DAT_0800b45c + 0x262) = 2;
  pcVar10 = DAT_0800a4ec;
  pcVar9 = DAT_0800a4e4;
  pcVar8 = DAT_0800a4dc;
  pcVar7 = DAT_0800a4d4;
  pcVar6 = DAT_0800a4d0;
  pcVar5 = DAT_0800a4cc;
  pcVar4 = DAT_0800a4c8;
  pcVar3 = DAT_0800a4c4;
  pbVar2 = DAT_0800a4c0;
  local_28 = 0;
  local_60[0] = 0x41;
  local_60[1] = 0x54;
  local_60[2] = 0x2b;
  local_60[3] = 0x4e;
  local_60[4] = 0x41;
  local_60[5] = 0x4d;
  local_60[6] = 0x45;
  local_60[7] = 0x20;
  if (0x17 < *DAT_0800a4c0) {
    return;
  }
  if (*DAT_0800a4c0 < 2) {
    return;
  }
  cVar1 = *(char *)(iVar11 + 0x262);
  if (cVar1 == '\x01') {
    if (*DAT_0800a4c4 == '\0') {
      return;
    }
    if (*DAT_0800a4d4 == '\0') goto LAB_0800a3c2;
    FUN_08015b28(1,0x2580);
    *pcVar7 = '\0';
    iVar12 = DAT_0800a4d8;
  }
  else if (cVar1 == '\x02') {
    if (*DAT_0800a4c8 == '\0') {
      return;
    }
    if (*DAT_0800a4dc == '\0') goto LAB_0800a3c2;
    FUN_08015b28(2,0x2580);
    *pcVar8 = '\0';
    iVar12 = DAT_0800a4e0;
  }
  else if (cVar1 == '\x03') {
    if (*DAT_0800a4cc == '\0') {
      return;
    }
    if (*DAT_0800a4e4 == '\0') goto LAB_0800a3c2;
    FUN_08015b28(3,0x2580);
    *pcVar9 = '\0';
    iVar12 = DAT_0800a4e8;
  }
  else {
    if (cVar1 != '\x04') goto LAB_0800a3c2;
    if (*DAT_0800a4d0 == '\0') {
      return;
    }
    if (*DAT_0800a4ec == '\0') goto LAB_0800a3c2;
    FUN_08015b28(4,0x2580);
    *pcVar10 = '\0';
    iVar12 = DAT_0800a4f0;
  }
  *(undefined2 *)(iVar12 + 0x260) = 0;
LAB_0800a3c2:
  local_28 = *pbVar2;
  for (local_2c = 0; local_2c < local_28; local_2c = local_2c + 1) {
    local_60[local_2c + 8] = pbVar2[local_2c + 1];
  }
  local_60[local_28 + 8] = 0xd;
  local_60[local_28 + 9] = 10;
  for (local_2c = 0; (uint)local_2c < local_28 + 10; local_2c = local_2c + 1) {
    *(byte *)((uint)local_2c + iVar11 + 0x12e) = local_60[local_2c];
  }
  *(ushort *)(iVar11 + 0x25a) = local_28 + 10;
  cVar1 = *(char *)(iVar11 + 0x262);
  if (cVar1 == '\x01') {
    if (*pcVar3 == '\0') {
      return;
    }
    puVar13 = DAT_0800a4f8;
  }
  else {
    if (cVar1 != '\x02') {
      if (cVar1 == '\x03') {
        if (*pcVar5 == '\0') {
          return;
        }
        uVar14 = DAT_0800a500;
      }
      else {
        if (cVar1 != '\x04') {
          return;
        }
        if (*pcVar6 == '\0') {
          return;
        }
        uVar14 = DAT_0800a4f4;
      }
      FUN_08020654(uVar14,0x525,0);
      FUN_08020654(uVar14,0x727,1);
      return;
    }
    if (*pcVar4 == '\0') {
      return;
    }
    puVar13 = DAT_0800a4fc;
  }
  *puVar13 = *puVar13 & 0xffdf;
  *puVar13 = *puVar13 | 0x80;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800b460 at 0x0800b460
// ---------------------------------------------------------------------------

void FUN_0800b460(void)

{
  uint uVar1;
  char cVar2;
  undefined2 *puVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  byte bVar7;
  int iVar8;
  undefined4 uVar9;
  float *pfVar10;
  uint in_fpscr;
  uint uVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  undefined4 uVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  ushort local_50;
  byte local_4c;
  float local_48;
  byte local_44;
  float local_40;
  
  puVar3 = DAT_0800b848;
  *(undefined4 *)(DAT_0800b848 + 6) = *(undefined4 *)(DAT_0800b848 + 2);
  iVar4 = DAT_0800b84c;
  pfVar10 = (float *)(puVar3 + -0x10);
  local_48 = (float)(*(int *)(puVar3 + 6) - *(int *)(puVar3 + 4));
  if ((int)(*pfVar10 / 10.0) < (int)local_48) {
LAB_0800b4ba:
    local_48 = 0.0;
LAB_0800b4c2:
    *(int *)(puVar3 + -10) = *(int *)(puVar3 + -10) - (int)local_48;
  }
  else {
    fVar13 = *pfVar10 / -10.0;
    fVar12 = (float)VectorSignedToFloat(local_48,(byte)(in_fpscr >> 0x16) & 3);
    uVar11 = in_fpscr & 0xfffffff | (uint)(fVar13 < fVar12) << 0x1f |
             (uint)(fVar13 == fVar12) << 0x1e;
    in_fpscr = uVar11 | (uint)(NAN(fVar13) || NAN(fVar12)) << 0x1c;
    bVar7 = (byte)(uVar11 >> 0x18);
    if (!(bool)(bVar7 >> 6 & 1) && bVar7 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) goto LAB_0800b4ba;
    if ((int)local_48 < 1) goto LAB_0800b4c2;
    fVar12 = (float)VectorSignedToFloat(local_48,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(DAT_0800b84c + 0x30) = *(float *)(DAT_0800b84c + 0x30) + fVar12;
  }
  fVar12 = DAT_0800b850;
  fVar13 = (float)VectorSignedToFloat(*(undefined4 *)(puVar3 + -10),(byte)(in_fpscr >> 0x16) & 3);
  uVar11 = in_fpscr & 0xfffffff;
  if (*pfVar10 * *(float *)(puVar3 + 0x22) < fVar13) {
    puVar3[-8] = puVar3[-8] + 1;
    fVar13 = (float)VectorUnsignedToFloat(*(undefined4 *)(puVar3 + -0xe),(byte)(uVar11 >> 0x16) & 3)
    ;
    *pfVar10 = *pfVar10 - *(float *)(puVar3 + 0x1c) * fVar12 * fVar13;
    *(undefined4 *)(puVar3 + -10) = 1;
    FUN_0801975c();
    FUN_08019844(0,7);
  }
  iVar5 = DAT_0800b854;
  fVar13 = (float)VectorSignedToFloat(*(undefined4 *)(puVar3 + -0xc),(byte)(uVar11 >> 0x16) & 3);
  uVar11 = uVar11 & 0xfffffff;
  if (*pfVar10 <= fVar13) {
    if (*(char *)(DAT_0800b854 + 0x3b) != '\0') goto LAB_0800b590;
    iVar8 = (int)*pfVar10;
  }
  else {
    if ((*(char *)(DAT_0800b854 + 0x3a) != '\0') && (*(char *)(iVar4 + 4) != '\0')) {
      fVar13 = (*DAT_0800b858 / fVar12) * *pfVar10;
      uVar1 = uVar11 | (uint)(fVar13 == *(float *)(iVar4 + 0x30)) << 0x1e;
      uVar11 = uVar1 | (uint)(*(float *)(iVar4 + 0x30) <= fVar13) << 0x1d;
      if (!(!(bool)((byte)(uVar11 >> 0x1d) & 1) || SUB41(uVar1 >> 0x1e,0))) goto LAB_0800b5b2;
      *(undefined1 *)(iVar4 + 4) = 0;
    }
LAB_0800b590:
    iVar8 = *(int *)(puVar3 + -0xc) + (int)local_48;
  }
  *(int *)(puVar3 + -0xc) = iVar8;
LAB_0800b5b2:
  *(undefined4 *)(puVar3 + 4) = *(undefined4 *)(puVar3 + 6);
  if (199 < *(byte *)(puVar3 + -6)) {
    *(undefined1 *)(iVar4 + 5) = 0;
  }
  if ((*(byte *)(puVar3 + -6) < 199) && (*(char *)(iVar5 + 0x3a) == '\0')) {
    *(short *)(iVar4 + 0x12) = *(short *)(iVar4 + 0x12) + 1;
    if (4 < *(ushort *)(iVar4 + 0x12)) {
      *(undefined2 *)(iVar4 + 0x12) = 0;
      *(undefined1 *)(iVar4 + 5) = 1;
    }
  }
  else {
    *(undefined2 *)(iVar4 + 0x12) = 0;
  }
  if (*(int *)(puVar3 + -0xc) < 1) {
    local_48 = DAT_0800b864;
    local_40 = DAT_0800b864;
    if (*(char *)(iVar5 + 0x3a) != '\0') {
      *(undefined4 *)(puVar3 + -0xc) = 0;
    }
  }
  else {
    uVar17 = FUN_080085d2(*pfVar10);
    uVar18 = FUN_08008526(*(undefined4 *)(puVar3 + -0xc));
    uVar9 = (undefined4)((ulonglong)DAT_0800b85c >> 0x20);
    uVar16 = (undefined4)DAT_0800b85c;
    uVar18 = FUN_08008364((int)uVar18,(int)((ulonglong)uVar18 >> 0x20),uVar16,uVar9);
    FUN_08008448((int)uVar18,(int)((ulonglong)uVar18 >> 0x20),(int)uVar17,
                 (int)((ulonglong)uVar17 >> 0x20));
    local_48 = (float)FUN_08008658();
    uVar17 = FUN_08008548(*(int *)(puVar3 + -0xe) * 100);
    uVar18 = FUN_08008526(*(undefined4 *)(puVar3 + -0xc));
    uVar18 = FUN_08008364((int)uVar18,(int)((ulonglong)uVar18 >> 0x20),uVar16,uVar9);
    FUN_08008448((int)uVar18,(int)((ulonglong)uVar18 >> 0x20),(int)uVar17,
                 (int)((ulonglong)uVar17 >> 0x20));
    bVar7 = FUN_080085a0();
    local_40 = (float)VectorUnsignedToFloat((uint)bVar7,(byte)(uVar11 >> 0x16) & 3);
  }
  pcVar6 = DAT_0800b86c;
  fVar13 = DAT_0800b868;
  uVar9 = VectorFloatToUnsigned(local_48 + DAT_0800b868,3);
  local_4c = (byte)uVar9;
  uVar9 = VectorFloatToUnsigned(local_40 + DAT_0800b868,3);
  local_44 = (byte)uVar9;
  if (200 < local_4c) {
    local_4c = 200;
  }
  if (200 < local_44) {
    local_44 = 200;
  }
  if ((((*DAT_0800b86c == '\0') && (*(char *)(iVar5 + 0x3a) != '\0')) && (199 < local_4c)) &&
     ((*(char *)(iVar4 + 3) == '\0' && (*(char *)(iVar4 + 5) == '\x01')))) {
    local_4c = 0xc6;
  }
  *(byte *)(puVar3 + -7) = local_4c;
  *(byte *)((int)puVar3 + -0xd) = local_44;
  if ((*DAT_0800b870 == 0) && (*DAT_0800b874 == 0)) {
    local_50 = (ushort)*(byte *)(puVar3 + -7);
  }
  else {
    fVar14 = (float)VectorUnsignedToFloat((uint)*DAT_0800b870,(byte)(uVar11 >> 0x16) & 3);
    iVar8 = (int)((*pfVar10 / fVar12) * fVar14);
    if ((*(int *)(puVar3 + -0xc) < 1) || (*(int *)(puVar3 + -0xc) <= iVar8)) {
      local_50 = 0;
    }
    else {
      fVar14 = (float)VectorSignedToFloat((100 - (uint)*DAT_0800b870) - (uint)*DAT_0800b874,
                                          (byte)(uVar11 >> 0x16) & 3);
      fVar15 = (float)VectorSignedToFloat(*(int *)(puVar3 + -0xc) - iVar8,(byte)(uVar11 >> 0x16) & 3
                                         );
      uVar9 = VectorFloatToUnsigned
                        (((fVar15 * fVar12) / ((*pfVar10 / fVar12) * fVar14)) * 2.0 + fVar13,3);
      local_50 = (ushort)uVar9;
    }
  }
  if (200 < local_50) {
    local_50 = 200;
  }
  if ((((*pcVar6 == '\0') && (*(char *)(iVar5 + 0x3a) != '\0')) && (199 < local_50)) &&
     ((*(char *)(iVar4 + 3) == '\0' && (*(char *)(iVar4 + 5) == '\x01')))) {
    local_50 = 0xc6;
  }
  *(char *)(puVar3 + -6) = (char)local_50;
  fVar12 = DAT_0800b878;
  if (*(char *)(iVar5 + 0x3a) == '\0') {
    cVar2 = *(char *)(iVar5 + 0x3b);
    *puVar3 = 0xffff;
    if (cVar2 == '\0') {
      puVar3[1] = 0xffff;
      *(undefined4 *)(puVar3 + 4) = 0xffffff;
      *(undefined4 *)(puVar3 + 6) = 0xffffff;
      *(undefined4 *)(puVar3 + 2) = 0xffffff;
    }
    else {
      if (0 < *(int *)(puVar3 + -0xc)) {
        fVar13 = *(float *)(puVar3 + 10);
        uVar11 = uVar11 & 0xfffffff | (uint)(fVar13 < 0.0) << 0x1f | (uint)(fVar13 == 0.0) << 0x1e;
        bVar7 = (byte)(uVar11 >> 0x18);
        if (!(bool)(bVar7 >> 6 & 1) && (bool)(bVar7 >> 7) == NAN(fVar13)) {
          fVar13 = (float)VectorSignedToFloat(*(undefined4 *)(puVar3 + -0xc),
                                              (byte)(uVar11 >> 0x16) & 3);
          uVar9 = VectorFloatToUnsigned((fVar13 * fVar12) / *(float *)(puVar3 + 10),3);
          puVar3[1] = (short)uVar9;
          return;
        }
      }
      puVar3[1] = 0;
    }
  }
  else {
    puVar3[1] = 0xffff;
    fVar13 = (float)VectorSignedToFloat(*(undefined4 *)(puVar3 + -0xc),(byte)(uVar11 >> 0x16) & 3);
    if (fVar13 < *pfVar10) {
      fVar13 = *(float *)(puVar3 + 8);
      uVar11 = uVar11 & 0xfffffff | (uint)(fVar13 < 0.0) << 0x1f | (uint)(fVar13 == 0.0) << 0x1e;
      bVar7 = (byte)(uVar11 >> 0x18);
      if (!(bool)(bVar7 >> 6 & 1) && (bool)(bVar7 >> 7) == NAN(fVar13)) {
        fVar13 = (float)VectorSignedToFloat(*(undefined4 *)(puVar3 + -0xc),
                                            (byte)(uVar11 >> 0x16) & 3);
        uVar9 = VectorFloatToUnsigned(((*pfVar10 - fVar13) * fVar12) / *(float *)(puVar3 + 8),3);
        *puVar3 = (short)uVar9;
        return;
      }
    }
    *puVar3 = 0;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800b8dc at 0x0800b8dc
// ---------------------------------------------------------------------------

void FUN_0800b8dc(void)

{
  float *pfVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  float *pfVar7;
  char *pcVar8;
  int iVar9;
  byte bVar10;
  uint uVar11;
  undefined8 uVar12;
  byte local_40;
  float local_38;
  float local_30;
  uint uStack_2c;
  uint local_18;
  
  pfVar7 = DAT_0800ba3c;
  iVar9 = DAT_0800ba38;
  pfVar1 = DAT_0800ba34;
  local_18 = 100;
  if (DAT_0800ba34[1] < *(float *)(DAT_0800ba38 + 4)) {
    DAT_0800ba34[1] = *DAT_0800ba3c - 0.25;
  }
  iVar2 = DAT_0800ba44;
  pcVar8 = DAT_0800ba40;
  if (*(char *)((int)pfVar1 + 0x16) == '\0') {
    if ((DAT_0800ba40[0x3a] == '\0') || (pfVar7[3] <= pfVar1[1])) {
      if (DAT_0800ba40[0x3f] == '\0') {
        return;
      }
LAB_0800b9ae:
      FUN_0800a040();
      return;
    }
    iVar9 = FUN_0800a040();
    if (((((iVar9 == 0) && (*pcVar8 == '\0')) && (pcVar8[0x12] == '\0')) &&
        ((pcVar8[0x1b] == '\0' && (pcVar8[0x39] == '\0')))) && (pcVar8[0x13] == '\0')) {
LAB_0800a158:
      pfVar1 = DAT_0800a2b8;
      local_38 = 0.0;
      local_30 = 0.0;
      uStack_2c = 0;
      if (0x3f000000 < (int)*DAT_0800a2b8) {
        *DAT_0800a2b8 = DAT_0800a2bc;
      }
      pbVar6 = DAT_0800a2d4;
      iVar5 = DAT_0800a2d0;
      iVar4 = DAT_0800a2cc;
      pbVar3 = DAT_0800a2c8;
      iVar2 = DAT_0800a2c4;
      iVar9 = DAT_0800a2c0;
      if (*pfVar1 < *(float *)(DAT_0800a2c0 + 0xc) - *(float *)(DAT_0800a2c4 + 0xc)) {
        for (local_40 = 0; local_40 < *pbVar6; local_40 = local_40 + 1) {
          if (*pfVar1 < *(float *)(DAT_0800a2d8 + (uint)local_40 * 4 + 4) - *(float *)(iVar2 + 0xc))
          {
            if (local_40 < *pbVar3) {
              uVar11 = (uint)local_40;
            }
            else {
              uVar11 = ((uint)local_40 - (uint)*pbVar3) + 0x10;
            }
            uVar11 = FUN_080081d4(1,0,uVar11,local_18);
            local_38 = (float)(uVar11 | (uint)local_38);
            uVar12 = FUN_080081d4(1,0,local_40);
            local_30 = (float)((uint)uVar12 | (uint)local_30);
            *(undefined1 *)(iVar5 + 0x3f) = 1;
            if (*(char *)((int)pfVar1 + 0x16) == '\x01') {
              *(undefined1 *)(iVar5 + 0x41) = 1;
            }
            *(char *)(iVar4 + 4) = *(char *)(iVar4 + 4) + '\x01';
            *(undefined2 *)(pfVar1 + 8) = 0x50;
            *(undefined2 *)((int)pfVar1 + 0x22) = 0x50;
            local_18 = uStack_2c;
            uStack_2c = (uint)((ulonglong)uVar12 >> 0x20) | uStack_2c;
          }
        }
        pfVar1[2] = local_38;
        pfVar1[3] = local_30;
        if (((*DAT_0800a2dc == '\0') && (*(char *)(iVar4 + 4) == '\x01')) &&
           ((*(float *)(iVar9 + 4) - DAT_0800a2e0 < *(float *)(iVar9 + 0xc) ||
            (*(char *)(iVar5 + 0x12) != '\0')))) {
          *(undefined1 *)(iVar5 + 0x3f) = 0;
          *(undefined2 *)(pfVar1 + 4) = 0;
          *(undefined1 *)(iVar4 + 4) = 0;
          pfVar1[2] = 0.0;
          pfVar1[3] = 0.0;
        }
      }
      return;
    }
  }
  else if (*(char *)((int)pfVar1 + 0x16) == '\x01') {
    if ((int)(pfVar7[3] - *(float *)(iVar9 + 0xc)) < 0x3f000001) {
      if (DAT_0800ba40[0x41] == '\0') {
        *(undefined2 *)((int)pfVar1 + 0x12) = 0;
        if (*(char *)(iVar2 + 5) == '\0') {
          return;
        }
        if (pfVar7[3] <= pfVar1[1]) {
          return;
        }
        if ((pcVar8[0x13] == '\x01') && (pcVar8[0x12] == '\0')) {
          return;
        }
        if (pcVar8[0x3b] != '\0') {
          return;
        }
        if (pcVar8[0x39] != '\0') {
          return;
        }
        if (pcVar8[0x1b] != '\0') {
          return;
        }
        if (pcVar8[0x3d] == '\0') {
          bVar10 = 0x1e;
        }
        else {
          bVar10 = 3;
        }
        local_18 = (uint)bVar10;
        if (pfVar7[3] - *(float *)(iVar9 + 0xc) <= *pfVar1) {
          *(undefined1 *)(iVar2 + 0x14) = 0;
          return;
        }
        *(char *)(iVar2 + 0x14) = *(char *)(iVar2 + 0x14) + '\x01';
        if (*(byte *)(iVar2 + 0x14) < bVar10) {
          return;
        }
        *(undefined1 *)(iVar2 + 0x14) = 0;
        goto LAB_0800a158;
      }
      if (DAT_0800ba40[0x3d] != '\0') {
        return;
      }
      goto LAB_0800b9ae;
    }
    if (DAT_0800ba40[0x3f] != '\0') {
      FUN_08008c40();
      pcVar8[0x3f] = '\0';
      *(undefined2 *)(pfVar1 + 4) = 0;
      *(undefined1 *)(iVar2 + 0x10) = 0;
      pfVar1[2] = 0.0;
      pfVar1[3] = 0.0;
      *(undefined2 *)((int)pfVar1 + 0x12) = 0;
      pcVar8[0x41] = '\0';
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800ba48 at 0x0800ba48
// ---------------------------------------------------------------------------

undefined8 FUN_0800ba48(byte *param_1,char param_2)

{
  short sVar1;
  bool bVar2;
  undefined4 local_10;
  
  sVar1 = 0;
  while( true ) {
    local_10 = CONCAT22(local_10._2_2_,sVar1);
    bVar2 = param_2 == '\0';
    param_2 = param_2 + -1;
    if (bVar2) break;
    sVar1 = (ushort)*param_1 + sVar1;
    param_1 = param_1 + 1;
  }
  return CONCAT44(local_10,(uint)(byte)sVar1);
}



// ---------------------------------------------------------------------------
// Function: FUN_0800ba74 at 0x0800ba74
// ---------------------------------------------------------------------------

void FUN_0800ba74(void)

{
  int iVar1;
  char *pcVar2;
  ushort *puVar3;
  int iVar4;
  
  iVar1 = DAT_0800bb80;
  if (*(char *)(DAT_0800bb80 + 0x3a) == '\0') {
    *(undefined1 *)(DAT_0800bb80 + 0x3a) = 1;
    pcVar2 = DAT_0800bb84;
    if (*(char *)(iVar1 + 0x3b) != '\0') {
      *(undefined1 *)(iVar1 + 0x3b) = 0;
      if ((*(char *)(iVar1 + 0x4a) != '\0') && (*pcVar2 == '\0')) {
        *(undefined1 *)(iVar1 + 0x4b) = 0;
        FUN_08016620();
        FUN_08016608();
        FUN_08019844(0,0x80);
      }
      iVar4 = DAT_0800bb8c;
      puVar3 = DAT_0800bb88;
      if (999 < *DAT_0800bb88) {
        *(ushort *)(DAT_0800bb8c + 8) = *DAT_0800bb88;
        if (*DAT_0800bb90 == '\0') {
          *(undefined1 *)(iVar1 + 0x13) = 1;
        }
        *(undefined2 *)(iVar4 + 0x12) = 0;
        *(ushort *)(iVar4 + 0x20) = *puVar3;
        if (*(char *)(iVar1 + 0x20) == '\x01') {
          *(undefined1 *)(iVar1 + 0x17) = 1;
        }
        *(undefined2 *)(iVar4 + 0x24) = 0;
      }
    }
    if ((*(char *)(iVar1 + 0x4a) != '\0') && (*pcVar2 == '\0')) {
      FUN_0800ac9c();
    }
    FUN_0800f06c();
  }
  iVar4 = DAT_0800bb94;
  if (((*(byte *)(iVar1 + 0x39) & 3) != 0) && (*(char *)(DAT_0800bb94 + 0x13) == '\x01')) {
    *DAT_0800bb98 = 0;
    *(undefined2 *)(iVar4 + 0x16) = 0;
    if ((int)((uint)*(byte *)(iVar1 + 0x39) << 0x1e) < 0) {
      FUN_08019844(0xd,10);
    }
    if ((*(byte *)(iVar1 + 0x39) & 1) != 0) {
      FUN_08019844(0xe,10);
    }
    *(byte *)(iVar1 + 0x39) = *(byte *)(iVar1 + 0x39) & 0xfc;
    FUN_0800c940();
  }
  iVar4 = DAT_0800bba0;
  if ((*DAT_0800bb9c != '\0') && (*(char *)(iVar1 + 0x4c) == '\0')) {
    if (*DAT_0800bba8 < *(float *)(DAT_0800bba4 + 0x14)) {
      *(short *)(DAT_0800bba0 + 8) = *(short *)(DAT_0800bba0 + 8) + 1;
      if (2 < *(ushort *)(iVar4 + 8)) {
        *(undefined2 *)(iVar4 + 8) = 0;
        FUN_0800f4c8();
        thunk_FUN_0800ceec();
        *(undefined1 *)(iVar1 + 0x4c) = 1;
      }
      goto LAB_0800bb76;
    }
  }
  *(undefined2 *)(DAT_0800bba0 + 8) = 0;
LAB_0800bb76:
  FUN_0800f46c();
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800bbac at 0x0800bbac
// ---------------------------------------------------------------------------

void FUN_0800bbac(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = DAT_0800bbf8;
  iVar1 = DAT_0800bbf4;
  *(undefined2 *)(DAT_0800bbf8 + 0x26) = 900;
  if (*(char *)(iVar1 + 0x3a) == '\0') {
    *(short *)(iVar2 + 0x22) = *(short *)(iVar2 + 0x22) + 1;
    if (*(ushort *)(iVar2 + 0x26) <= *(ushort *)(iVar2 + 0x22)) {
      *(undefined2 *)(iVar2 + 0x22) = 0;
      *(short *)(iVar2 + 0x24) = *(short *)(iVar2 + 0x24) + 1;
      iVar1 = DAT_0800bbfc;
      *(undefined2 *)(DAT_0800bbfc + 0x20) = *(undefined2 *)(iVar2 + 0x24);
      if (*(ushort *)(iVar1 + 0x22) < *(ushort *)(iVar1 + 0x20)) {
        *(undefined2 *)(iVar1 + 0x22) = *(undefined2 *)(iVar1 + 0x20);
      }
      FUN_0801975c();
      return;
    }
  }
  else {
    *(undefined2 *)(iVar2 + 0x22) = 0;
    *(undefined2 *)(iVar2 + 0x24) = 0;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800bc04 at 0x0800bc04
// ---------------------------------------------------------------------------

undefined1 FUN_0800bc04(void)

{
  undefined1 uVar1;
  
  if ((((*DAT_0800bc48 == 'B') && (DAT_0800bc48[1] == 'T')) && (DAT_0800bc48[0xb] == 'W')) &&
     (((DAT_0800bc48[0xc] == 'D' && (DAT_0800bc48[0xd] == 'K')) && (DAT_0800bc48[0xe] == 'J')))) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800bc4c at 0x0800bc4c
// ---------------------------------------------------------------------------

void FUN_0800bc4c(void)

{
  char *pcVar1;
  int iVar2;
  uint local_10;
  
  iVar2 = DAT_0800bcbc;
  pcVar1 = DAT_0800bcb8;
  local_10 = 0;
  while ((byte)local_10 < 0x18) {
    *(char *)(iVar2 + local_10) = pcVar1[local_10 + 1];
    local_10 = (uint)(byte)((byte)local_10 + 1);
  }
  if ((((*pcVar1 == '\x18') && (pcVar1[1] == 'B')) && (pcVar1[2] == 'T')) &&
     (((pcVar1[0xc] == 'W' && (pcVar1[0xd] == 'D')) &&
      ((pcVar1[0xe] == 'K' && (pcVar1[0xf] == 'J')))))) {
    *DAT_0800bcc0 = 1;
    return;
  }
  *DAT_0800bcc0 = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800bcc4 at 0x0800bcc4
// ---------------------------------------------------------------------------

void FUN_0800bcc4(undefined4 param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  byte *pbVar4;
  ushort *puVar5;
  undefined2 *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  short sVar10;
  undefined4 local_28;
  uint local_24;
  
  local_28 = param_3;
  local_24 = param_4;
  FUN_0800e570(&local_28,&local_24);
  puVar5 = DAT_0800bfb8;
  pbVar4 = DAT_0800bfb0;
  pcVar3 = DAT_0800bfac;
  pcVar2 = DAT_0800bfa8;
  iVar1 = DAT_0800bfa4;
  if (((char)local_28 == '\x01') && ((char)local_24 == '\x01')) {
    *(undefined2 *)(DAT_0800bfa4 + 10) = 0;
    *(undefined2 *)(iVar1 + 0xc) = 0;
    if (*(float *)(DAT_0800bfb4 + 0x10) <= *(float *)(DAT_0800bfb4 + 0x14)) {
      if (*(float *)(DAT_0800bfb4 + 0x10) < *(float *)(DAT_0800bfb4 + 0x14)) {
        FUN_0800ba74();
      }
    }
    else {
      FUN_0800c818();
    }
  }
  else if (((char)local_28 == '\x01') && ((local_24 & 0xff) == 0)) {
    *(undefined2 *)(DAT_0800bfa4 + 10) = 0;
    *(undefined2 *)(iVar1 + 0xc) = 0;
    *(undefined2 *)(iVar1 + 0xe) = 0;
    FUN_0800c818();
    if ((pbVar4[0x4a] != 0) && ((*pcVar2 == '\0' && (pbVar4[0x4b] == 0)))) {
      pbVar4[0x4b] = 1;
      if ((*DAT_0800bfbc == '\x05') || (*DAT_0800bfbc == '\n')) {
        FUN_0801662c();
        FUN_08016614();
      }
      FUN_08019844(0,0x7f);
    }
    if (*pcVar3 != '\0') {
      if (((int)((uint)*pbVar4 << 0x1e) < 0) && (pbVar4[0x4c] != 0)) {
        FUN_0800c8f4();
      }
      if (((pbVar4[0x1b] & 3) != 0) && (pbVar4[0x4c] != 0)) {
        FUN_0800c8f4();
      }
      if (((int)((uint)pbVar4[0x51] << 0x1d) < 0) && (pbVar4[0x4c] != 0)) {
        FUN_0800c8f4();
      }
      if (((pbVar4[0x10] & 3) != 0) && (pbVar4[0x4c] != 0)) {
        FUN_0800c8f4();
      }
    }
  }
  else if (((char)local_28 == '\0') && ((local_24 & 0xff) == 1)) {
    *(undefined2 *)(DAT_0800bfa4 + 10) = 0;
    *(undefined2 *)(iVar1 + 0x10) = 0;
    FUN_0800ba74();
    iVar9 = DAT_0800bfd4;
    iVar8 = DAT_0800bfd0;
    iVar7 = DAT_0800bfcc;
    if ((*(short *)(DAT_0800bfcc + 8) != (ushort)((*(byte *)(DAT_0800bfd0 + 3) & 0x7f) * 100)) ||
       (*(short *)(DAT_0800bfcc + 0x20) != (ushort)((*(byte *)(DAT_0800bfd4 + 10) & 0x7f) * 100))) {
      if ((uint)*(ushort *)(iVar1 + 0xc) < *puVar5 / 1000) {
        *(short *)(iVar1 + 0xc) = *(short *)(iVar1 + 0xc) + 1;
      }
      else {
        *(undefined2 *)(iVar1 + 0xc) = 0;
        *(ushort *)(iVar7 + 8) = (*(byte *)(iVar8 + 3) & 0x7f) * 100;
        *(ushort *)(iVar7 + 0x20) = (*(byte *)(iVar9 + 10) & 0x7f) * 100;
      }
    }
    if ((*pcVar3 != '\0') &&
       ((((pbVar4[0x12] & 0x13) != 0 || ((*pbVar4 & 1) != 0)) && (pbVar4[0x4d] != 0)))) {
      if ((uint)*(ushort *)(iVar1 + 0xe) < *puVar5 / 1000) {
        *(short *)(iVar1 + 0xe) = *(short *)(iVar1 + 0xe) + 1;
      }
      else {
        *(undefined2 *)(iVar1 + 0xe) = 0;
        FUN_0800ac9c();
      }
    }
  }
  else {
    *(undefined2 *)(DAT_0800bfa4 + 0xc) = 0;
    *(undefined2 *)(iVar1 + 0x10) = 0;
    if ((pbVar4[0x3a] != 0) && (pbVar4[0x3a] = 0, *(char *)(DAT_0800bfc0 + 0xec) != '\0')) {
      FUN_0800f482();
    }
    puVar6 = DAT_0800bfc4;
    if ((pbVar4[0x3b] != 0) && (pbVar4[0x3b] = 0, *DAT_0800bfc8 == '\x02')) {
      *(undefined1 *)((int)puVar6 + 0x19) = 0;
    }
    if (*pcVar3 != '\0') {
      if ((((pbVar4[0x12] & 0x13) != 0) || ((*pbVar4 & 1) != 0)) && (pbVar4[0x4d] != 0)) {
        if ((uint)*(ushort *)(iVar1 + 10) < *puVar5 / 100) {
          if (pbVar4[0x3d] == 0) {
            sVar10 = *(short *)(iVar1 + 10) + 1;
          }
          else {
            sVar10 = *(short *)(iVar1 + 10) + 10;
          }
          *(short *)(iVar1 + 10) = sVar10;
        }
        else {
          *(undefined2 *)(iVar1 + 10) = 0;
          FUN_0800ac9c();
        }
      }
      if (((int)((uint)*pbVar4 << 0x1e) < 0) && (pbVar4[0x4c] != 0)) {
        FUN_0800c8f4();
      }
      if (((pbVar4[0x1b] & 3) != 0) && (pbVar4[0x4c] != 0)) {
        FUN_0800c8f4();
      }
      if (((int)((uint)pbVar4[0x39] << 0x1d) < 0) && (pbVar4[0x4d] != 0)) {
        FUN_0800ac9c();
      }
      if (((int)((uint)pbVar4[0x51] << 0x1d) < 0) && (pbVar4[0x4d] != 0)) {
        FUN_0800ac9c();
      }
      if (((int)((uint)pbVar4[0x51] << 0x1d) < 0) && (pbVar4[0x4c] != 0)) {
        FUN_0800c8f4();
      }
      if (((pbVar4[0x10] & 3) != 0) && (pbVar4[0x4d] != 0)) {
        FUN_0800ac9c();
      }
      if (((pbVar4[0x10] & 3) != 0) && (pbVar4[0x4c] != 0)) {
        FUN_0800c8f4();
      }
    }
    if (((pbVar4[0x4a] != 0) && (pbVar4[0x4d] != 0)) && (*pcVar2 == '\0')) {
      FUN_0800ac9c();
    }
    *puVar6 = 0xffff;
    puVar6[1] = 0xffff;
    FUN_0801757c();
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800bfd8 at 0x0800bfd8
// ---------------------------------------------------------------------------

void FUN_0800bfd8(void)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  short sVar4;
  
  pcVar2 = DAT_0800c064;
  pcVar1 = DAT_0800c060;
  if (*(int *)(DAT_0800c058 + 4) != DAT_0800c05c) {
    return;
  }
  if (*DAT_0800c060 != '\0') goto LAB_0800c03c;
  *DAT_0800c060 = '\x01';
  iVar3 = DAT_0800c06c;
  *(ushort *)(DAT_0800c06c + 8) = (*(byte *)(DAT_0800c068 + 3) & 0x7f) * 100;
  if (*(ushort *)(iVar3 + 8) < 0x1f5) {
    if (200 < *(ushort *)(iVar3 + 8)) {
      sVar4 = *(short *)(iVar3 + 8) + -100;
      goto LAB_0800c01c;
    }
  }
  else {
    sVar4 = *(ushort *)(iVar3 + 8) - 300;
LAB_0800c01c:
    *(short *)(iVar3 + 8) = sVar4;
  }
  *(ushort *)(iVar3 + 0x20) = (*(byte *)(DAT_0800c070 + 10) & 0x7f) * 100;
  if ((*DAT_0800c074 == '\0') && (*pcVar2 == '\0')) {
    *DAT_0800c078 = 0;
  }
LAB_0800c03c:
  pcVar1[1] = '\0';
  pcVar1[6] = '\0';
  pcVar1[7] = '\0';
  pcVar1[2] = '\0';
  if ((*pcVar2 == '\0') && (*DAT_0800c07c != '\x02')) {
    *DAT_0800c080 = 1;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800c084 at 0x0800c084
// ---------------------------------------------------------------------------

undefined8 FUN_0800c084(undefined4 param_1,undefined1 param_2)

{
  short sVar1;
  short sVar2;
  uint uVar3;
  undefined6 uStack_16;
  
  FUN_08018708(DAT_0800c0c8);
  sVar1 = FUN_08017b04(param_1,param_2);
  sVar2 = FUN_08017b04(DAT_0800c0c8,0xc);
  uVar3 = FUN_08018768(0x100);
  *(bool *)DAT_0800c0cc = uVar3 == (ushort)(sVar2 + sVar1);
  return CONCAT62(uStack_16,sVar2 + sVar1);
}



// ---------------------------------------------------------------------------
// Function: FUN_0800c0d0 at 0x0800c0d0
// ---------------------------------------------------------------------------

ulonglong FUN_0800c0d0(byte *param_1,char param_2)

{
  uint local_10;
  
  local_10 = local_10 & 0xffffff00;
  while (param_2 = param_2 + -1, param_2 != '\0') {
    local_10 = CONCAT31(local_10._1_3_,*param_1 ^ (byte)local_10);
    param_1 = param_1 + 1;
  }
  return CONCAT44(local_10,local_10) & 0xffffffff000000ff;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800c108 at 0x0800c108
// ---------------------------------------------------------------------------

undefined4 FUN_0800c108(void)

{
  ushort uVar1;
  ushort uVar2;
  char *pcVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 local_1c;
  
  pcVar3 = DAT_0800c21c;
  if (DAT_0800c21c[1] == '\0') {
    return 0;
  }
  iVar4 = FUN_0800bc04();
  if ((iVar4 == 0) || (*pcVar3 == '\0')) {
    local_1c = 1;
    goto LAB_0800c20e;
  }
  uVar5 = (uint)*(byte *)(DAT_0800c220 + 6) * 0x10000 + (uint)*(byte *)(DAT_0800c220 + 7) * 0x100 +
          (uint)*(byte *)(DAT_0800c220 + 8);
  uVar6 = (uint)*(byte *)(DAT_0800c220 + 0x1e) * 0x10000 +
          (uint)*(byte *)(DAT_0800c220 + 0x1f) * 0x100 + (uint)*(byte *)(DAT_0800c220 + 0x20);
  if (uVar6 <= uVar5 && uVar5 != uVar6) {
LAB_0800c160:
    local_1c = 0x14;
  }
  else {
    if (uVar6 <= uVar5) {
      uVar1 = CONCAT11(*(undefined1 *)(DAT_0800c220 + 0xf),*(undefined1 *)(DAT_0800c220 + 0x10));
      uVar2 = CONCAT11(*(undefined1 *)(DAT_0800c220 + 0x27),*(undefined1 *)(DAT_0800c220 + 0x28));
      if (uVar1 < uVar2) goto LAB_0800c160;
      if (uVar1 <= uVar2) {
        uVar1 = CONCAT11(*(undefined1 *)(DAT_0800c220 + 0x11),*(undefined1 *)(DAT_0800c220 + 0x12));
        uVar2 = CONCAT11(*(undefined1 *)(DAT_0800c220 + 0x29),*(undefined1 *)(DAT_0800c220 + 0x2a));
        if (uVar1 < uVar2) goto LAB_0800c160;
        if (uVar1 <= uVar2) {
          uVar1 = CONCAT11(*(undefined1 *)(DAT_0800c220 + 0x13),*(undefined1 *)(DAT_0800c220 + 0x14)
                          );
          uVar2 = CONCAT11(*(undefined1 *)(DAT_0800c220 + 0x2b),*(undefined1 *)(DAT_0800c220 + 0x2c)
                          );
          if (uVar1 < uVar2) goto LAB_0800c160;
          if (uVar1 <= uVar2) {
            uVar5 = (uint)*(byte *)(DAT_0800c220 + 0x17) +
                    (uint)*(byte *)(DAT_0800c220 + 0x15) * 0x10000 +
                    (uint)*(byte *)(DAT_0800c220 + 0x16) * 0x100;
            uVar6 = (uint)*(byte *)(DAT_0800c220 + 0x2d) * 0x10000 +
                    (uint)*(byte *)(DAT_0800c220 + 0x2e) * 0x100 +
                    (uint)*(byte *)(DAT_0800c220 + 0x2f);
            if (uVar5 < uVar6) goto LAB_0800c160;
            if (uVar5 <= uVar6) {
              local_1c = 2;
              goto LAB_0800c20e;
            }
          }
        }
      }
    }
    local_1c = 0x1d;
  }
LAB_0800c20e:
  pcVar3[1] = '\0';
  FUN_08015efc();
  return local_1c;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800c260 at 0x0800c260
// ---------------------------------------------------------------------------

void FUN_0800c260(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_18 [2];
  
  iVar2 = DAT_0800c2a0;
  uVar1 = DAT_0800c29c;
  local_18[0] = 0;
  *(undefined4 *)(DAT_0800c2a0 + 8) = DAT_0800c29c;
  FUN_080127e0(0x180,local_18,4);
  *(undefined4 *)(iVar2 + 0xc) = uVar1;
  FUN_080127e0(0x184,local_18,4);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800c400 at 0x0800c400
// ---------------------------------------------------------------------------

void FUN_0800c400(void)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  undefined4 uVar5;
  short local_20;
  
  pfVar1 = DAT_0800c4f4;
  iVar4 = FUN_08009c48(DAT_0800c4f4 + 1,1);
  fVar3 = DAT_0800c4fc;
  fVar2 = DAT_0800c4f8;
  if (iVar4 != 0) {
    if (0.0 <= pfVar1[1]) {
      uVar5 = VectorFloatToUnsigned(pfVar1[1] * DAT_0800c4fc,3);
      local_20 = (short)uVar5;
    }
    else {
      uVar5 = VectorFloatToUnsigned(pfVar1[1] * DAT_0800c4f8,3);
      local_20 = ~(ushort)uVar5 + 1;
    }
    if (local_20 == -1) {
      local_20 = 0;
    }
    iVar4 = FUN_08021fae(0x42,local_20);
    if ((iVar4 != 0) && (iVar4 = FUN_08009c48(DAT_0800c4f4,2), iVar4 != 0)) {
      if (0.0 <= *pfVar1) {
        uVar5 = VectorFloatToUnsigned(*pfVar1 * fVar3,3);
        local_20 = (short)uVar5;
      }
      else {
        uVar5 = VectorFloatToUnsigned(*pfVar1 * fVar2,3);
        local_20 = ~(ushort)uVar5 + 1;
      }
      if (local_20 == -1) {
        local_20 = 0;
      }
      iVar4 = FUN_08021fae(0x40,local_20);
      if (iVar4 != 0) {
        FUN_08019844(0,0x59);
        FUN_08013448();
        return;
      }
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800c500 at 0x0800c500
// ---------------------------------------------------------------------------

void FUN_0800c500(void)

{
  *DAT_0800c518 = *DAT_0800c518 & 0xfffffffe;
  *DAT_0800c51c = *DAT_0800c51c & 0xfffffffe;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800c520 at 0x0800c520
// ---------------------------------------------------------------------------

void FUN_0800c520(void)

{
  char *pcVar1;
  int iVar2;
  
  pcVar1 = DAT_0800c584;
  iVar2 = DAT_0800c580;
  if (*DAT_0800c57c != '\x01') {
    if (((*(char *)(DAT_0800c580 + 0x3a) == '\0') || (*DAT_0800c584 != '\0')) ||
       (*DAT_0800c588 != '\0')) {
      pcVar1[6] = '\0';
      pcVar1[7] = '\0';
    }
    else {
      *(short *)(DAT_0800c584 + 6) = *(short *)(DAT_0800c584 + 6) + 1;
      if (6000 < *(ushort *)(pcVar1 + 6)) {
        pcVar1[6] = '\0';
        pcVar1[7] = '\0';
        pcVar1[2] = '\x01';
        if (*(char *)(iVar2 + 0x4d) == '\x01') {
          FUN_0800ac9c();
        }
      }
    }
    if ((*(char *)(iVar2 + 0x3b) != '\0') && (pcVar1[2] != '\0')) {
      pcVar1[2] = '\0';
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800c58c at 0x0800c58c
// ---------------------------------------------------------------------------

void FUN_0800c58c(void)

{
  char *pcVar1;
  
  pcVar1 = DAT_0800c5e0;
  if (*DAT_0800c5d8 != '\x01') {
    if ((*DAT_0800c5dc == '\0') && (*DAT_0800c5e0 == '\0')) {
      DAT_0800c5e0[4] = '\0';
      pcVar1[3] = '\0';
    }
    else if (0x40000000 < *(int *)(DAT_0800c5e4 + 0x10)) {
      DAT_0800c5e0[4] = DAT_0800c5e0[4] + '\x01';
      if (0x13 < (byte)pcVar1[4]) {
        pcVar1[4] = '\0';
        pcVar1[3] = '\x01';
        if (*(char *)(DAT_0800c5e8 + 0x4c) == '\x01') {
          FUN_0800c8f4();
          return;
        }
      }
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800c5ec at 0x0800c5ec
// ---------------------------------------------------------------------------

void FUN_0800c5ec(void)

{
  uint uVar1;
  
  uVar1 = DAT_e000e010;
  DAT_e000e010 = uVar1 & 0xfffffffe;
  DAT_e000e018 = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800c5fe at 0x0800c5fe
// ---------------------------------------------------------------------------

void FUN_0800c5fe(undefined1 *param_1)

{
  *param_1 = 0;
  *(undefined2 *)(param_1 + 300) = 0;
  *(undefined2 *)(param_1 + 0x25e) = 0;
  param_1[0x25c] = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800c614 at 0x0800c614
// ---------------------------------------------------------------------------

void FUN_0800c614(void)

{
  int iVar1;
  byte *pbVar2;
  
  iVar1 = DAT_0800c6f8;
  if ((((*DAT_0800c6e0 == '\0') && (*DAT_0800c6e4 != '\x01')) && (*DAT_0800c6e8 != '\x01')) &&
     ((*DAT_0800c6ec != '\x01' && (*DAT_0800c6f0 != '\x01')))) {
    if (*DAT_0800c6f4 == '\x14') {
      *(undefined1 *)(DAT_0800c6f8 + 0x38) = 1;
      *(undefined1 *)(iVar1 + 0x39) = 1;
    }
    else if (*DAT_0800c6f4 == '\x1d') {
      *DAT_0800c6fc = 1;
      *DAT_0800c700 = 1;
    }
    pbVar2 = DAT_0800c704;
    if ((((DAT_0800c704[0x4c] == 0) && ((DAT_0800c704[0x39] & 3) == 0)) &&
        (((DAT_0800c704[0x1b] & 3) == 0 &&
         (((-1 < (int)((uint)*DAT_0800c704 << 0x1e) &&
           (-1 < (int)((uint)DAT_0800c704[0x51] << 0x1d))) && ((DAT_0800c704[0x10] & 3) == 0))))))
       && ((*DAT_0800c708 != '\x11' && (*DAT_0800c70c == '\0')))) {
      FUN_0800c940();
    }
    if (((pbVar2[0x4d] == 0) && (-1 < (int)((uint)pbVar2[0x39] << 0x1d))) &&
       (((pbVar2[0x12] & 0x13) == 0 &&
        (((((*pbVar2 & 1) == 0 && (-1 < (int)((uint)pbVar2[0x51] << 0x1d))) &&
          (*DAT_0800c710 == '\0')) && (*DAT_0800c714 == '\0')))))) {
      FUN_0800acd8();
      return;
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800c718 at 0x0800c718
// ---------------------------------------------------------------------------

void FUN_0800c718(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 uVar4;
  undefined4 extraout_r2;
  undefined4 extraout_r3;
  undefined4 unaff_r4;
  
  FUN_0800e5f0();
  FUN_0800e600();
  FUN_0800e9bc();
  FUN_0800ee00();
  FUN_0800ebbc();
  FUN_08017780();
  FUN_080188d0();
  FUN_0800e7f8();
  FUN_0800e87c();
  FUN_0800efe8();
  FUN_0800e91c();
  FUN_0800ded0();
  iVar3 = DAT_0800e440;
  iVar2 = DAT_0800e43c;
  iVar1 = DAT_0800e438;
  if (*(char *)(DAT_0800e438 + 0x25) == '\0') goto LAB_0800e430;
  if (*(char *)(DAT_0800e43c + 0x3b) == '\0') {
LAB_0800e370:
    *(undefined2 *)(DAT_0800e438 + 0x34) = 0;
  }
  else if ((*(byte *)(DAT_0800e43c + 8) & 1) == 0) {
    if (((*(short *)(DAT_0800e438 + 0x1e) <= *(short *)(DAT_0800e438 + 0x2a)) ||
        (*(char *)(DAT_0800e440 + 0xb) != '\0')) &&
       ((*(short *)(DAT_0800e438 + 0x2c) <= *(short *)(DAT_0800e438 + 0x22) ||
        (*(char *)(DAT_0800e440 + 0xd) != '\0')))) goto LAB_0800e370;
    *(short *)(DAT_0800e438 + 0x34) = *(short *)(DAT_0800e438 + 0x34) + 1;
    if (*(ushort *)(iVar1 + 0x2e) / 100 <= (uint)*(ushort *)(iVar1 + 0x34)) {
      *(undefined2 *)(iVar1 + 0x38) = 0;
      *(undefined2 *)(iVar1 + 0x34) = 0;
      FUN_08019844(0,0x1d,extraout_r2,extraout_r3,unaff_r4);
      if (*(short *)(iVar1 + 0x2a) < *(short *)(iVar1 + 0x1e)) {
        if (*(char *)(iVar3 + 0xb) == '\0') {
          uVar4 = 0x11;
LAB_0800e3ec:
          *(undefined1 *)(iVar2 + 8) = uVar4;
        }
      }
      else if (*(char *)(iVar3 + 0xd) == '\0') {
        uVar4 = 0x21;
        goto LAB_0800e3ec;
      }
    }
  }
  if ((*(byte *)(iVar2 + 8) & 1) == 0) {
    return;
  }
  if ((*DAT_0800e444 <= *(short *)(iVar1 + 0x1e)) || (*(short *)(iVar1 + 0x22) <= *DAT_0800e448)) {
    *(undefined2 *)(iVar1 + 0x38) = 0;
    return;
  }
  *(short *)(iVar1 + 0x38) = *(short *)(iVar1 + 0x38) + 1;
  if ((uint)*(ushort *)(iVar1 + 0x38) < *(ushort *)(iVar1 + 0x30) / 100) {
    return;
  }
  *(undefined2 *)(iVar1 + 0x38) = 0;
  *(undefined2 *)(iVar1 + 0x34) = 0;
  if ((*(char *)(iVar3 + 0xc) == '\0') && (*(char *)(iVar3 + 0xe) == '\0')) {
    *(undefined1 *)(iVar2 + 8) = 0;
  }
  if ((*(char *)(iVar3 + 0xc) != '\0') && (*(char *)(iVar3 + 0xe) == '\0')) {
    if ((int)((uint)*(byte *)(iVar2 + 8) << 0x1a) < 0) {
      *(byte *)(iVar2 + 8) = *(byte *)(iVar2 + 8) & 0xef;
    }
    else {
      *(undefined1 *)(iVar2 + 8) = 0;
    }
  }
  if (*(char *)(iVar3 + 0xc) != '\0') {
    return;
  }
  if (*(char *)(iVar3 + 0xe) == '\0') {
    return;
  }
  if ((int)((uint)*(byte *)(iVar2 + 8) << 0x1b) < 0) {
    *(byte *)(iVar2 + 8) = *(byte *)(iVar2 + 8) & 0xdf;
    return;
  }
LAB_0800e430:
  *(undefined1 *)(iVar2 + 8) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800c754 at 0x0800c754
// ---------------------------------------------------------------------------

void FUN_0800c754(byte *param_1,short param_2)

{
  uint uVar1;
  uint uVar2;
  byte *pbVar3;
  byte bVar4;
  bool bVar5;
  
  uVar2 = 0xffff;
  while (bVar5 = param_2 != 0, param_2 = param_2 + -1, bVar5) {
    pbVar3 = param_1 + 1;
    uVar2 = uVar2 ^ *param_1;
    bVar4 = 0;
    do {
      uVar1 = uVar2 & 1;
      uVar2 = uVar2 >> 1;
      if (uVar1 != 0) {
        uVar2 = uVar2 ^ 0xa001;
      }
      bVar4 = bVar4 + 1;
      param_1 = pbVar3;
    } while (bVar4 < 8);
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800c78c at 0x0800c78c
// ---------------------------------------------------------------------------

void FUN_0800c78c(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = DAT_0800c810;
  if (*(char *)(DAT_0800c810 + 3) == '\0') {
    if (*DAT_0800c814 * 0x4000000 < 0) {
      *(undefined1 *)(DAT_0800c810 + 0x22) = 0;
    }
    else {
      *(undefined1 *)(DAT_0800c810 + 0x23) = 0;
      *(char *)(iVar1 + 0x22) = *(char *)(iVar1 + 0x22) + '\x01';
      if (9 < *(byte *)(iVar1 + 0x22)) {
        *(undefined1 *)(iVar1 + 0x22) = 0;
        *(undefined1 *)(iVar1 + 3) = 1;
        if (*(char *)(iVar1 + 4) != '\0') {
          *(undefined1 *)(iVar1 + 4) = 0;
        }
        if (*(char *)(iVar1 + 2) == '\0') {
          *(undefined1 *)(iVar1 + 5) = 0;
          *(undefined1 *)(iVar1 + 6) = 0;
          *(undefined1 *)(iVar1 + 7) = 0;
          *(undefined1 *)(iVar1 + 8) = 0;
          *(undefined1 *)(iVar1 + 9) = 0;
          *(undefined1 *)(iVar1 + 10) = 0;
          *(undefined1 *)(iVar1 + 0xb) = 0;
        }
        uVar2 = 0xa4;
        goto LAB_0800c7be;
      }
    }
  }
  else {
    if (-1 < *DAT_0800c814 * 0x4000000) {
      *(undefined1 *)(DAT_0800c810 + 0x23) = 0;
      return;
    }
    *(undefined1 *)(DAT_0800c810 + 0x22) = 0;
    *(char *)(iVar1 + 0x23) = *(char *)(iVar1 + 0x23) + '\x01';
    if (9 < *(byte *)(iVar1 + 0x23)) {
      *(undefined1 *)(iVar1 + 0x23) = 0;
      *(undefined1 *)(iVar1 + 3) = 0;
      uVar2 = 0xa5;
LAB_0800c7be:
      FUN_08019844(0,uVar2);
      return;
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800c818 at 0x0800c818
// ---------------------------------------------------------------------------

void FUN_0800c818(void)

{
  byte *pbVar1;
  int iVar2;
  
  pbVar1 = DAT_0800c8d0;
  if (DAT_0800c8d0[0x3b] == 0) {
    if ((DAT_0800c8d0[0x3a] != 0) && (*(char *)(DAT_0800c8d4 + 0xec) != '\0')) {
      FUN_0800f482();
    }
    pbVar1[0x3b] = 1;
    pbVar1[0x3a] = 0;
    FUN_0800f06e(pbVar1[0x4a]);
  }
  iVar2 = DAT_0800c8d8;
  if (((int)((uint)pbVar1[0x39] << 0x1d) < 0) && (*(char *)(DAT_0800c8d8 + 0xf) == '\x01')) {
    *DAT_0800c8dc = 0;
    *(undefined2 *)(iVar2 + 0x14) = 0;
    pbVar1[0x39] = pbVar1[0x39] & 0xfb;
    FUN_0800acd8();
    FUN_08019844(0xc,10);
  }
  iVar2 = DAT_0800c8e4;
  if ((*DAT_0800c8e0 == '\x01') && (pbVar1[0x4d] == 0)) {
    if (*DAT_0800c8ec < *(float *)(DAT_0800c8e8 + 0x10)) {
      *(short *)(DAT_0800c8e4 + 6) = *(short *)(DAT_0800c8e4 + 6) + 1;
      if (2 < *(ushort *)(iVar2 + 6)) {
        *(undefined2 *)(iVar2 + 6) = 0;
        FUN_0800f490();
        thunk_FUN_0800cdb4();
        pbVar1[0x4d] = 1;
        if (*DAT_0800c8f0 == '\0') {
          *pbVar1 = *pbVar1 & 0xce;
        }
      }
      goto LAB_0800c8c8;
    }
  }
  *(undefined2 *)(DAT_0800c8e4 + 6) = 0;
LAB_0800c8c8:
  FUN_0800f46c();
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800c8f4 at 0x0800c8f4
// ---------------------------------------------------------------------------

void FUN_0800c8f4(void)

{
  int iVar1;
  
  iVar1 = FUN_0800cc08();
  if (iVar1 != 0) {
    if ((~*(byte *)(DAT_0800c938 + 3) & 5) != 0) {
      FUN_0800f4bc();
      if (*(char *)(DAT_0800c93c + 0x4c) != '\0') {
        *(undefined1 *)(DAT_0800c93c + 0x4c) = 0;
        FUN_0800f4b0();
        thunk_FUN_0800ce70();
        FUN_0800db18(0x14);
        FUN_0800f49c();
      }
      return;
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800c940 at 0x0800c940
// ---------------------------------------------------------------------------

void FUN_0800c940(void)

{
  byte *pbVar1;
  byte bVar2;
  int iVar3;
  uint in_r3;
  uint local_10;
  
  local_10 = in_r3 & 0xffffff00;
  iVar3 = FUN_080122f0(0,&local_10,1);
  if ((iVar3 != 0) && ((local_10 & 0x35) != 0)) {
    bVar2 = (byte)local_10 & ~((byte)local_10 & 0x35);
    local_10 = CONCAT31(local_10._1_3_,bVar2);
    FUN_08012720(0,bVar2);
  }
  pbVar1 = DAT_0800c9d0;
  if (((((*DAT_0800c9c8 != '\0') && (*DAT_0800c9cc == '\x02')) && ((DAT_0800c9d0[0x39] & 3) == 0))
      && (((DAT_0800c9d0[0x1b] & 3) == 0 && (-1 < (int)((uint)*DAT_0800c9d0 << 0x1e))))) &&
     ((-1 < (int)((uint)DAT_0800c9d0[0x51] << 0x1d) &&
      (((DAT_0800c9d0[0x10] & 3) == 0 && (iVar3 = FUN_0800cc50(), iVar3 != 0)))))) {
    thunk_FUN_0800ceec();
    pbVar1[0x4c] = 1;
    FUN_0800f4c8();
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800c9d4 at 0x0800c9d4
// ---------------------------------------------------------------------------

void FUN_0800c9d4(void)

{
  byte *pbVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint in_r3;
  float local_18;
  uint local_14;
  
  iVar3 = DAT_0800ca8c;
  local_18 = DAT_0800ca84;
  local_14 = in_r3 & 0xffffff00;
  if ((*DAT_0800ca88 == '\0') && ((*(byte *)(DAT_0800ca8c + 0x39) & 3) == 0)) {
    if (*DAT_0800ca90 == '\x02') {
      puVar2 = (undefined1 *)(DAT_0800ca8c + 0x3d);
      local_14 = CONCAT31((int3)(in_r3 >> 8),*puVar2);
      *puVar2 = 1;
      FUN_08018574(&local_18);
      *puVar2 = (undefined1)local_14;
    }
    else {
      local_18 = *DAT_0800ca94;
    }
    iVar5 = DAT_0800ca9c;
    iVar4 = DAT_0800ca98;
    local_18 = -local_18;
    if (local_18 < *(float *)(DAT_0800ca98 + 4)) {
      *(undefined2 *)(DAT_0800ca9c + 0x36) = 0;
      return;
    }
    *(short *)(DAT_0800ca9c + 0x36) = *(short *)(DAT_0800ca9c + 0x36) + 1;
    if (*(ushort *)(iVar4 + 2) <= *(ushort *)(iVar5 + 0x36)) {
      *(undefined2 *)(iVar5 + 0x36) = 0;
      FUN_0800c8f4();
      if (-1 < (int)((uint)*(byte *)(iVar3 + 0x39) << 0x1e)) {
        FUN_08019844(10,8);
        FUN_080196d0(0x1de);
      }
      pbVar1 = (byte *)(iVar3 + 0x39);
      *pbVar1 = *pbVar1 | 2;
      *DAT_0800caa0 = 1;
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800caa4 at 0x0800caa4
// ---------------------------------------------------------------------------

void FUN_0800caa4(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  
  iVar3 = DAT_0800cb5c;
  iVar2 = DAT_0800cb58;
  iVar1 = DAT_0800cb54;
  if (((*(byte *)(DAT_0800cb54 + 0x39) & 3) != 0) && (*(char *)(DAT_0800cb58 + 0x10) != '\0')) {
    if ((*(ushort *)(DAT_0800cb58 + 0x16) < (ushort)*(byte *)(DAT_0800cb58 + 0x12)) ||
       (*(char *)(DAT_0800cb58 + 0x12) == '\0')) {
      *(int *)(DAT_0800cb5c + 0x58) = *(int *)(DAT_0800cb5c + 0x58) + 1;
      uVar4 = 0;
      uVar5 = (uint)*(byte *)(iVar2 + 0x11) * 0x3c == 0;
      uVar6 = FUN_08008548();
      uVar6 = FUN_08008364((int)uVar6,(int)((ulonglong)uVar6 >> 0x20),(int)DAT_0800cb60,
                           (int)((ulonglong)DAT_0800cb60 >> 0x20));
      uVar7 = FUN_08008548(*(undefined4 *)(iVar3 + 0x58));
      FUN_08008628((int)uVar7,(int)((ulonglong)uVar7 >> 0x20),(int)uVar6,
                   (int)((ulonglong)uVar6 >> 0x20));
      if (!(bool)uVar4 || (bool)uVar5) {
        if (*(char *)(iVar2 + 0x12) == '\0') {
          *(undefined2 *)(iVar2 + 0x16) = 0;
        }
        else {
          *(short *)(iVar2 + 0x16) = *(short *)(iVar2 + 0x16) + 1;
        }
        *(undefined4 *)(iVar3 + 0x58) = 0;
        if ((int)((uint)*(byte *)(iVar1 + 0x39) << 0x1e) < 0) {
          FUN_08019844(0xd,10);
        }
        if ((*(byte *)(iVar1 + 0x39) & 1) != 0) {
          FUN_08019844(0xe,10);
        }
        *(byte *)(iVar1 + 0x39) = *(byte *)(iVar1 + 0x39) & 0xfc;
        *DAT_0800cb68 = 0;
        FUN_0800c940();
        *(undefined1 *)(iVar3 + 6) = 1;
      }
    }
    else {
      *(undefined4 *)(DAT_0800cb5c + 0x58) = 0;
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800cb6c at 0x0800cb6c
// ---------------------------------------------------------------------------

undefined4 FUN_0800cb6c(void)

{
  return 1;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800cb70 at 0x0800cb70
// ---------------------------------------------------------------------------

void FUN_0800cb70(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar3 = DAT_0800cbf4;
  iVar2 = DAT_0800cbf0;
  iVar1 = DAT_0800cbec;
  if (*(char *)(DAT_0800cbec + 0x3a) == '\0') {
    if ((*(char *)(DAT_0800cbf0 + 7) != '\x02') || (*(int *)(DAT_0800cbf0 + 8) <= DAT_0800cbf8)) {
      *(undefined2 *)(DAT_0800cbf4 + 0x2c) = 0;
      *(undefined2 *)(iVar3 + 0x2e) = 0;
      return;
    }
    *(short *)(DAT_0800cbf4 + 0x2c) = *(short *)(DAT_0800cbf4 + 0x2c) + 1;
    uVar4 = DAT_0800cc00;
    if (*DAT_0800cbfc < *(ushort *)(iVar3 + 0x2c)) {
      *(undefined2 *)(iVar3 + 0x2c) = 0;
      *(undefined2 *)(iVar3 + 0x2e) = 0;
      *(undefined1 *)(iVar2 + 1) = 0;
      *(undefined1 *)(iVar2 + 7) = 3;
      *(undefined4 *)(iVar2 + 0xc) = uVar4;
      *(undefined4 *)(iVar2 + 8) = uVar4;
    }
    if ((*(char *)(iVar1 + 0x3b) != '\0') &&
       (*(short *)(iVar3 + 0x2e) = *(short *)(iVar3 + 0x2e) + 1, 300 < *(ushort *)(iVar3 + 0x2e))) {
      *(undefined2 *)(iVar3 + 0x2e) = 0;
      *(undefined2 *)(iVar3 + 0x2c) = 0;
      *(undefined1 *)(iVar2 + 1) = 0;
      *(undefined1 *)(iVar2 + 7) = 0;
      *(undefined4 *)(iVar2 + 0xc) = uVar4;
      *(undefined4 *)(iVar2 + 8) = uVar4;
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800cc08 at 0x0800cc08
// ---------------------------------------------------------------------------

undefined1 FUN_0800cc08(void)

{
  if ((((DAT_0800cc44[0x39] & 3) == 0) && ((*(byte *)(DAT_0800cc48 + 4) & 1) != 0)) ||
     ((((DAT_0800cc44[0x1b] & 3) != 0 ||
       ((((int)((uint)*DAT_0800cc44 << 0x1e) < 0 || ((int)((uint)DAT_0800cc44[0x51] << 0x1d) < 0))
        || ((DAT_0800cc44[0x10] & 3) != 0)))) && (*DAT_0800cc4c == '\0')))) {
    return 0;
  }
  return 1;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800cc50 at 0x0800cc50
// ---------------------------------------------------------------------------

undefined1 FUN_0800cc50(void)

{
  int iVar1;
  int iVar2;
  ushort uVar3;
  char *pcVar4;
  undefined4 *puVar5;
  
  iVar1 = DAT_0800cd2c;
  if (*DAT_0800cd14 == '\0') {
    if (*DAT_0800cd18 != '\0') {
      return 0;
    }
    if (*DAT_0800cd1c == '\x14') {
      pcVar4 = DAT_0800cd24;
    }
    else {
      if (*DAT_0800cd20 != '\0') goto LAB_0800cc82;
      pcVar4 = DAT_0800cd28;
    }
    if (*pcVar4 == '\0') {
      return 0;
    }
  }
LAB_0800cc82:
  *(undefined4 *)(DAT_0800cd2c + 0x10) = 0x1000;
  *DAT_0800cd30 = 0x10;
  iVar2 = DAT_0800cd34;
  *(undefined1 *)(DAT_0800cd34 + 6) = 0;
  uVar3 = 0;
  do {
    if (9 < uVar3) {
LAB_0800ccde:
      puVar5 = DAT_0800cd30 + 1;
      if (uVar3 < 10) {
        *(undefined4 *)(iVar1 + 0x14) = 0x1000;
        *puVar5 = 0x10;
        *(byte *)(DAT_0800cd38 + 0x39) = *(byte *)(DAT_0800cd38 + 0x39) | 1;
        FUN_08019844(0,0x31);
        FUN_080196d0(0x1e2);
        return 0;
      }
      *puVar5 = 0x10;
      return 1;
    }
    FUN_0800db18(10);
    if ((int)((uint)*(byte *)(iVar1 + 8) << 0x1e) < 0) {
      *(char *)(iVar2 + 6) = *(char *)(iVar2 + 6) + '\x01';
      if (3 < *(byte *)(iVar2 + 6)) {
        *(undefined1 *)(iVar2 + 6) = 0;
        goto LAB_0800ccde;
      }
    }
    else {
      *(undefined1 *)(iVar2 + 6) = 0;
    }
    uVar3 = uVar3 + 1;
  } while( true );
}



// ---------------------------------------------------------------------------
// Function: FUN_0800cd3c at 0x0800cd3c
// ---------------------------------------------------------------------------

longlong FUN_0800cd3c(undefined4 param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint local_18;
  uint local_14;
  uint local_10;
  
  local_18 = param_2 & 0xffffff00;
  local_10 = param_4 & 0xffffff00;
  local_14 = param_3;
  iVar1 = FUN_080122f0(0x51,&local_18,1);
  uVar2 = 0;
  if (iVar1 != 0) {
    if ((~(local_18 & 0xff) & 3) == 0) {
      local_14 = local_14 & 0xffffff00;
      while ((byte)local_14 < 10) {
        FUN_08012720(0x51,local_18 & 0xfc,1);
        FUN_0800db18(5);
        iVar1 = FUN_080122f0(0x51,&local_18,1);
        if ((iVar1 != 0) && ((local_18 & 3) == 0)) break;
        local_14 = CONCAT31(local_14._1_3_,(byte)local_14 + '\x01');
      }
      if ((byte)local_14 == '\n') {
        return (ulonglong)local_18 << 0x20;
      }
    }
    uVar2 = 1;
  }
  return CONCAT44(local_18,uVar2);
}



// ---------------------------------------------------------------------------
// Function: FUN_0800cdb4 at 0x0800cdb4
// ---------------------------------------------------------------------------

longlong FUN_0800cdb4(undefined4 param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  uint local_18;
  uint local_14;
  uint local_10;
  
  local_18 = param_2 & 0xffffff00;
  local_14 = param_3 & 0xffffff00;
  local_10 = param_4;
  iVar3 = FUN_080122f0(6,&local_18,1);
  uVar4 = 0;
  if (iVar3 != 0) {
    if ((local_18 & 1) == 0) {
      FUN_080122f0(0,&local_14,1);
      if ((local_14 & 0x4a) != 0) {
        bVar2 = (byte)local_14 & ~((byte)local_14 & 0x4a);
        local_14 = CONCAT31(local_14._1_3_,bVar2);
        FUN_08012720(0,bVar2);
      }
      local_10 = local_10 & 0xffffff00;
      while ((byte)local_10 < 10) {
        iVar3 = FUN_080122f0(0x51,&local_18,1);
        uVar1 = local_18;
        if (iVar3 != 0) {
          local_18 = local_18 & 0xffffff9c;
          FUN_08012720(0x51,uVar1 & 0x9c | 3,1);
        }
        FUN_0800db18(5);
        iVar3 = FUN_080122f0(6,&local_18,1);
        if ((iVar3 != 0) && ((local_18 & 1) != 0)) break;
        local_10 = CONCAT31(local_10._1_3_,(byte)local_10 + '\x01');
      }
      if ((byte)local_10 == '\n') {
        return (ulonglong)local_18 << 0x20;
      }
    }
    uVar4 = 1;
  }
  return CONCAT44(local_18,uVar4);
}



// ---------------------------------------------------------------------------
// Function: FUN_0800ce70 at 0x0800ce70
// ---------------------------------------------------------------------------

longlong FUN_0800ce70(undefined4 param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint local_18;
  uint local_14;
  uint local_10;
  
  local_18 = param_2 & 0xffffff00;
  local_10 = param_4 & 0xffffff00;
  local_14 = param_3;
  iVar1 = FUN_080122f0(0x51,&local_18,1);
  uVar2 = 0;
  if (iVar1 != 0) {
    if ((local_18 & 0xf) >> 2 == 3) {
      local_14 = local_14 & 0xffffff00;
      while ((byte)local_14 < 10) {
        FUN_08012720(0x51,local_18 & 0xf3,1);
        FUN_0800db18(5);
        iVar1 = FUN_080122f0(0x51,&local_18,1);
        if ((iVar1 != 0) && ((local_18 & 0xc) == 0)) break;
        local_14 = CONCAT31(local_14._1_3_,(byte)local_14 + '\x01');
      }
      if ((byte)local_14 == '\n') {
        return (ulonglong)local_18 << 0x20;
      }
    }
    uVar2 = 1;
  }
  return CONCAT44(local_18,uVar2);
}



// ---------------------------------------------------------------------------
// Function: FUN_0800ceec at 0x0800ceec
// ---------------------------------------------------------------------------

longlong FUN_0800ceec(undefined4 param_1,uint param_2,uint param_3,uint param_4)

{
  char *pcVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  uint local_18;
  uint local_14;
  uint local_10;
  
  local_18 = param_2 & 0xffffff00;
  local_14 = param_3 & 0xffffff00;
  local_10 = param_4;
  iVar3 = FUN_080122f0(6,&local_18,1);
  uVar4 = 0;
  if (iVar3 != 0) {
    if (-1 < (int)(local_18 << 0x1e)) {
      FUN_080122f0(0,&local_14,1);
      if ((local_14 & 0x35) != 0) {
        bVar2 = (byte)local_14 & ~((byte)local_14 & 0x35);
        local_14 = CONCAT31(local_14._1_3_,bVar2);
        FUN_08012720(0,bVar2);
      }
      pcVar1 = DAT_0800cfbc;
      local_10 = local_10 & 0xffffff00;
      while ((byte)local_10 < 10) {
        iVar3 = FUN_080122f0(0x51,&local_18,1);
        if (iVar3 != 0) {
          local_18 = local_18 & 0xffffff83;
          if (*pcVar1 == '\0') {
            local_18 = local_18 | 0x10;
          }
          FUN_08012720(0x51,local_18 & 0xff | 0xc,1);
        }
        FUN_0800db18(5);
        iVar3 = FUN_080122f0(6,&local_18,1);
        if ((iVar3 != 0) && ((int)(local_18 << 0x1e) < 0)) break;
        local_10 = CONCAT31(local_10._1_3_,(byte)local_10 + '\x01');
      }
      if ((byte)local_10 == '\n') {
        return (ulonglong)local_18 << 0x20;
      }
    }
    uVar4 = 1;
  }
  return CONCAT44(local_18,uVar4);
}



// ---------------------------------------------------------------------------
// Function: FUN_0800cfc0 at 0x0800cfc0
// ---------------------------------------------------------------------------

undefined4 FUN_0800cfc0(int param_1,byte param_2)

{
  uint uVar1;
  undefined8 uVar2;
  int iVar3;
  undefined4 uVar4;
  uint in_fpscr;
  float fVar5;
  float fVar6;
  undefined8 uVar7;
  byte local_78;
  float local_70 [7];
  byte local_54 [16];
  float afStack_44 [6];
  byte local_2c;
  
  if (6 < param_2) {
    param_2 = 6;
  }
  iVar3 = FUN_080122f0(0xf,local_54,param_2 * '\x02' + '\x02');
  uVar2 = DAT_0800d1f0;
  if (iVar3 == 0) {
    uVar4 = 0;
  }
  else {
    for (local_2c = 0; iVar3 = DAT_0800d1f8, (uint)local_2c < param_2 + 1; local_2c = local_2c + 1)
    {
      uVar7 = FUN_08008548(CONCAT11(local_54[(uint)local_2c * 2],local_54[(uint)local_2c * 2 + 1]));
      FUN_08008364((int)uVar7,(int)((ulonglong)uVar7 >> 0x20),(int)uVar2,
                   (int)((ulonglong)uVar2 >> 0x20));
      fVar5 = (float)FUN_08008658();
      local_70[local_2c] = fVar5;
    }
    if ((*(int *)(DAT_0800d1f8 + 4) < 0x41000000) || (DAT_0800d1fc < *(int *)(DAT_0800d1f8 + 4))) {
      FUN_080122f0(0x7e,local_54,1);
      fVar5 = (float)VectorUnsignedToFloat((uint)local_54[0],(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(iVar3 + 4) = (DAT_0800d200 + fVar5 * 25.0) / DAT_0800d204;
    }
    fVar5 = DAT_0800d208;
    for (local_2c = 0; local_2c < param_2; local_2c = local_2c + 1) {
      afStack_44[local_2c] =
           (local_70[local_2c + 1] * *(float *)(iVar3 + 4)) / (local_70[0] - local_70[local_2c + 1])
      ;
      in_fpscr = in_fpscr & 0xfffffff;
      if (0.0 <= afStack_44[local_2c]) {
        local_78 = 0xa0;
        for (; local_78 != 0; local_78 = local_78 - 1) {
          fVar6 = *(float *)(*DAT_0800d20c + (uint)local_78 * 4);
          uVar1 = in_fpscr & 0xfffffff | (uint)(afStack_44[local_2c] == fVar6) << 0x1e;
          in_fpscr = uVar1 | (uint)(fVar6 <= afStack_44[local_2c]) << 0x1d;
          if (!(bool)((byte)(in_fpscr >> 0x1d) & 1) || SUB41(uVar1 >> 0x1e,0)) {
            fVar6 = (float)VectorSignedToFloat(local_78 - 0x28,(byte)(in_fpscr >> 0x16) & 3);
            afStack_44[local_2c] = fVar6;
            break;
          }
        }
        if (local_78 == 0) {
          afStack_44[local_2c] = fVar5;
        }
        if (DAT_0800d210 < (int)afStack_44[local_2c]) {
          afStack_44[local_2c] = DAT_0800d214;
        }
      }
      else {
        afStack_44[local_2c] = fVar5;
      }
      *(short *)(param_1 + (uint)local_2c * 2) = (short)(int)afStack_44[local_2c];
    }
    uVar4 = 1;
  }
  return uVar4;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800d218 at 0x0800d218
// ---------------------------------------------------------------------------

undefined4 FUN_0800d218(int param_1,uint param_2)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  uint in_fpscr;
  byte abStack_60 [8];
  undefined1 auStack_58 [12];
  undefined1 auStack_4c [40];
  byte local_24;
  float local_20;
  int iStack_18;
  uint local_14;
  
  local_14 = param_2;
  uVar3 = local_14;
  iStack_18 = param_1;
  local_20 = (float)(DAT_0800d3b4 & 0xffffff00);
  local_14._0_1_ = (byte)param_2;
  local_14 = uVar3;
  if (*DAT_0800d3b8 != 0x464) {
    if (*DAT_0800d3b8 != 0x45d) {
      if (*DAT_0800d3b8 == 0x45a) {
        iVar4 = FUN_080122f0(0x1d,abStack_60,((param_2 & 0xff) * 2 + 0x7c & 0x7f) << 1);
        if (iVar4 == 0) {
          return 0;
        }
        for (local_24 = 0; (int)(uint)local_24 < (int)((local_14 & 0xff) - 4);
            local_24 = local_24 + 1) {
          auStack_58[(uint)local_24 * 2] = auStack_58[(uint)local_24 * 4 + 2];
          auStack_58[(uint)local_24 * 2 + 1] = auStack_58[(uint)local_24 * 4 + 3];
        }
      }
      goto LAB_0800d338;
    }
    if (10 < (byte)local_14) {
      iVar4 = FUN_080122f0(0x1d,abStack_60,((param_2 & 0xff) * 2 + 0x76 & 0x7f) << 1);
      if (iVar4 == 0) {
        return 0;
      }
      for (local_24 = 0; (int)(uint)local_24 < (int)((local_14 & 0xff) - 10);
          local_24 = local_24 + 1) {
        auStack_4c[(uint)local_24 * 2] = auStack_4c[(uint)local_24 * 4 + 2];
        auStack_4c[(uint)local_24 * 2 + 1] = auStack_4c[(uint)local_24 * 4 + 3];
      }
      goto LAB_0800d338;
    }
  }
  iVar4 = FUN_080122f0(0x1d,abStack_60,(param_2 & 0x7f) << 1);
  if (iVar4 == 0) {
    return 0;
  }
LAB_0800d338:
  fVar2 = DAT_0800d3c0;
  fVar1 = DAT_0800d3bc;
  for (local_24 = 0; local_24 < (byte)local_14; local_24 = local_24 + 1) {
    local_20 = (float)CONCAT22(local_20._2_2_,(ushort)abStack_60[(uint)local_24 * 2]);
    local_20 = (float)(uint)CONCAT11(abStack_60[(uint)local_24 * 2],
                                     abStack_60[(uint)local_24 * 2 + 1]);
    local_20 = (float)VectorUnsignedToFloat(local_20,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(param_1 + (uint)local_24 * 4) = fVar2 + local_20 * fVar1;
  }
  return 1;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800d3c4 at 0x0800d3c4
// ---------------------------------------------------------------------------

bool FUN_0800d3c4(float *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  uint in_fpscr;
  float fVar2;
  float *local_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 local_c;
  
  local_c = DAT_0800d41c;
  local_18 = param_1;
  uStack_14 = param_2;
  uStack_10 = param_3;
  iVar1 = FUN_080122f0(0xb,&local_18,2);
  if (iVar1 != 0) {
    fVar2 = (float)VectorUnsignedToFloat
                             (((uint)local_18 >> 8 & 0xff) + ((uint)local_18 & 0xff) * 0x100,
                              (byte)(in_fpscr >> 0x16) & 3);
    *param_1 = DAT_0800d424 + fVar2 * DAT_0800d420;
  }
  return iVar1 != 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800d428 at 0x0800d428
// ---------------------------------------------------------------------------

bool FUN_0800d428(float *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  uint in_fpscr;
  float fVar2;
  float *local_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 local_c;
  
  local_c = DAT_0800d480;
  local_18 = param_1;
  uStack_14 = param_2;
  uStack_10 = param_3;
  iVar1 = FUN_080122f0(7,&local_18,2);
  if (iVar1 != 0) {
    fVar2 = (float)VectorUnsignedToFloat
                             (((uint)local_18 >> 8 & 0xff) + ((uint)local_18 & 0xff) * 0x100,
                              (byte)(in_fpscr >> 0x16) & 3);
    *param_1 = DAT_0800d488 + fVar2 * DAT_0800d484;
  }
  return iVar1 != 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800d48c at 0x0800d48c
// ---------------------------------------------------------------------------

undefined4 FUN_0800d48c(float *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  short *psVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  uint in_fpscr;
  float fVar5;
  float fVar6;
  undefined4 local_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  local_1c = param_2;
  uStack_18 = param_3;
  uStack_14 = param_4;
  iVar3 = FUN_080122f0(2,&local_1c,2,param_4,DAT_0800d520);
  psVar1 = DAT_0800d528;
  uVar4 = 0;
  if (iVar3 != 0) {
    fVar5 = (float)VectorSignedToFloat((int)CONCAT11((undefined1)local_1c,local_1c._1_1_),
                                       (byte)(in_fpscr >> 0x16) & 3);
    if (*(char *)(DAT_0800d524 + 0x3d) == '\x01') {
      sVar2 = FUN_0800d5cc();
      *psVar1 = sVar2;
    }
    uVar4 = 1;
    fVar6 = (float)VectorSignedToFloat((int)*psVar1,(byte)(in_fpscr >> 0x16) & 3);
    *param_1 = -(fVar5 - fVar6) * DAT_0800d52c;
  }
  return uVar4;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800d530 at 0x0800d530
// ---------------------------------------------------------------------------

bool FUN_0800d530(float *param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint in_fpscr;
  float fVar2;
  float fVar3;
  uint local_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  local_14 = param_2;
  uStack_10 = param_3;
  uStack_c = param_4;
  iVar1 = FUN_080122f0(4,&local_14,3,param_4,DAT_0800d5c0);
  if (iVar1 != 0) {
    fVar2 = (float)VectorSignedToFloat((int)(((local_14 >> 0x10 & 0xf0) +
                                             ((local_14 >> 8 & 0xff) + (local_14 & 0xff) * 0x100) *
                                             0x100) * 0x100) >> 0xc,(byte)(in_fpscr >> 0x16) & 3);
    fVar3 = (float)VectorSignedToFloat((int)*DAT_0800d5c4 << 4,(byte)(in_fpscr >> 0x16) & 3);
    *param_1 = -(fVar2 - fVar3) * DAT_0800d5c8;
  }
  return iVar1 != 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800d5cc at 0x0800d5cc
// ---------------------------------------------------------------------------

undefined4 FUN_0800d5cc(undefined4 param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  undefined4 local_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  uint local_c;
  
  local_c = param_4 & 0xffff0000;
  local_18 = param_1;
  uStack_14 = param_2;
  uStack_10 = param_3;
  FUN_080122f0(0x4f,&local_18,2);
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800d5fc at 0x0800d5fc
// ---------------------------------------------------------------------------

undefined4 FUN_0800d5fc(void)

{
  char *pcVar1;
  char *pcVar2;
  float *pfVar3;
  float *pfVar4;
  float *pfVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  bool bVar10;
  undefined1 local_50;
  undefined1 local_4f;
  undefined1 local_4e;
  undefined1 local_4d;
  undefined1 local_4c [3];
  undefined1 local_49;
  undefined1 local_48;
  undefined1 local_47;
  undefined1 local_46;
  byte local_44;
  byte local_43;
  char local_42;
  char local_41;
  byte local_40;
  char local_3f;
  undefined1 local_3d;
  undefined1 local_3c;
  undefined1 local_3b;
  undefined1 local_3a;
  undefined1 local_39;
  undefined1 local_38;
  undefined1 local_37;
  undefined1 local_36;
  undefined1 local_35;
  undefined1 local_34;
  undefined1 local_32;
  byte local_31;
  undefined1 local_30;
  byte local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined1 local_2a;
  undefined1 local_29;
  byte local_28 [4];
  char local_24 [4];
  uint local_20;
  byte local_1c [8];
  
  local_20 = 0;
  local_24[0] = '\0';
  iVar6 = FUN_080122f0(0x5a,local_24,1);
  pcVar1 = DAT_0800d920;
  bVar10 = iVar6 == 0;
LAB_0800d618:
  do {
    do {
      if (bVar10) goto LAB_0800d86c;
      if ((local_24[0] != -2) && (*pcVar1 != '\0')) {
        iVar6 = FUN_08012720(1,0xd,0);
        bVar10 = true;
        if (iVar6 == 0) goto LAB_0800d618;
      }
      FUN_0800db18(0xfa);
      iVar6 = FUN_080122f0(0x52,&local_50,0x28);
      bVar10 = true;
    } while (iVar6 == 0);
    local_50 = 0x9e;
    local_4f = 0xff;
    local_4e = 0xff;
    iVar6 = FUN_08012760(0x52,&local_50,3);
    pfVar5 = DAT_0800d950;
    pfVar4 = DAT_0800d944;
    pfVar3 = DAT_0800d940;
    pcVar2 = DAT_0800d924;
    bVar10 = true;
  } while (iVar6 == 0);
  if (*DAT_0800d924 == '\0') {
    local_4d = 0xac;
  }
  else {
    local_4d = 0x2c;
  }
  local_4c[0] = 0xff;
  local_49 = 0xff;
  local_48 = 0xff;
  local_47 = 0xff;
  local_46 = 0xff;
  local_44 = (*(char *)(DAT_0800d928 + 8) + '\x01') * '\x04' | 0x40;
  local_43 = ((*(byte *)(DAT_0800d928 + 0x1f) >> 4) + 1) * '\x04' | 0x40;
  local_42 = (*(char *)(DAT_0800d928 + 9) + '\x01') * '\x04';
  local_41 = ((*(byte *)(DAT_0800d928 + 0x1f) & 0xf) + 1) * '\x04';
  local_40 = (*(char *)(DAT_0800d928 + 0x17) + '\x01') * '\x04' | 0x40;
  local_3f = (*(char *)(DAT_0800d928 + 0x18) + '\x01') * '\x04';
  local_3d = 0;
  local_3c = 2;
  local_3b = 0;
  local_3a = 0;
  local_39 = 0;
  if (*DAT_0800d92c == 0x464) {
LAB_0800d720:
    uVar7 = DAT_0800d930 >> (0x18 - *DAT_0800d934 & 0xff);
  }
  else {
    if (*DAT_0800d92c == 0x45d) {
      if (*DAT_0800d934 < 0xb) goto LAB_0800d720;
      iVar6 = 0x11 - (uint)*DAT_0800d934;
      uVar7 = DAT_0800d938 + 0x15;
    }
    else {
      iVar6 = 0xe - (uint)*DAT_0800d934;
      uVar7 = DAT_0800d938;
    }
    uVar7 = DAT_0800d930 >> (iVar6 * 2 & 0xffU) & uVar7;
  }
  uVar7 = (~uVar7 & 0xfffff) << 4;
  if (*DAT_0800d924 == '\0') {
    uVar7 = uVar7 | 0xe;
  }
  else {
    uVar7 = uVar7 | 2;
  }
  local_38 = (undefined1)(uVar7 >> 0x10);
  local_37 = (undefined1)(uVar7 >> 8);
  local_36 = (undefined1)uVar7;
  local_35 = 0x28;
  local_34 = 0xcd;
  if (*DAT_0800d93c == '\x01') {
    *DAT_0800d940 = *DAT_0800d948 + DAT_0800d94c;
    *pfVar4 = *pfVar5 - DAT_0800d954;
  }
  uVar7 = VectorFloatToUnsigned(*pfVar3 * DAT_0800d958 - DAT_0800d95c,3);
  local_32 = (undefined1)(uVar7 >> 4);
  local_31 = (byte)(uVar7 << 4) | 0xb;
  local_20 = VectorFloatToUnsigned(*pfVar4 * DAT_0800d958,3);
  local_30 = (undefined1)(local_20 >> 4);
  local_2f = (byte)(local_20 << 4) | 0xb;
  local_2d = 0x49;
  local_2e = 0x49;
  if (*pcVar2 == '\0') {
    local_2d = 0x7f;
  }
  local_2c = 0;
  local_2b = 0xc0;
  local_2a = 0;
  local_29 = 0xff;
  iVar6 = FUN_08012760(0x56,local_4c,0x24);
  if (iVar6 == 0) {
LAB_0800d86c:
    *pcVar1 = '\x01';
    uVar8 = 0;
  }
  else {
    if ((local_24[0] != -2) && (*pcVar1 != '\0')) {
      if (*pcVar2 == '\0') {
        uVar9 = 0xac;
        uVar8 = 0xad;
      }
      else {
        uVar9 = 0x2c;
        uVar8 = 0x2d;
      }
      FUN_080127a0(0x55,uVar8,uVar9);
      FUN_0800db18(0xf);
    }
    if (*pcVar1 == '\x01') {
      FUN_08019844(0,0x83);
    }
    *pcVar1 = '\0';
    local_1c[0] = 0;
    iVar6 = FUN_080122f0(0x8e,local_1c,1);
    if (iVar6 != 0) {
      FUN_08012720(0x8e,local_1c[0] | 0x80,0);
    }
    local_28[0] = 0;
    iVar6 = FUN_080122f0(0,local_28,1);
    if ((iVar6 != 0) && ((local_28[0] & 0x35) != 0)) {
      local_28[0] = local_28[0] & ~(local_28[0] & 0x35);
      FUN_08012720(0,local_28[0]);
    }
    iVar6 = FUN_080122f0(0,local_28,1);
    if ((iVar6 != 0) && ((local_28[0] & 0x4a) != 0)) {
      local_28[0] = local_28[0] & ~(local_28[0] & 0x4a);
      FUN_08012720(0,local_28[0]);
    }
    if ((local_24[0] != -2) && (*pcVar1 != '\0')) {
      FUN_08016ee8(0);
    }
    uVar8 = 1;
  }
  return uVar8;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800d960 at 0x0800d960
// ---------------------------------------------------------------------------

void FUN_0800d960(void)

{
  int iVar1;
  undefined4 in_r3;
  undefined4 local_18;
  
  local_18 = in_r3;
  FUN_08020684(DAT_0800d9b8);
  local_18 = CONCAT22(local_18._2_2_,0xc);
  local_18 = CONCAT13(4,(undefined3)local_18);
  FUN_0801031c(DAT_0800d9bc,&local_18);
  FUN_08020684(DAT_0800d9c0);
  iVar1 = DAT_0800d9c4;
  local_18 = 0x10020040;
  FUN_0801031c(DAT_0800d9c4,&local_18);
  *(undefined4 *)(DAT_0800d9c4 + 0x10) = 0x40;
  local_18 = CONCAT22(local_18._2_2_,0x80);
  local_18 = CONCAT13(4,(undefined3)local_18);
  FUN_0801031c(iVar1,&local_18);
  return;
}



// ---------------------------------------------------------------------------
// Function: DebugMon_Handler at 0x0800d9c8
// ---------------------------------------------------------------------------

void DebugMon_Handler(void)

{
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800d9cc at 0x0800d9cc
// ---------------------------------------------------------------------------

longlong FUN_0800d9cc(float param_1)

{
  int iVar1;
  short sVar2;
  
  iVar1 = DAT_0800dae0;
  if (*DAT_0800dad8 == '\0') {
    sVar2 = 0;
    if (param_1 <= *DAT_0800dadc) {
      *(undefined2 *)(DAT_0800dae0 + 0x1a) = 0;
      *(undefined2 *)(iVar1 + 0x18) = 0;
      *(undefined2 *)(iVar1 + 0x16) = 0;
      *(undefined2 *)(iVar1 + 0x14) = 0;
      *(undefined2 *)(iVar1 + 0x12) = 0;
      *(undefined2 *)(iVar1 + 0x1c) = 0;
      *(undefined2 *)(iVar1 + 0x1e) = 0;
      *(undefined1 *)(iVar1 + 9) = 0;
      if (*(char *)(DAT_0800daf0 + 0x4c) == '\0') {
LAB_0800dab8:
        return (ulonglong)(uint)param_1 << 0x20;
      }
    }
    else if (*(char *)(DAT_0800dae0 + 9) == '\0') {
      if ((((*(ushort *)(DAT_0800dae0 + 0x1e) < 0x33) && (*(ushort *)(DAT_0800dae0 + 0x1c) < 0x65))
          && (*(ushort *)(DAT_0800dae0 + 0x1a) < 0x96)) &&
         (((*(ushort *)(DAT_0800dae0 + 0x18) < 200 && (*(ushort *)(DAT_0800dae0 + 0x16) < 300)) &&
          ((*(ushort *)(DAT_0800dae0 + 0x14) < 400 && (*(ushort *)(DAT_0800dae0 + 0x12) < 500))))))
      {
        if (DAT_0800dae4 < (int)param_1) {
          *(short *)(DAT_0800dae0 + 0x1e) = *(short *)(DAT_0800dae0 + 0x1e) + 1;
        }
        else {
          *(undefined2 *)(DAT_0800dae0 + 0x1e) = 0;
        }
        if (DAT_0800dae8 < (int)param_1) {
          *(short *)(iVar1 + 0x1c) = *(short *)(iVar1 + 0x1c) + 1;
        }
        else {
          *(undefined2 *)(iVar1 + 0x1c) = 0;
        }
        if ((int)param_1 < 0x40000001) {
          *(undefined2 *)(iVar1 + 0x1a) = 0;
        }
        else {
          *(short *)(iVar1 + 0x1a) = *(short *)(iVar1 + 0x1a) + 1;
        }
        if ((int)param_1 < 0x3fc00001) {
          *(undefined2 *)(iVar1 + 0x18) = 0;
        }
        else {
          *(short *)(iVar1 + 0x18) = *(short *)(iVar1 + 0x18) + 1;
        }
        if ((int)param_1 < 0x3f800001) {
          *(undefined2 *)(iVar1 + 0x16) = 0;
        }
        else {
          *(short *)(iVar1 + 0x16) = *(short *)(iVar1 + 0x16) + 1;
        }
        if ((int)param_1 < 0x3f000001) {
          *(undefined2 *)(iVar1 + 0x14) = 0;
        }
        else {
          *(short *)(iVar1 + 0x14) = *(short *)(iVar1 + 0x14) + 1;
        }
        if (DAT_0800daec < (int)param_1) {
          sVar2 = *(short *)(iVar1 + 0x12) + 1;
        }
        *(short *)(iVar1 + 0x12) = sVar2;
        goto LAB_0800dab8;
      }
      *(undefined1 *)(DAT_0800dae0 + 9) = 1;
    }
  }
  return CONCAT44(param_1,1);
}



// ---------------------------------------------------------------------------
// Function: FUN_0800daf4 at 0x0800daf4
// ---------------------------------------------------------------------------

void FUN_0800daf4(undefined4 param_1)

{
  undefined1 *puVar1;
  
  puVar1 = DAT_0800db14;
  *DAT_0800db14 = (char)((uint)param_1 >> 0x18);
  puVar1[1] = (byte)((uint)param_1 >> 0x10) & 0x1f;
  puVar1[2] = (char)((uint)param_1 >> 8);
  puVar1[3] = (char)param_1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800db18 at 0x0800db18
// ---------------------------------------------------------------------------

undefined8 FUN_0800db18(short param_1)

{
  undefined4 *puVar1;
  bool bVar2;
  short local_1c;
  undefined2 uStack_1a;
  short local_18;
  undefined2 uStack_16;
  ushort local_14;
  
  puVar1 = DAT_0800db94;
  local_1c = 0;
  local_18 = 0;
  local_14 = (ushort)(*DAT_0800db90 >> 3);
  while (bVar2 = local_14 != 0, local_14 = local_14 - 1, bVar2) {
    local_18 = 0;
    while (local_18 < param_1) {
      local_18 = local_18 + 1;
      local_1c = 0;
      while (local_1c < 0x1b6) {
        local_1c = local_1c + 1;
        *puVar1 = 0xaaaa;
      }
    }
  }
  return CONCAT26(uStack_16,CONCAT24(local_18,CONCAT22(uStack_1a,local_1c)));
}



// ---------------------------------------------------------------------------
// Function: FUN_0800db98 at 0x0800db98
// ---------------------------------------------------------------------------

void FUN_0800db98(void)

{
  short *psVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  byte bVar5;
  
  psVar1 = DAT_0800deb4;
  if ((0x78 < *DAT_0800deb4) || (*DAT_0800deb4 < 0x14)) {
    *DAT_0800deb4 = 0x50;
  }
  if ((*psVar1 <= psVar1[1]) || ((int)psVar1[1] <= *psVar1 + -0x14)) {
    psVar1[1] = *psVar1 + -10;
  }
  if ((psVar1[2] < -0x28) || (0x28 < psVar1[2])) {
    psVar1[2] = -0x1e;
  }
  if ((psVar1[3] <= psVar1[2]) || (psVar1[2] + 0x14 <= (int)psVar1[3])) {
    psVar1[3] = psVar1[2] + 10;
  }
  iVar4 = DAT_0800dec4;
  iVar3 = DAT_0800dec0;
  pbVar2 = DAT_0800deb8;
  if (((DAT_0800deb8[0x3a] != 0) && (*DAT_0800debc == '\0')) ||
     ((-1 < (int)((uint)*DAT_0800deb8 << 0x1e) &&
      ((DAT_0800deb8[0x3b] == 0 && (*DAT_0800debc == '\x01')))))) {
    if (DAT_0800deb8[1] == 0) {
      if (((*(char *)(DAT_0800dec0 + 4) == '\0') && (*psVar1 <= psVar1[0xf])) ||
         ((*(char *)(DAT_0800dec0 + 6) == '\0' && (psVar1[0x11] <= psVar1[2])))) {
        DAT_0800deb8[1] = 1;
        psVar1[10] = 0;
        pbVar2[5] = 1;
      }
      goto LAB_0800dd58;
    }
    if (DAT_0800deb8[1] == 0) goto LAB_0800dd58;
    psVar1[10] = psVar1[10] + 1;
    if ((ushort)psVar1[8] / 100 <= (uint)(ushort)psVar1[10]) {
      pbVar2[1] = 0;
      pbVar2[5] = 0;
      if (((*(char *)(iVar3 + 4) == '\0') && (*psVar1 <= psVar1[0xf])) ||
         ((*(char *)(iVar3 + 6) == '\0' && (psVar1[0x11] <= psVar1[2])))) {
        if (*pbVar2 == 0) {
          FUN_08019844(0xf,9);
        }
        if (psVar1[0xf] < *psVar1) {
          if ((*pbVar2 & 0x21) == 0) {
            FUN_080196d0(0x1c6);
          }
          *pbVar2 = *pbVar2 | 0x21;
          bVar5 = *(byte *)(iVar4 + 0xf) | 0x21;
        }
        else {
          if ((*pbVar2 & 0x11) == 0) {
            FUN_080196d0(0x1c4);
          }
          *pbVar2 = *pbVar2 | 0x11;
          bVar5 = *(byte *)(iVar4 + 0xf) | 0x11;
        }
        *(byte *)(iVar4 + 0xf) = bVar5;
        if (((*pbVar2 & 0x11) == 0) && ((*pbVar2 & 0x21) == 0)) {
          return;
        }
        FUN_0800ac9c();
        return;
      }
      goto LAB_0800dd58;
    }
    if ((((*psVar1 <= psVar1[0xf]) || (psVar1[0x11] <= psVar1[2])) &&
        ((*(char *)(iVar3 + 4) == '\0' || (psVar1[0xf] <= *psVar1)))) &&
       ((*(char *)(iVar3 + 6) == '\0' || (psVar1[2] <= psVar1[0x11])))) goto LAB_0800dd58;
  }
  pbVar2[1] = 0;
  pbVar2[5] = 0;
  psVar1[10] = 0;
LAB_0800dd58:
  if ((*pbVar2 & 1) != 0) {
    if (pbVar2[2] == 0) {
      if ((((*(char *)(iVar3 + 5) == '\0') && ((int)((uint)*(byte *)(iVar4 + 0xf) << 0x1b) < 0)) &&
          (psVar1[0xf] <= psVar1[1])) ||
         (((*(char *)(iVar3 + 7) == '\0' && ((int)((uint)*(byte *)(iVar4 + 0xf) << 0x1a) < 0)) &&
          (psVar1[3] <= psVar1[0x11])))) {
        pbVar2[2] = 1;
        psVar1[0xc] = 0;
        pbVar2[6] = 1;
      }
    }
    else if (pbVar2[2] != 0) {
      psVar1[0xc] = psVar1[0xc] + 1;
      if ((uint)(ushort)psVar1[0xc] < (ushort)psVar1[9] / 100) {
        if ((((psVar1[1] < psVar1[0xf]) || (psVar1[0x11] < psVar1[3])) ||
            ((*(char *)(iVar3 + 5) != '\0' &&
             (((int)((uint)*(byte *)(iVar4 + 0xf) << 0x1b) < 0 && (psVar1[0xf] < psVar1[1])))))) ||
           ((*(char *)(iVar3 + 7) != '\0' &&
            (((int)((uint)*(byte *)(iVar4 + 0xf) << 0x1a) < 0 && (psVar1[3] < psVar1[0x11])))))) {
          pbVar2[2] = 0;
          pbVar2[6] = 0;
          psVar1[0xc] = 0;
        }
      }
      else {
        pbVar2[2] = 0;
        pbVar2[6] = 0;
        if ((((*(char *)(iVar3 + 5) == '\0') && ((int)((uint)*(byte *)(iVar4 + 0xf) << 0x1b) < 0))
            && (psVar1[0xf] <= psVar1[1])) ||
           (((*(char *)(iVar3 + 7) == '\0' && ((int)((uint)*(byte *)(iVar4 + 0xf) << 0x1a) < 0)) &&
            (psVar1[3] <= psVar1[0x11])))) {
          if (((*pbVar2 & 0x11) != 0) || ((*pbVar2 & 0x21) != 0)) {
            if ((~*(byte *)(iVar4 + 0xf) & 0xc2) == 0) {
              bVar5 = *pbVar2 & 0xfe;
            }
            else if ((~*(byte *)(iVar4 + 0xf) & 0x42) == 0) {
              bVar5 = *pbVar2 & 0xde;
            }
            else if ((~*(byte *)(iVar4 + 0xf) & 0x82) == 0) {
              bVar5 = *pbVar2 & 0xee;
            }
            else {
              bVar5 = *pbVar2 & 0xce;
            }
            *pbVar2 = bVar5;
            *(byte *)(iVar4 + 0xf) = *(byte *)(iVar4 + 0xf) & 0xce;
            FUN_0800acd8();
            if ((*DAT_0800dec8 == '\0') && (*DAT_0800decc == '\0')) {
              FUN_08019844(0x11,0xb);
            }
            return;
          }
          *pbVar2 = *pbVar2 & 0xce;
        }
      }
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800ded0 at 0x0800ded0
// ---------------------------------------------------------------------------

void FUN_0800ded0(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 uVar4;
  
  iVar3 = DAT_0800dfe4;
  iVar2 = DAT_0800dfe0;
  iVar1 = DAT_0800dfdc;
  if (*(char *)(DAT_0800dfdc + 0x25) == '\0') goto LAB_0800dfd4;
  if (*(char *)(DAT_0800dfe0 + 0x3a) == '\0') {
LAB_0800df14:
    *(undefined2 *)(DAT_0800dfdc + 0x32) = 0;
  }
  else if ((*(byte *)(DAT_0800dfe0 + 7) & 1) == 0) {
    if (((*(short *)(DAT_0800dfdc + 0x1e) <= *(short *)(DAT_0800dfdc + 0x26)) ||
        (*(char *)(DAT_0800dfe4 + 7) != '\0')) &&
       ((*(short *)(DAT_0800dfdc + 0x28) <= *(short *)(DAT_0800dfdc + 0x22) ||
        (*(char *)(DAT_0800dfe4 + 9) != '\0')))) goto LAB_0800df14;
    *(short *)(DAT_0800dfdc + 0x32) = *(short *)(DAT_0800dfdc + 0x32) + 1;
    if (*(ushort *)(iVar1 + 0x2e) / 100 <= (uint)*(ushort *)(iVar1 + 0x32)) {
      *(undefined2 *)(iVar1 + 0x36) = 0;
      *(undefined2 *)(iVar1 + 0x32) = 0;
      FUN_08019844(0,0x1c);
      if (*(short *)(iVar1 + 0x26) < *(short *)(iVar1 + 0x1e)) {
        if (*(char *)(iVar3 + 7) == '\0') {
          uVar4 = 0x11;
LAB_0800df90:
          *(undefined1 *)(iVar2 + 7) = uVar4;
        }
      }
      else if (*(char *)(iVar3 + 9) == '\0') {
        uVar4 = 0x21;
        goto LAB_0800df90;
      }
    }
  }
  if ((*(byte *)(iVar2 + 7) & 1) == 0) {
    return;
  }
  if ((*DAT_0800dfe8 <= *(short *)(iVar1 + 0x1e)) || (*(short *)(iVar1 + 0x22) <= *DAT_0800dfec)) {
    *(undefined2 *)(iVar1 + 0x36) = 0;
    return;
  }
  *(short *)(iVar1 + 0x36) = *(short *)(iVar1 + 0x36) + 1;
  if ((uint)*(ushort *)(iVar1 + 0x36) < *(ushort *)(iVar1 + 0x30) / 100) {
    return;
  }
  *(undefined2 *)(iVar1 + 0x36) = 0;
  *(undefined2 *)(iVar1 + 0x32) = 0;
  if ((*(char *)(iVar3 + 8) == '\0') && (*(char *)(iVar3 + 10) == '\0')) {
    *(undefined1 *)(iVar2 + 7) = 0;
  }
  if ((*(char *)(iVar3 + 8) != '\0') && (*(char *)(iVar3 + 10) == '\0')) {
    if ((int)((uint)*(byte *)(iVar2 + 7) << 0x1a) < 0) {
      *(byte *)(iVar2 + 7) = *(byte *)(iVar2 + 7) & 0xef;
    }
    else {
      *(undefined1 *)(iVar2 + 7) = 0;
    }
  }
  if (*(char *)(iVar3 + 8) != '\0') {
    return;
  }
  if (*(char *)(iVar3 + 10) == '\0') {
    return;
  }
  if ((int)((uint)*(byte *)(iVar2 + 7) << 0x1b) < 0) {
    *(byte *)(iVar2 + 7) = *(byte *)(iVar2 + 7) & 0xdf;
    return;
  }
LAB_0800dfd4:
  *(undefined1 *)(iVar2 + 7) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800e44c at 0x0800e44c
// ---------------------------------------------------------------------------

void FUN_0800e44c(void)

{
  float fVar1;
  int iVar2;
  int iVar3;
  float local_28;
  float local_24;
  byte local_20;
  float local_1c;
  
  iVar2 = DAT_0800e560;
  fVar1 = DAT_0800e55c;
  local_28 = DAT_0800e55c;
  if (*(char *)(DAT_0800e560 + 0x3e) != '\0') {
    return;
  }
  FUN_08018574(&local_28);
  iVar3 = DAT_0800e56c;
  local_1c = *DAT_0800e564;
  local_20 = 0;
  local_24 = *DAT_0800e568;
  if (0.0 <= local_28) {
    if (local_28 <= 0.0) goto LAB_0800e4f8;
    *(float *)(DAT_0800e56c + 0x14) = local_28;
    *(float *)(iVar3 + 0x10) = fVar1;
    if (*(char *)(iVar2 + 0x3d) != '\x01') {
      return;
    }
    while ((local_20 < 10 && (local_24 <= local_28))) {
      FUN_0800db18(4);
      FUN_08018574(&local_28);
      local_20 = local_20 + 1;
    }
  }
  else {
    *(float *)(DAT_0800e56c + 0x10) = -local_28;
    *(float *)(iVar3 + 0x14) = fVar1;
    if (*(char *)(iVar2 + 0x3d) != '\x01') {
      return;
    }
    while ((local_20 < 10 && (local_1c <= -local_28))) {
      FUN_0800db18(4);
      FUN_08018574(&local_28);
      local_20 = local_20 + 1;
    }
  }
  if (local_20 == 10) {
    return;
  }
LAB_0800e4f8:
  *(float *)(iVar3 + 0x14) = fVar1;
  *(float *)(iVar3 + 0x10) = fVar1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800e570 at 0x0800e570
// ---------------------------------------------------------------------------

void FUN_0800e570(undefined1 *param_1,undefined1 *param_2)

{
  FUN_0800e44c();
  if (*DAT_0800e5e8 < *(float *)(DAT_0800e5ec + 0x14)) {
    *param_1 = 0;
    *param_2 = 1;
    return;
  }
  if (*DAT_0800e5e4 < *(float *)(DAT_0800e5ec + 0x10)) {
    *param_1 = 1;
    *param_2 = 0;
    return;
  }
  *param_2 = 0;
  *param_1 = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800e5f0 at 0x0800e5f0
// ---------------------------------------------------------------------------

void FUN_0800e5f0(void)

{
  int iVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  byte bVar5;
  int iVar6;
  undefined4 unaff_r4;
  
  FUN_0800db98();
  iVar1 = DAT_0800e310;
  if ((0x78 < *(short *)(DAT_0800e310 + 8)) || (*(short *)(DAT_0800e310 + 8) < 0x14)) {
    *(undefined2 *)(DAT_0800e310 + 8) = 0x50;
  }
  if ((*(short *)(iVar1 + 8) <= *(short *)(iVar1 + 10)) ||
     ((int)*(short *)(iVar1 + 10) <= *(short *)(iVar1 + 8) + -0x14)) {
    *(short *)(iVar1 + 10) = *(short *)(iVar1 + 8) + -10;
  }
  if ((*(short *)(iVar1 + 0xc) < -0x28) || (0x28 < *(short *)(iVar1 + 0xc))) {
    *(undefined2 *)(iVar1 + 0xc) = 0xffe2;
  }
  if ((*(short *)(iVar1 + 0xe) <= *(short *)(iVar1 + 0xc)) ||
     (*(short *)(iVar1 + 0xc) + 0x14 <= (int)*(short *)(iVar1 + 0xe))) {
    *(short *)(iVar1 + 0xe) = *(short *)(iVar1 + 0xc) + 10;
  }
  iVar4 = DAT_0800e320;
  iVar3 = DAT_0800e31c;
  pbVar2 = DAT_0800e314;
  if (((DAT_0800e314[0x3b] != 0) && (*DAT_0800e318 == '\0')) ||
     ((-1 < (int)((uint)*DAT_0800e314 << 0x1e) &&
      ((DAT_0800e314[0x3a] == 0 && (*DAT_0800e318 == '\x01')))))) {
    if (DAT_0800e314[3] == 0) {
      if (((*(char *)(DAT_0800e31c + 8) == '\0') &&
          (*(short *)(iVar1 + 8) <= *(short *)(iVar1 + 0x1e))) ||
         ((*(char *)(DAT_0800e31c + 10) == '\0' &&
          (*(short *)(iVar1 + 0x22) <= *(short *)(iVar1 + 0xc))))) {
        DAT_0800e314[3] = 1;
        *(undefined2 *)(iVar1 + 0x16) = 0;
        pbVar2[5] = 1;
      }
      goto LAB_0800e1b0;
    }
    if (DAT_0800e314[3] == 0) goto LAB_0800e1b0;
    *(short *)(iVar1 + 0x16) = *(short *)(iVar1 + 0x16) + 1;
    if (*(ushort *)(iVar1 + 0x10) / 100 <= (uint)*(ushort *)(iVar1 + 0x16)) {
      pbVar2[3] = 0;
      pbVar2[5] = 0;
      if (((*(char *)(iVar3 + 8) == '\0') &&
          (iVar6 = (int)*(short *)(iVar1 + 0x1e), *(short *)(iVar1 + 8) <= iVar6)) ||
         ((*(char *)(iVar3 + 10) == '\0' &&
          (iVar6 = (int)*(short *)(iVar1 + 0x22), iVar6 <= *(short *)(iVar1 + 0xc))))) {
        if (*pbVar2 == 0) {
          FUN_08019844(0x10,8,100,iVar6,unaff_r4);
        }
        if (*(short *)(iVar1 + 0x1e) < *(short *)(iVar1 + 8)) {
          if ((*pbVar2 & 0x22) == 0) {
            FUN_080196d0(0x1ca);
          }
          *pbVar2 = *pbVar2 | 0x22;
          bVar5 = *(byte *)(iVar4 + 0xf) | 0x82;
        }
        else {
          if ((*pbVar2 & 0x12) == 0) {
            FUN_080196d0(0x1c8);
          }
          *pbVar2 = *pbVar2 | 0x12;
          bVar5 = *(byte *)(iVar4 + 0xf) | 0x42;
        }
        *(byte *)(iVar4 + 0xf) = bVar5;
        if (((*pbVar2 & 0x12) == 0) && ((*pbVar2 & 0x22) == 0)) {
          return;
        }
        FUN_0800c8f4();
        return;
      }
      goto LAB_0800e1b0;
    }
    if ((((*(short *)(iVar1 + 8) <= *(short *)(iVar1 + 0x1e)) ||
         (*(short *)(iVar1 + 0x22) <= *(short *)(iVar1 + 0xc))) &&
        ((*(char *)(iVar3 + 8) == '\0' || (*(short *)(iVar1 + 0x1e) <= *(short *)(iVar1 + 8))))) &&
       ((*(char *)(iVar3 + 10) == '\0' || (*(short *)(iVar1 + 0xc) <= *(short *)(iVar1 + 0x22)))))
    goto LAB_0800e1b0;
  }
  pbVar2[3] = 0;
  pbVar2[5] = 0;
  *(undefined2 *)(iVar1 + 0x16) = 0;
LAB_0800e1b0:
  if ((int)((uint)*pbVar2 << 0x1e) < 0) {
    if (pbVar2[4] == 0) {
      if ((((*(char *)(iVar3 + 9) == '\0') && ((int)((uint)*(byte *)(iVar4 + 0xf) << 0x19) < 0)) &&
          (*(short *)(iVar1 + 0x1e) <= *(short *)(iVar1 + 10))) ||
         (((*(char *)(iVar3 + 0xb) == '\0' && ((int)((uint)*(byte *)(iVar4 + 0xf) << 0x18) < 0)) &&
          (*(short *)(iVar1 + 0xe) <= *(short *)(iVar1 + 0x22))))) {
        pbVar2[4] = 1;
        *(undefined2 *)(iVar1 + 0x1a) = 0;
        pbVar2[6] = 1;
      }
    }
    else if (pbVar2[4] != 0) {
      *(short *)(iVar1 + 0x1a) = *(short *)(iVar1 + 0x1a) + 1;
      if ((uint)*(ushort *)(iVar1 + 0x1a) < *(ushort *)(iVar1 + 0x12) / 100) {
        if ((((*(short *)(iVar1 + 10) < *(short *)(iVar1 + 0x1e)) ||
             (*(short *)(iVar1 + 0x22) < *(short *)(iVar1 + 0xe))) ||
            ((*(char *)(iVar3 + 9) != '\0' &&
             (((int)((uint)*(byte *)(iVar4 + 0xf) << 0x19) < 0 &&
              (*(short *)(iVar1 + 0x1e) < *(short *)(iVar1 + 10))))))) ||
           ((*(char *)(iVar3 + 0xb) != '\0' &&
            (((int)((uint)*(byte *)(iVar4 + 0xf) << 0x18) < 0 &&
             (*(short *)(iVar1 + 0xe) < *(short *)(iVar1 + 0x22))))))) {
          pbVar2[4] = 0;
          pbVar2[6] = 0;
          *(undefined2 *)(iVar1 + 0x1a) = 0;
        }
      }
      else {
        pbVar2[4] = 0;
        pbVar2[6] = 0;
        if ((((*(char *)(iVar3 + 9) == '\0') && ((int)((uint)*(byte *)(iVar4 + 0xf) << 0x19) < 0))
            && (*(short *)(iVar1 + 0x1e) <= *(short *)(iVar1 + 10))) ||
           (((*(char *)(iVar3 + 0xb) == '\0' && ((int)((uint)*(byte *)(iVar4 + 0xf) << 0x18) < 0))
            && (*(short *)(iVar1 + 0xe) <= *(short *)(iVar1 + 0x22))))) {
          if (((*pbVar2 & 0x12) != 0) || ((*pbVar2 & 0x22) != 0)) {
            if ((~*(byte *)(iVar4 + 0xf) & 0x31) == 0) {
              bVar5 = *pbVar2 & 0xfd;
            }
            else if ((~*(byte *)(iVar4 + 0xf) & 0x11) == 0) {
              bVar5 = *pbVar2 & 0xdd;
            }
            else if ((~*(byte *)(iVar4 + 0xf) & 0x21) == 0) {
              bVar5 = *pbVar2 & 0xed;
            }
            else {
              bVar5 = *pbVar2 & 0xcd;
            }
            *pbVar2 = bVar5;
            *(byte *)(iVar4 + 0xf) = *(byte *)(iVar4 + 0xf) & 0x3d;
            FUN_0801789a();
            FUN_0800c940();
            if ((*DAT_0800e324 == '\0') && (*DAT_0800e328 == '\0')) {
              FUN_08019844(0x12,10);
              return;
            }
          }
        }
        else {
          *pbVar2 = *pbVar2 & 0xcd;
        }
      }
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800e600 at 0x0800e600
// ---------------------------------------------------------------------------

void FUN_0800e600(void)

{
  char *pcVar1;
  float *pfVar2;
  int iVar3;
  
  iVar3 = DAT_0800e7dc;
  pfVar2 = DAT_0800e7d8;
  pcVar1 = DAT_0800e7d4;
  if (*DAT_0800e7d4 == '\0') {
    if ((*DAT_0800e7e0 < *DAT_0800e7d8) || (*DAT_0800e7d8 < *DAT_0800e7e0 - 2.0)) {
      *DAT_0800e7d8 = *DAT_0800e7e0 - DAT_0800e7e4;
    }
    if ((*pfVar2 < pfVar2[1]) || (pfVar2[1] < *pfVar2 - 1.0)) {
      pfVar2[1] = *pfVar2 - DAT_0800e7e8;
    }
    if (*(char *)(iVar3 + 0x13) == '\0') {
      if (*pfVar2 <= pfVar2[3]) {
        *(undefined1 *)(iVar3 + 0x13) = 1;
        *(undefined2 *)((int)pfVar2 + 0x12) = 0;
        *(undefined1 *)(iVar3 + 0x15) = 1;
      }
    }
    else if (*(char *)(iVar3 + 0x13) != '\0') {
      if ((uint)*(ushort *)((int)pfVar2 + 0x12) < *(ushort *)(pfVar2 + 2) / 10) {
        if (pfVar2[3] < *pfVar2) {
          *(undefined1 *)(iVar3 + 0x15) = 0;
          *(undefined1 *)(iVar3 + 0x13) = 0;
        }
      }
      else {
        *(undefined1 *)(iVar3 + 0x15) = 0;
        *(undefined1 *)(iVar3 + 0x13) = 0;
        if (*pfVar2 <= pfVar2[3]) {
          if ((*DAT_0800e7ec != '\x01') || (*(char *)(iVar3 + 0x3b) == '\0')) {
            FUN_0800ac9c();
          }
          if ((*(byte *)(iVar3 + 0x12) & 1) == 0) {
            FUN_08019844(1,9);
            FUN_080196d0(0x1ce);
          }
          *(byte *)(iVar3 + 0x12) = *(byte *)(iVar3 + 0x12) | 1;
          return;
        }
      }
    }
  }
  if ((pcVar1[1] != '\x01') &&
     ((((*(byte *)(iVar3 + 0x12) & 0x11) != 0 && (*DAT_0800e7f0 != '\0')) ||
      (((*(byte *)(iVar3 + 0x12) & 1) != 0 && (*DAT_0800e7f0 == '\0')))))) {
    if (*(char *)(iVar3 + 0x14) == '\0') {
      if (pfVar2[3] < pfVar2[1]) {
        *(undefined1 *)(iVar3 + 0x14) = 1;
        *(undefined2 *)(pfVar2 + 5) = 0;
        *(undefined1 *)(iVar3 + 0x16) = 1;
      }
    }
    else if (*(char *)(iVar3 + 0x14) != '\0') {
      if ((uint)*(ushort *)(pfVar2 + 5) < *(ushort *)((int)pfVar2 + 10) / 10) {
        if (pfVar2[1] < pfVar2[3]) {
          *(undefined1 *)(iVar3 + 0x14) = 0;
          *(undefined1 *)(iVar3 + 0x16) = 0;
        }
      }
      else {
        *(undefined1 *)(iVar3 + 0x14) = 0;
        *(undefined1 *)(iVar3 + 0x16) = 0;
        if (pfVar2[3] < pfVar2[1]) {
          if ((int)((uint)*(byte *)(iVar3 + 0x12) << 0x1b) < 0) {
            FUN_08019844(0x16,0xb);
          }
          if (((*(byte *)(iVar3 + 0x12) & 1) != 0) && (*DAT_0800e7f4 == '\0')) {
            FUN_08019844(5,0xb);
          }
          *(byte *)(iVar3 + 0x12) = *(byte *)(iVar3 + 0x12) & 0xee;
          FUN_0800acd8();
          return;
        }
      }
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800e7f8 at 0x0800e7f8
// ---------------------------------------------------------------------------

void FUN_0800e7f8(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = DAT_0800e878;
  iVar1 = DAT_0800e874;
  if (*(char *)(DAT_0800e874 + 0x28) == '\0') {
LAB_0800e822:
    *(undefined1 *)(iVar2 + 0x2f) = 0;
    return;
  }
  if (*(char *)(DAT_0800e878 + 0x2f) == '\0') {
    if (*(float *)(DAT_0800e874 + 0x2c) <= *(float *)(DAT_0800e874 + 0xc)) {
      *(short *)(DAT_0800e874 + 0x38) = *(short *)(DAT_0800e874 + 0x38) + 1;
      if ((uint)*(ushort *)(iVar1 + 0x38) < *(ushort *)(iVar1 + 0x34) / 100) {
        return;
      }
      *(undefined2 *)(iVar1 + 0x38) = 0;
      FUN_08019844(0,0x16);
      *(undefined1 *)(iVar2 + 0x2f) = 1;
      return;
    }
  }
  else if (*(float *)(DAT_0800e874 + 0xc) < *(float *)(DAT_0800e874 + 0x30)) {
    *(short *)(DAT_0800e874 + 0x38) = *(short *)(DAT_0800e874 + 0x38) + 1;
    if ((uint)*(ushort *)(iVar1 + 0x38) < *(ushort *)(iVar1 + 0x36) / 100) {
      return;
    }
    *(undefined2 *)(iVar1 + 0x38) = 0;
    goto LAB_0800e822;
  }
  *(undefined2 *)(DAT_0800e874 + 0x38) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800e87c at 0x0800e87c
// ---------------------------------------------------------------------------

void FUN_0800e87c(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = DAT_0800e914;
  iVar1 = DAT_0800e910;
  if (*(char *)(DAT_0800e910 + 0x28) == '\0') {
LAB_0800e8a8:
    *(undefined1 *)(iVar2 + 0x34) = 0;
    return;
  }
  if (*(char *)(DAT_0800e914 + 0x34) == '\0') {
    if (*(float *)(DAT_0800e910 + 0x3c) <= *(float *)(DAT_0800e918 + 0x114)) {
      *(short *)(DAT_0800e910 + 0x48) = *(short *)(DAT_0800e910 + 0x48) + 1;
      if ((uint)*(ushort *)(iVar1 + 0x48) < *(ushort *)(iVar1 + 0x44) / 100) {
        return;
      }
      *(undefined2 *)(iVar1 + 0x48) = 0;
      FUN_08019844(0,0x17);
      *(undefined1 *)(iVar2 + 0x34) = 1;
      return;
    }
  }
  else if (*(float *)(DAT_0800e918 + 0x114) < *(float *)(DAT_0800e910 + 0x40)) {
    *(short *)(DAT_0800e910 + 0x48) = *(short *)(DAT_0800e910 + 0x48) + 1;
    if ((uint)*(ushort *)(iVar1 + 0x48) < *(ushort *)(iVar1 + 0x46) / 100) {
      return;
    }
    *(undefined2 *)(iVar1 + 0x48) = 0;
    goto LAB_0800e8a8;
  }
  *(undefined2 *)(DAT_0800e910 + 0x48) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800e91c at 0x0800e91c
// ---------------------------------------------------------------------------

void FUN_0800e91c(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = DAT_0800e9b4;
  iVar1 = DAT_0800e9b0;
  if (*(char *)(DAT_0800e9b0 + 0x28) == '\0') {
LAB_0800e948:
    *(undefined1 *)(iVar2 + 0x2a) = 0;
    return;
  }
  if (*(char *)(DAT_0800e9b4 + 0x2a) == '\0') {
    if (*(float *)(DAT_0800e9b8 + 0x114) <= *(float *)(DAT_0800e9b0 + 0x3c)) {
      *(short *)(DAT_0800e9b0 + 0x48) = *(short *)(DAT_0800e9b0 + 0x48) + 1;
      if ((uint)*(ushort *)(iVar1 + 0x48) < *(ushort *)(iVar1 + 0x44) / 100) {
        return;
      }
      *(undefined2 *)(iVar1 + 0x48) = 0;
      FUN_08019844(0,0x19);
      *(undefined1 *)(iVar2 + 0x2a) = 1;
      return;
    }
  }
  else if (*(float *)(DAT_0800e9b0 + 0x40) < *(float *)(DAT_0800e9b8 + 0x114)) {
    *(short *)(DAT_0800e9b0 + 0x48) = *(short *)(DAT_0800e9b0 + 0x48) + 1;
    if ((uint)*(ushort *)(iVar1 + 0x48) < *(ushort *)(iVar1 + 0x46) / 100) {
      return;
    }
    *(undefined2 *)(iVar1 + 0x48) = 0;
    goto LAB_0800e948;
  }
  *(undefined2 *)(DAT_0800e9b0 + 0x48) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800e9bc at 0x0800e9bc
// ---------------------------------------------------------------------------

void FUN_0800e9bc(void)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  uint in_fpscr;
  uint uVar6;
  uint uVar7;
  float fVar8;
  float fVar9;
  
  pbVar4 = DAT_0800eba8;
  iVar3 = DAT_0800eba0;
  iVar2 = DAT_0800eb9c;
  if (*(char *)(DAT_0800eb9c + 0x20) == '\0') {
    return;
  }
  fVar8 = (float)VectorUnsignedToFloat((uint)*DAT_0800eba8,(byte)(in_fpscr >> 0x16) & 3);
  uVar6 = in_fpscr & 0xfffffff;
  if (*(float *)(DAT_0800eba0 + 0x18) < (*DAT_0800eba4 - 1.0) * fVar8) {
LAB_0800ea18:
    fVar8 = (float)VectorUnsignedToFloat((uint)*DAT_0800eba8,(byte)(uVar6 >> 0x16) & 3);
    *(float *)(DAT_0800eba0 + 0x18) = (*DAT_0800eba4 - DAT_0800ebac) * fVar8;
  }
  else {
    fVar9 = *(float *)(DAT_0800eba0 + 0x18);
    fVar8 = (float)VectorUnsignedToFloat((uint)*DAT_0800eba8,(byte)(uVar6 >> 0x16) & 3);
    fVar8 = *DAT_0800eba4 * fVar8;
    uVar6 = uVar6 | (uint)(fVar9 < fVar8) << 0x1f | (uint)(fVar9 == fVar8) << 0x1e;
    bVar1 = (byte)(uVar6 >> 0x18);
    if (!(bool)(bVar1 >> 6 & 1) && (bool)(bVar1 >> 7) == (NAN(fVar9) || NAN(fVar8)))
    goto LAB_0800ea18;
  }
  uVar7 = uVar6 & 0xfffffff | (uint)(*(float *)(iVar3 + 0x1c) < *(float *)(iVar3 + 0x18)) << 0x1f;
  if (SUB41(uVar7 >> 0x1f,0) != (NAN(*(float *)(iVar3 + 0x1c)) || NAN(*(float *)(iVar3 + 0x18)))) {
    fVar8 = (float)VectorUnsignedToFloat((uint)*pbVar4,(byte)(uVar7 >> 0x16) & 3);
    fVar8 = *(float *)(iVar3 + 0x18) - fVar8 * 0.5;
    fVar9 = *(float *)(iVar3 + 0x1c);
    uVar7 = uVar6 & 0xfffffff | (uint)(fVar8 < fVar9) << 0x1f | (uint)(fVar8 == fVar9) << 0x1e;
    bVar1 = (byte)(uVar7 >> 0x18);
    if ((bool)(bVar1 >> 6 & 1) || (bool)(bVar1 >> 7) != (NAN(fVar8) || NAN(fVar9)))
    goto LAB_0800ea86;
  }
  fVar8 = (float)VectorUnsignedToFloat((uint)*pbVar4,(byte)(uVar7 >> 0x16) & 3);
  *(float *)(iVar3 + 0x1c) = *(float *)(iVar3 + 0x18) - fVar8 * DAT_0800ebb0;
LAB_0800ea86:
  iVar5 = DAT_0800ebb4;
  if (*(char *)(iVar2 + 0x17) == '\0') {
    if (*(float *)(iVar3 + 0x18) <= *(float *)(DAT_0800ebb4 + 0x114)) {
      *(undefined1 *)(iVar2 + 0x17) = 1;
      *(undefined2 *)(iVar3 + 0x24) = 0;
      *(undefined1 *)(iVar2 + 0x19) = 1;
    }
  }
  else if (*(char *)(iVar2 + 0x17) != '\0') {
    if ((uint)*(ushort *)(iVar3 + 0x24) < *(ushort *)(iVar3 + 0x20) / 10) {
      if (*(float *)(DAT_0800ebb4 + 0x114) < *(float *)(iVar3 + 0x18)) {
        *(undefined1 *)(iVar2 + 0x19) = 0;
        *(undefined1 *)(iVar2 + 0x17) = 0;
      }
    }
    else {
      *(undefined1 *)(iVar2 + 0x19) = 0;
      *(undefined1 *)(iVar2 + 0x17) = 0;
      if (*(float *)(iVar3 + 0x18) <= *(float *)(iVar5 + 0x114)) {
        if ((*DAT_0800ebb8 != '\x01') || (*(char *)(iVar2 + 0x3b) == '\0')) {
          FUN_0800ac9c();
        }
        if (-1 < (int)((uint)*(byte *)(iVar2 + 0x12) << 0x1e)) {
          FUN_08019844(2,9);
          FUN_080196d0(0x1d2);
        }
        *(byte *)(iVar2 + 0x12) = *(byte *)(iVar2 + 0x12) | 2;
        return;
      }
    }
  }
  if ((int)((uint)*(byte *)(iVar2 + 0x12) << 0x1e) < 0) {
    if (*(char *)(iVar2 + 0x18) == '\0') {
      if (*(float *)(iVar5 + 0x114) < *(float *)(iVar3 + 0x1c)) {
        *(undefined1 *)(iVar2 + 0x18) = 1;
        *(undefined2 *)(iVar3 + 0x26) = 0;
        *(undefined1 *)(iVar2 + 0x1a) = 1;
      }
    }
    else if (*(char *)(iVar2 + 0x18) != '\0') {
      if ((uint)*(ushort *)(iVar3 + 0x26) < *(ushort *)(iVar3 + 0x22) / 10) {
        if (*(float *)(iVar3 + 0x1c) < *(float *)(iVar5 + 0x114)) {
          *(undefined1 *)(iVar2 + 0x18) = 0;
          *(undefined1 *)(iVar2 + 0x1a) = 0;
        }
      }
      else {
        *(undefined1 *)(iVar2 + 0x18) = 0;
        *(undefined1 *)(iVar2 + 0x1a) = 0;
        if (*(float *)(iVar5 + 0x114) < *(float *)(iVar3 + 0x1c)) {
          *(byte *)(iVar2 + 0x12) = *(byte *)(iVar2 + 0x12) & 0xfd;
          FUN_0800acd8();
          FUN_08019844(6,0xb);
          return;
        }
      }
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800ebbc at 0x0800ebbc
// ---------------------------------------------------------------------------

void FUN_0800ebbc(void)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  char *pcVar6;
  int iVar7;
  uint in_fpscr;
  uint uVar8;
  uint uVar9;
  float fVar10;
  float fVar11;
  
  pbVar5 = DAT_0800ede8;
  iVar4 = DAT_0800ede0;
  iVar3 = DAT_0800eddc;
  if (*(char *)(DAT_0800eddc + 0x20) != '\0') {
    fVar11 = *(float *)(DAT_0800ede0 + 0x18);
    fVar10 = (float)VectorUnsignedToFloat((uint)*DAT_0800ede8,(byte)(in_fpscr >> 0x16) & 3);
    fVar10 = (*DAT_0800ede4 + 1.5) * fVar10;
    uVar1 = in_fpscr & 0xfffffff;
    uVar8 = uVar1 | (uint)(fVar11 < fVar10) << 0x1f | (uint)(fVar11 == fVar10) << 0x1e;
    bVar2 = (byte)(uVar8 >> 0x18);
    if ((!(bool)(bVar2 >> 6 & 1) && (bool)(bVar2 >> 7) == (NAN(fVar11) || NAN(fVar10))) ||
       (fVar10 = (float)VectorUnsignedToFloat((uint)*DAT_0800ede8,(byte)(uVar8 >> 0x16) & 3),
       uVar8 = uVar1, *(float *)(DAT_0800ede0 + 0x18) < *DAT_0800ede4 * fVar10)) {
      fVar10 = (float)VectorUnsignedToFloat((uint)*DAT_0800ede8,(byte)(uVar8 >> 0x16) & 3);
      *(float *)(DAT_0800ede0 + 0x18) = (*DAT_0800ede4 + DAT_0800edec) * fVar10;
    }
    uVar1 = uVar8 & 0xfffffff | (uint)(*(float *)(iVar4 + 0x1c) == *(float *)(iVar4 + 0x18)) << 0x1e
    ;
    uVar9 = uVar1 | (uint)(*(float *)(iVar4 + 0x18) <= *(float *)(iVar4 + 0x1c)) << 0x1d;
    if ((!(bool)((byte)(uVar9 >> 0x1d) & 1) || SUB41(uVar1 >> 0x1e,0)) ||
       (fVar10 = (float)VectorUnsignedToFloat((uint)*pbVar5,(byte)(uVar9 >> 0x16) & 3),
       uVar9 = uVar8 & 0xfffffff,
       *(float *)(iVar4 + 0x18) + fVar10 * DAT_0800edf0 < *(float *)(iVar4 + 0x1c))) {
      fVar10 = (float)VectorUnsignedToFloat((uint)*pbVar5,(byte)(uVar9 >> 0x16) & 3);
      *(float *)(iVar4 + 0x1c) = *(float *)(iVar4 + 0x18) + fVar10 * DAT_0800edf4;
    }
    iVar7 = DAT_0800edfc;
    pcVar6 = DAT_0800edf8;
    if (*(char *)(iVar3 + 0x21) == '\0') {
      if (*(float *)(DAT_0800edfc + 0x114) <= *(float *)(iVar4 + 0x18)) {
        *(undefined1 *)(iVar3 + 0x21) = 1;
        *(undefined2 *)(iVar4 + 0x24) = 0;
        *(undefined1 *)(iVar3 + 0x23) = 1;
      }
    }
    else if (*(char *)(iVar3 + 0x21) != '\0') {
      if ((uint)*(ushort *)(iVar4 + 0x24) < *(ushort *)(iVar4 + 0x20) / 10) {
        if (*(float *)(iVar4 + 0x18) < *(float *)(DAT_0800edfc + 0x114)) {
          *(undefined1 *)(iVar3 + 0x23) = 0;
          *(undefined1 *)(iVar3 + 0x21) = 0;
        }
      }
      else {
        *(undefined1 *)(iVar3 + 0x23) = 0;
        *(undefined1 *)(iVar3 + 0x21) = 0;
        *(undefined2 *)(iVar4 + 0x24) = 0;
        if (*(float *)(iVar7 + 0x114) <= *(float *)(iVar4 + 0x18)) {
          if ((*pcVar6 == '\0') || (*(char *)(iVar3 + 0x3a) == '\0')) {
            FUN_0800c8f4();
          }
          if (-1 < (int)((uint)*(byte *)(iVar3 + 0x1b) << 0x1e)) {
            FUN_08019844(4,8);
            FUN_080196d0(0x1d4);
          }
          *(byte *)(iVar3 + 0x1b) = *(byte *)(iVar3 + 0x1b) | 2;
          return;
        }
      }
    }
    if ((int)((uint)*(byte *)(iVar3 + 0x1b) << 0x1e) < 0) {
      if (*(char *)(iVar3 + 0x22) == '\0') {
        if (*(float *)(iVar4 + 0x1c) < *(float *)(iVar7 + 0x114)) {
          *(undefined1 *)(iVar3 + 0x22) = 1;
          *(undefined2 *)(iVar4 + 0x26) = 0;
          *(undefined1 *)(iVar3 + 0x24) = 1;
        }
      }
      else if (*(char *)(iVar3 + 0x22) != '\0') {
        if ((uint)*(ushort *)(iVar4 + 0x26) < *(ushort *)(iVar4 + 0x22) / 10) {
          if (*(float *)(iVar7 + 0x114) < *(float *)(iVar4 + 0x1c)) {
            *(undefined1 *)(iVar3 + 0x22) = 0;
            *(undefined1 *)(iVar3 + 0x24) = 0;
          }
        }
        else {
          *(undefined1 *)(iVar3 + 0x22) = 0;
          *(undefined1 *)(iVar3 + 0x24) = 0;
          *(undefined2 *)(iVar4 + 0x26) = 0;
          if (*(float *)(iVar4 + 0x1c) < *(float *)(iVar7 + 0x114)) {
            *(byte *)(iVar3 + 0x1b) = *(byte *)(iVar3 + 0x1b) & 0xfd;
            if ((*(char *)(iVar3 + 0x3a) == '\0') || (*pcVar6 == '\0')) {
              FUN_0800c940();
            }
            else {
              FUN_0800f4c8();
              thunk_FUN_0800ceec();
              *(undefined1 *)(iVar3 + 0x4c) = 1;
            }
            FUN_08019844(8,10);
            return;
          }
        }
      }
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800ee00 at 0x0800ee00
// ---------------------------------------------------------------------------

void FUN_0800ee00(void)

{
  int iVar1;
  char *pcVar2;
  float *pfVar3;
  int iVar4;
  
  iVar4 = DAT_0800efd8;
  pfVar3 = DAT_0800efd4;
  pcVar2 = DAT_0800efd0;
  iVar1 = DAT_0800efcc;
  if (*(char *)(DAT_0800efcc + 2) == '\0') {
    if ((*DAT_0800efd4 < *DAT_0800efdc) || (*DAT_0800efdc + 3.5 < *DAT_0800efd4)) {
      *DAT_0800efd4 = *DAT_0800efdc + DAT_0800efe0;
    }
    if ((pfVar3[1] < *pfVar3) || (*pfVar3 + 2.0 < pfVar3[1])) {
      pfVar3[1] = *pfVar3 + 0.5;
    }
    if (*(char *)(iVar4 + 0x1c) == '\0') {
      if (pfVar3[3] <= *pfVar3) {
        *(undefined1 *)(iVar4 + 0x1c) = 1;
        *(undefined2 *)((int)pfVar3 + 0x12) = 0;
        *(undefined1 *)(iVar4 + 0x1e) = 1;
      }
    }
    else if (*(char *)(iVar4 + 0x1c) != '\0') {
      if ((uint)*(ushort *)((int)pfVar3 + 0x12) < *(ushort *)(pfVar3 + 2) / 10) {
        if (*pfVar3 < pfVar3[3]) {
          *(undefined1 *)(iVar4 + 0x1e) = 0;
          *(undefined1 *)(iVar4 + 0x1c) = 0;
        }
      }
      else {
        *(undefined1 *)(iVar4 + 0x1e) = 0;
        *(undefined1 *)(iVar4 + 0x1c) = 0;
        *(undefined2 *)((int)pfVar3 + 0x12) = 0;
        if (pfVar3[3] <= *pfVar3) {
          if ((*pcVar2 == '\0') || (*(char *)(iVar4 + 0x3a) == '\0')) {
            FUN_0800c8f4();
          }
          if ((*(byte *)(iVar4 + 0x1b) & 1) == 0) {
            FUN_08019844(3,8);
            FUN_080196d0(0x1d0);
          }
          *(byte *)(iVar4 + 0x1b) = *(byte *)(iVar4 + 0x1b) | 1;
          return;
        }
      }
    }
  }
  if ((*(char *)(iVar1 + 2) != '\x01') && ((*(byte *)(iVar4 + 0x1b) & 1) != 0)) {
    if (*(char *)(iVar4 + 0x1d) == '\0') {
      if (pfVar3[1] < pfVar3[3]) {
        *(undefined1 *)(iVar4 + 0x1d) = 1;
        *(undefined2 *)(pfVar3 + 5) = 0;
        *(undefined1 *)(iVar4 + 0x1f) = 1;
      }
    }
    else if (*(char *)(iVar4 + 0x1d) != '\0') {
      if ((uint)*(ushort *)(pfVar3 + 5) < *(ushort *)((int)pfVar3 + 10) / 10) {
        if (pfVar3[3] < pfVar3[1]) {
          *(undefined1 *)(iVar4 + 0x1d) = 0;
          *(undefined1 *)(iVar4 + 0x1f) = 0;
        }
      }
      else {
        *(undefined1 *)(iVar4 + 0x1d) = 0;
        *(undefined1 *)(iVar4 + 0x1f) = 0;
        *(undefined2 *)(pfVar3 + 5) = 0;
        if (pfVar3[1] < pfVar3[3]) {
          *(byte *)(iVar4 + 0x1b) = *(byte *)(iVar4 + 0x1b) & 0xfe;
          if ((*(char *)(iVar4 + 0x3a) == '\0') || (*pcVar2 == '\0')) {
            FUN_0800c940();
          }
          else {
            FUN_0800f4c8();
            thunk_FUN_0800ceec();
            *(undefined1 *)(iVar4 + 0x4c) = 1;
          }
          if (*DAT_0800efe4 == '\0') {
            FUN_08019844(7,10);
            return;
          }
        }
      }
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800efe8 at 0x0800efe8
// ---------------------------------------------------------------------------

void FUN_0800efe8(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = DAT_0800f068;
  iVar1 = DAT_0800f064;
  if (*(char *)(DAT_0800f064 + 0x28) == '\0') {
LAB_0800f012:
    *(undefined1 *)(iVar2 + 0x25) = 0;
    return;
  }
  if (*(char *)(DAT_0800f068 + 0x25) == '\0') {
    if (*(float *)(DAT_0800f064 + 0xc) <= *(float *)(DAT_0800f064 + 0x2c)) {
      *(short *)(DAT_0800f064 + 0x38) = *(short *)(DAT_0800f064 + 0x38) + 1;
      if ((uint)*(ushort *)(iVar1 + 0x38) < *(ushort *)(iVar1 + 0x34) / 100) {
        return;
      }
      *(undefined2 *)(iVar1 + 0x38) = 0;
      FUN_08019844(0,0x18);
      *(undefined1 *)(iVar2 + 0x25) = 1;
      return;
    }
  }
  else if (*(float *)(DAT_0800f064 + 0x30) < *(float *)(DAT_0800f064 + 0xc)) {
    *(short *)(DAT_0800f064 + 0x38) = *(short *)(DAT_0800f064 + 0x38) + 1;
    if ((uint)*(ushort *)(iVar1 + 0x38) < *(ushort *)(iVar1 + 0x36) / 100) {
      return;
    }
    *(undefined2 *)(iVar1 + 0x38) = 0;
    goto LAB_0800f012;
  }
  *(undefined2 *)(DAT_0800f064 + 0x38) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f06c at 0x0800f06c
// ---------------------------------------------------------------------------

void FUN_0800f06c(void)

{
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f06e at 0x0800f06e
// ---------------------------------------------------------------------------

void FUN_0800f06e(void)

{
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f070 at 0x0800f070
// ---------------------------------------------------------------------------

void FUN_0800f070(void)

{
  int iVar1;
  undefined1 uVar2;
  
  iVar1 = DAT_0800f0b8;
  uVar2 = 0;
  if ((*(char *)(DAT_0800f0b8 + 3) != '\0') &&
     (*(short *)(DAT_0800f0b8 + 0x48) = *(short *)(DAT_0800f0b8 + 0x48) + 1,
     0x95 < *(ushort *)(iVar1 + 0x48))) {
    *(undefined2 *)(iVar1 + 0x48) = 0;
    *(undefined1 *)(iVar1 + 3) = 0;
  }
  if (*(char *)(DAT_0800f0bc + 0x3b) == '\0') {
    if (*(ushort *)(iVar1 + 0x4a) < 0x96) {
      *(short *)(iVar1 + 0x4a) = *(short *)(iVar1 + 0x4a) + 1;
      return;
    }
    uVar2 = 1;
  }
  else {
    *(undefined2 *)(iVar1 + 0x4a) = 0;
  }
  *(undefined1 *)(iVar1 + 5) = uVar2;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f0f0 at 0x0800f0f0
// ---------------------------------------------------------------------------

void FUN_0800f0f0(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  
  iVar4 = DAT_0800f1fc;
  iVar3 = DAT_0800f1f8;
  iVar2 = DAT_0800f1f4;
  iVar1 = DAT_0800f1f0;
  if (*(char *)(DAT_0800f1f0 + 0x48) == '\0') {
    return;
  }
  if ((*(byte *)(DAT_0800f1f4 + 0xf) & 1) == 0) {
    if (*(short *)(DAT_0800f1f8 + 0x118) < *(short *)(DAT_0800f1f0 + 0x4a)) {
      *(undefined1 *)(DAT_0800f1fc + 0x1b) = 0;
    }
    else {
      *(char *)(DAT_0800f1fc + 0x1b) = *(char *)(DAT_0800f1fc + 0x1b) + '\x01';
      if (*DAT_0800f208 <= (ushort)*(byte *)(iVar4 + 0x1b)) {
        *(undefined1 *)(iVar4 + 0x1b) = 0;
        *(byte *)(iVar2 + 0xf) = *(byte *)(iVar2 + 0xf) | 1;
        uVar5 = 0x75;
LAB_0800f140:
        FUN_08019844(0,uVar5);
      }
    }
  }
  else if ((*(byte *)(DAT_0800f1f4 + 0xf) & 1) != 0) {
    if (*DAT_0800f200 < *(short *)(DAT_0800f1f8 + 0x118)) {
      *(undefined1 *)(DAT_0800f1fc + 0x1c) = 0;
    }
    else {
      *(char *)(DAT_0800f1fc + 0x1c) = *(char *)(DAT_0800f1fc + 0x1c) + '\x01';
      if (*DAT_0800f204 <= (ushort)*(byte *)(iVar4 + 0x1c)) {
        *(undefined1 *)(iVar4 + 0x1c) = 0;
        *(byte *)(iVar2 + 0xf) = *(byte *)(iVar2 + 0xf) & 0xfe;
        uVar5 = 0x76;
        goto LAB_0800f140;
      }
    }
  }
  if ((int)((uint)*(byte *)(iVar2 + 0xf) << 0x1e) < 0) {
    if ((int)((uint)*(byte *)(iVar2 + 0xf) << 0x1e) < 0) {
      if (*(short *)(iVar3 + 0x118) < *DAT_0800f210) {
        *(undefined1 *)(iVar4 + 0x1e) = 0;
      }
      else {
        *(char *)(iVar4 + 0x1e) = *(char *)(iVar4 + 0x1e) + '\x01';
        if (*DAT_0800f214 <= (ushort)*(byte *)(iVar4 + 0x1e)) {
          *(undefined1 *)(iVar4 + 0x1e) = 0;
          *(byte *)(iVar2 + 0xf) = *(byte *)(iVar2 + 0xf) & 0xfd;
          uVar5 = 0x78;
          goto LAB_0800f1e2;
        }
      }
    }
  }
  else if (*(short *)(iVar1 + 0x4c) < *(short *)(iVar3 + 0x118)) {
    *(undefined1 *)(iVar4 + 0x1d) = 0;
  }
  else {
    *(char *)(iVar4 + 0x1d) = *(char *)(iVar4 + 0x1d) + '\x01';
    if (*DAT_0800f20c <= (ushort)*(byte *)(iVar4 + 0x1d)) {
      *(undefined1 *)(iVar4 + 0x1d) = 0;
      *(byte *)(iVar2 + 0xf) = *(byte *)(iVar2 + 0xf) | 2;
      uVar5 = 0x77;
LAB_0800f1e2:
      FUN_08019844(0,uVar5);
      return;
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f218 at 0x0800f218
// ---------------------------------------------------------------------------

void FUN_0800f218(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  
  iVar4 = DAT_0800f358;
  iVar3 = DAT_0800f354;
  iVar2 = DAT_0800f350;
  iVar1 = DAT_0800f34c;
  if ((*(byte *)(DAT_0800f34c + 0x10) & 1) == 0) {
    if (*(short *)(DAT_0800f350 + 0x118) < *(short *)(DAT_0800f354 + 0x4e)) {
      *(undefined1 *)(DAT_0800f358 + 0x21) = 0;
    }
    else {
      *(char *)(DAT_0800f358 + 0x21) = *(char *)(DAT_0800f358 + 0x21) + '\x01';
      if (4 < *(byte *)(iVar4 + 0x21)) {
        *(undefined1 *)(iVar4 + 0x21) = 0;
        if ((*(byte *)(iVar1 + 0x10) & 1) == 0) {
          *(byte *)(iVar1 + 0x10) = *(byte *)(iVar1 + 0x10) | 1;
          FUN_0800c8f4();
          FUN_0800ac9c();
        }
        uVar5 = 0x7b;
LAB_0800f26a:
        FUN_08019844(0,uVar5);
      }
    }
  }
  else if ((*(byte *)(DAT_0800f34c + 0x10) & 1) != 0) {
    if (*(short *)(DAT_0800f354 + 0x50) < *(short *)(DAT_0800f350 + 0x118)) {
      *(undefined1 *)(DAT_0800f358 + 0x22) = 0;
    }
    else {
      *(char *)(DAT_0800f358 + 0x22) = *(char *)(DAT_0800f358 + 0x22) + '\x01';
      if (4 < *(byte *)(iVar4 + 0x22)) {
        *(undefined1 *)(iVar4 + 0x22) = 0;
        *(byte *)(iVar1 + 0x10) = *(byte *)(iVar1 + 0x10) & 0xfe;
        FUN_0800c940();
        FUN_0800acd8();
        uVar5 = 0x7c;
        goto LAB_0800f26a;
      }
    }
  }
  if ((int)((uint)*(byte *)(iVar1 + 0x10) << 0x1e) < 0) {
    if ((int)((uint)*(byte *)(iVar1 + 0x10) << 0x1e) < 0) {
      if (*(short *)(iVar2 + 0x118) < *(short *)(iVar3 + 0x54)) {
        *(undefined1 *)(iVar4 + 0x24) = 0;
      }
      else {
        *(char *)(iVar4 + 0x24) = *(char *)(iVar4 + 0x24) + '\x01';
        if (4 < *(byte *)(iVar4 + 0x24)) {
          *(undefined1 *)(iVar4 + 0x24) = 0;
          *(byte *)(iVar1 + 0x10) = *(byte *)(iVar1 + 0x10) & 0xfd;
          FUN_0800c940();
          FUN_0800acd8();
          uVar5 = 0x7e;
          goto LAB_0800f33c;
        }
      }
    }
  }
  else if (*(short *)(iVar3 + 0x52) < *(short *)(iVar2 + 0x118)) {
    *(undefined1 *)(iVar4 + 0x23) = 0;
  }
  else {
    *(char *)(iVar4 + 0x23) = *(char *)(iVar4 + 0x23) + '\x01';
    if (4 < *(byte *)(iVar4 + 0x23)) {
      *(undefined1 *)(iVar4 + 0x23) = 0;
      if (-1 < (int)((uint)*(byte *)(iVar1 + 0x10) << 0x1e)) {
        *(byte *)(iVar1 + 0x10) = *(byte *)(iVar1 + 0x10) | 2;
        FUN_0800c8f4();
        FUN_0800ac9c();
      }
      uVar5 = 0x7d;
LAB_0800f33c:
      FUN_08019844(0,uVar5);
      return;
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: EXTI0_IRQHandler at 0x0800f35c
// ---------------------------------------------------------------------------

/* WARNING: Removing unreachable block (ram,0x08011312) */
/* WARNING: Removing unreachable block (ram,0x08011316) */
/* WARNING: Removing unreachable block (ram,0x0801131a) */
/* WARNING: Removing unreachable block (ram,0x0801131e) */
/* WARNING: Removing unreachable block (ram,0x08011322) */
/* WARNING: Removing unreachable block (ram,0x08011326) */
/* WARNING: Removing unreachable block (ram,0x0801132a) */

void EXTI0_IRQHandler(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar1 = DAT_08011414;
  FUN_080102cc(DAT_08011414,1);
  uVar2 = DAT_08011418;
  FUN_080102cc(DAT_08011418,2);
  FUN_080102cc(uVar1,4);
  FUN_080102cc(uVar2,8);
  iVar3 = DAT_0801141c;
  FUN_080102cc(DAT_0801141c,0x10);
  FUN_080102cc(uVar1,0x20);
  FUN_080102cc(uVar1,0x80);
  FUN_080102cc(uVar1,0x8000);
  FUN_0800f3d0(1);
  FUN_0800f3d0(2);
  FUN_0800f3d0(4);
  FUN_0800f3d0(8);
  FUN_0800f3d0(0x10);
  FUN_0800f3d0(0x20);
  FUN_0800f3d0(0x80);
  FUN_0800f3d0(0x8000);
  FUN_08017cb0(4,1);
  FUN_08017cb0(8,1);
  FUN_08017cb0(0x10,1);
  FUN_08017cb0(0x20,1);
  *(undefined4 *)(iVar3 + 0x14) = 1;
  *(undefined4 *)(iVar3 + 0x14) = 0x80;
  *DAT_08011420 = 0;
  *(undefined4 *)(DAT_08011424 + 4) = 0;
  *DAT_08011428 = 0;
  *(undefined2 *)(DAT_0801142c + 0x260) = 0;
  *DAT_08011430 = 0;
  *(undefined2 *)(DAT_08011434 + 0x260) = 0;
  *DAT_08011438 = 0;
  *(undefined2 *)(DAT_0801143c + 0x260) = 0;
  *DAT_08011440 = 0;
  *(undefined2 *)(DAT_08011444 + 0x260) = 0;
  *DAT_08011448 = 0;
  *(undefined2 *)(DAT_0801144c + 0x260) = 0;
  *DAT_08011450 = 0;
  *(undefined2 *)(DAT_08011454 + 0x260) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: USART3_IRQHandler at 0x0800f362
// ---------------------------------------------------------------------------

void USART3_IRQHandler(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 extraout_r2_01;
  undefined4 uVar3;
  undefined4 extraout_r3;
  undefined4 extraout_r3_00;
  undefined4 extraout_r3_01;
  undefined4 uVar4;
  undefined4 unaff_r4;
  int iVar5;
  
  iVar5 = 0x1000;
  iVar2 = FUN_0800f3dc(0x1000);
  uVar3 = extraout_r2;
  uVar4 = extraout_r3;
  if (iVar2 == 0) {
    iVar5 = 0x2000;
    iVar2 = FUN_0800f3dc(0x2000);
    uVar3 = extraout_r2_00;
    uVar4 = extraout_r3_00;
    if (iVar2 == 0) {
      iVar5 = 0x8000;
      iVar2 = FUN_0800f3dc(0x8000);
      uVar3 = extraout_r2_01;
      uVar4 = extraout_r3_01;
      if (iVar2 == 0) {
        return;
      }
    }
  }
  uVar1 = DAT_08011414;
  if (((((iVar5 == 1) || (iVar5 == 2)) || (iVar5 == 4)) || ((iVar5 == 8 || (iVar5 == 0x10)))) ||
     ((iVar5 == 0x20 || ((iVar5 == 0x80 || (iVar5 == 0x8000)))))) {
    FUN_080102cc(DAT_08011414,1,uVar3,uVar4,unaff_r4);
    uVar3 = DAT_08011418;
    FUN_080102cc(DAT_08011418,2);
    FUN_080102cc(uVar1,4);
    FUN_080102cc(uVar3,8);
    iVar2 = DAT_0801141c;
    FUN_080102cc(DAT_0801141c,0x10);
    FUN_080102cc(uVar1,0x20);
    FUN_080102cc(uVar1,0x80);
    FUN_080102cc(uVar1,0x8000);
    FUN_0800f3d0(1);
    FUN_0800f3d0(2);
    FUN_0800f3d0(4);
    FUN_0800f3d0(8);
    FUN_0800f3d0(0x10);
    FUN_0800f3d0(0x20);
    FUN_0800f3d0(0x80);
    FUN_0800f3d0(0x8000);
    FUN_08017cb0(4,1);
    FUN_08017cb0(8,1);
    FUN_08017cb0(0x10,1);
    FUN_08017cb0(0x20,1);
    *(undefined4 *)(iVar2 + 0x14) = 1;
    *(undefined4 *)(iVar2 + 0x14) = 0x80;
    *DAT_08011420 = 0;
  }
  *(undefined4 *)(DAT_08011424 + 4) = 0;
  *DAT_08011428 = 0;
  *(undefined2 *)(DAT_0801142c + 0x260) = 0;
  *DAT_08011430 = 0;
  *(undefined2 *)(DAT_08011434 + 0x260) = 0;
  *DAT_08011438 = 0;
  *(undefined2 *)(DAT_0801143c + 0x260) = 0;
  *DAT_08011440 = 0;
  *(undefined2 *)(DAT_08011444 + 0x260) = 0;
  *DAT_08011448 = 0;
  *(undefined2 *)(DAT_0801144c + 0x260) = 0;
  *DAT_08011450 = 0;
  *(undefined2 *)(DAT_08011454 + 0x260) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: EXTI1_IRQHandler at 0x0800f392
// ---------------------------------------------------------------------------

/* WARNING: Removing unreachable block (ram,0x08011316) */
/* WARNING: Removing unreachable block (ram,0x0801131a) */
/* WARNING: Removing unreachable block (ram,0x0801131e) */
/* WARNING: Removing unreachable block (ram,0x08011322) */
/* WARNING: Removing unreachable block (ram,0x08011326) */
/* WARNING: Removing unreachable block (ram,0x0801132a) */

void EXTI1_IRQHandler(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar1 = DAT_08011414;
  FUN_080102cc(DAT_08011414,1);
  uVar2 = DAT_08011418;
  FUN_080102cc(DAT_08011418,2);
  FUN_080102cc(uVar1,4);
  FUN_080102cc(uVar2,8);
  iVar3 = DAT_0801141c;
  FUN_080102cc(DAT_0801141c,0x10);
  FUN_080102cc(uVar1,0x20);
  FUN_080102cc(uVar1,0x80);
  FUN_080102cc(uVar1,0x8000);
  FUN_0800f3d0(1);
  FUN_0800f3d0(2);
  FUN_0800f3d0(4);
  FUN_0800f3d0(8);
  FUN_0800f3d0(0x10);
  FUN_0800f3d0(0x20);
  FUN_0800f3d0(0x80);
  FUN_0800f3d0(0x8000);
  FUN_08017cb0(4,1);
  FUN_08017cb0(8,1);
  FUN_08017cb0(0x10,1);
  FUN_08017cb0(0x20,1);
  *(undefined4 *)(iVar3 + 0x14) = 1;
  *(undefined4 *)(iVar3 + 0x14) = 0x80;
  *DAT_08011420 = 0;
  *(undefined4 *)(DAT_08011424 + 4) = 0;
  *DAT_08011428 = 0;
  *(undefined2 *)(DAT_0801142c + 0x260) = 0;
  *DAT_08011430 = 0;
  *(undefined2 *)(DAT_08011434 + 0x260) = 0;
  *DAT_08011438 = 0;
  *(undefined2 *)(DAT_0801143c + 0x260) = 0;
  *DAT_08011440 = 0;
  *(undefined2 *)(DAT_08011444 + 0x260) = 0;
  *DAT_08011448 = 0;
  *(undefined2 *)(DAT_0801144c + 0x260) = 0;
  *DAT_08011450 = 0;
  *(undefined2 *)(DAT_08011454 + 0x260) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: EXTI2_IRQHandler at 0x0800f398
// ---------------------------------------------------------------------------

/* WARNING: Removing unreachable block (ram,0x0801131a) */
/* WARNING: Removing unreachable block (ram,0x0801131e) */
/* WARNING: Removing unreachable block (ram,0x08011322) */
/* WARNING: Removing unreachable block (ram,0x08011326) */
/* WARNING: Removing unreachable block (ram,0x0801132a) */

void EXTI2_IRQHandler(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar1 = DAT_08011414;
  FUN_080102cc(DAT_08011414,1);
  uVar2 = DAT_08011418;
  FUN_080102cc(DAT_08011418,2);
  FUN_080102cc(uVar1,4);
  FUN_080102cc(uVar2,8);
  iVar3 = DAT_0801141c;
  FUN_080102cc(DAT_0801141c,0x10);
  FUN_080102cc(uVar1,0x20);
  FUN_080102cc(uVar1,0x80);
  FUN_080102cc(uVar1,0x8000);
  FUN_0800f3d0(1);
  FUN_0800f3d0(2);
  FUN_0800f3d0(4);
  FUN_0800f3d0(8);
  FUN_0800f3d0(0x10);
  FUN_0800f3d0(0x20);
  FUN_0800f3d0(0x80);
  FUN_0800f3d0(0x8000);
  FUN_08017cb0(4,1);
  FUN_08017cb0(8,1);
  FUN_08017cb0(0x10,1);
  FUN_08017cb0(0x20,1);
  *(undefined4 *)(iVar3 + 0x14) = 1;
  *(undefined4 *)(iVar3 + 0x14) = 0x80;
  *DAT_08011420 = 0;
  *(undefined4 *)(DAT_08011424 + 4) = 0;
  *DAT_08011428 = 0;
  *(undefined2 *)(DAT_0801142c + 0x260) = 0;
  *DAT_08011430 = 0;
  *(undefined2 *)(DAT_08011434 + 0x260) = 0;
  *DAT_08011438 = 0;
  *(undefined2 *)(DAT_0801143c + 0x260) = 0;
  *DAT_08011440 = 0;
  *(undefined2 *)(DAT_08011444 + 0x260) = 0;
  *DAT_08011448 = 0;
  *(undefined2 *)(DAT_0801144c + 0x260) = 0;
  *DAT_08011450 = 0;
  *(undefined2 *)(DAT_08011454 + 0x260) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: EXTI3_IRQHandler at 0x0800f39e
// ---------------------------------------------------------------------------

/* WARNING: Removing unreachable block (ram,0x0801131e) */
/* WARNING: Removing unreachable block (ram,0x08011322) */
/* WARNING: Removing unreachable block (ram,0x08011326) */
/* WARNING: Removing unreachable block (ram,0x0801132a) */

void EXTI3_IRQHandler(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar1 = DAT_08011414;
  FUN_080102cc(DAT_08011414,1);
  uVar2 = DAT_08011418;
  FUN_080102cc(DAT_08011418,2);
  FUN_080102cc(uVar1,4);
  FUN_080102cc(uVar2,8);
  iVar3 = DAT_0801141c;
  FUN_080102cc(DAT_0801141c,0x10);
  FUN_080102cc(uVar1,0x20);
  FUN_080102cc(uVar1,0x80);
  FUN_080102cc(uVar1,0x8000);
  FUN_0800f3d0(1);
  FUN_0800f3d0(2);
  FUN_0800f3d0(4);
  FUN_0800f3d0(8);
  FUN_0800f3d0(0x10);
  FUN_0800f3d0(0x20);
  FUN_0800f3d0(0x80);
  FUN_0800f3d0(0x8000);
  FUN_08017cb0(4,1);
  FUN_08017cb0(8,1);
  FUN_08017cb0(0x10,1);
  FUN_08017cb0(0x20,1);
  *(undefined4 *)(iVar3 + 0x14) = 1;
  *(undefined4 *)(iVar3 + 0x14) = 0x80;
  *DAT_08011420 = 0;
  *(undefined4 *)(DAT_08011424 + 4) = 0;
  *DAT_08011428 = 0;
  *(undefined2 *)(DAT_0801142c + 0x260) = 0;
  *DAT_08011430 = 0;
  *(undefined2 *)(DAT_08011434 + 0x260) = 0;
  *DAT_08011438 = 0;
  *(undefined2 *)(DAT_0801143c + 0x260) = 0;
  *DAT_08011440 = 0;
  *(undefined2 *)(DAT_08011444 + 0x260) = 0;
  *DAT_08011448 = 0;
  *(undefined2 *)(DAT_0801144c + 0x260) = 0;
  *DAT_08011450 = 0;
  *(undefined2 *)(DAT_08011454 + 0x260) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: EXTI4_IRQHandler at 0x0800f3a4
// ---------------------------------------------------------------------------

/* WARNING: Removing unreachable block (ram,0x08011322) */
/* WARNING: Removing unreachable block (ram,0x08011326) */
/* WARNING: Removing unreachable block (ram,0x0801132a) */

void EXTI4_IRQHandler(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar1 = DAT_08011414;
  FUN_080102cc(DAT_08011414,1);
  uVar2 = DAT_08011418;
  FUN_080102cc(DAT_08011418,2);
  FUN_080102cc(uVar1,4);
  FUN_080102cc(uVar2,8);
  iVar3 = DAT_0801141c;
  FUN_080102cc(DAT_0801141c,0x10);
  FUN_080102cc(uVar1,0x20);
  FUN_080102cc(uVar1,0x80);
  FUN_080102cc(uVar1,0x8000);
  FUN_0800f3d0(1);
  FUN_0800f3d0(2);
  FUN_0800f3d0(4);
  FUN_0800f3d0(8);
  FUN_0800f3d0(0x10);
  FUN_0800f3d0(0x20);
  FUN_0800f3d0(0x80);
  FUN_0800f3d0(0x8000);
  FUN_08017cb0(4,1);
  FUN_08017cb0(8,1);
  FUN_08017cb0(0x10,1);
  FUN_08017cb0(0x20,1);
  *(undefined4 *)(iVar3 + 0x14) = 1;
  *(undefined4 *)(iVar3 + 0x14) = 0x80;
  *DAT_08011420 = 0;
  *(undefined4 *)(DAT_08011424 + 4) = 0;
  *DAT_08011428 = 0;
  *(undefined2 *)(DAT_0801142c + 0x260) = 0;
  *DAT_08011430 = 0;
  *(undefined2 *)(DAT_08011434 + 0x260) = 0;
  *DAT_08011438 = 0;
  *(undefined2 *)(DAT_0801143c + 0x260) = 0;
  *DAT_08011440 = 0;
  *(undefined2 *)(DAT_08011444 + 0x260) = 0;
  *DAT_08011448 = 0;
  *(undefined2 *)(DAT_0801144c + 0x260) = 0;
  *DAT_08011450 = 0;
  *(undefined2 *)(DAT_08011454 + 0x260) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: CAN1_SCE_IRQHandler at 0x0800f3aa
// ---------------------------------------------------------------------------

void CAN1_SCE_IRQHandler(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 uVar3;
  undefined4 extraout_r3;
  undefined4 extraout_r3_00;
  undefined4 uVar4;
  undefined4 unaff_r4;
  
  iVar2 = FUN_0800f3dc(0x20);
  if (iVar2 == 0) {
    iVar2 = FUN_0800f3dc(0x80);
    if (iVar2 == 0) {
      return;
    }
    iVar2 = 0x80;
    uVar3 = extraout_r2_00;
    uVar4 = extraout_r3_00;
  }
  else {
    iVar2 = 0x20;
    uVar3 = extraout_r2;
    uVar4 = extraout_r3;
  }
  uVar1 = DAT_08011414;
  if (((((iVar2 == 1) || (iVar2 == 2)) || (iVar2 == 4)) || ((iVar2 == 8 || (iVar2 == 0x10)))) ||
     ((iVar2 == 0x20 || ((iVar2 == 0x80 || (iVar2 == 0x8000)))))) {
    FUN_080102cc(DAT_08011414,1,uVar3,uVar4,unaff_r4);
    uVar3 = DAT_08011418;
    FUN_080102cc(DAT_08011418,2);
    FUN_080102cc(uVar1,4);
    FUN_080102cc(uVar3,8);
    iVar2 = DAT_0801141c;
    FUN_080102cc(DAT_0801141c,0x10);
    FUN_080102cc(uVar1,0x20);
    FUN_080102cc(uVar1,0x80);
    FUN_080102cc(uVar1,0x8000);
    FUN_0800f3d0(1);
    FUN_0800f3d0(2);
    FUN_0800f3d0(4);
    FUN_0800f3d0(8);
    FUN_0800f3d0(0x10);
    FUN_0800f3d0(0x20);
    FUN_0800f3d0(0x80);
    FUN_0800f3d0(0x8000);
    FUN_08017cb0(4,1);
    FUN_08017cb0(8,1);
    FUN_08017cb0(0x10,1);
    FUN_08017cb0(0x20,1);
    *(undefined4 *)(iVar2 + 0x14) = 1;
    *(undefined4 *)(iVar2 + 0x14) = 0x80;
    *DAT_08011420 = 0;
  }
  *(undefined4 *)(DAT_08011424 + 4) = 0;
  *DAT_08011428 = 0;
  *(undefined2 *)(DAT_0801142c + 0x260) = 0;
  *DAT_08011430 = 0;
  *(undefined2 *)(DAT_08011434 + 0x260) = 0;
  *DAT_08011438 = 0;
  *(undefined2 *)(DAT_0801143c + 0x260) = 0;
  *DAT_08011440 = 0;
  *(undefined2 *)(DAT_08011444 + 0x260) = 0;
  *DAT_08011448 = 0;
  *(undefined2 *)(DAT_0801144c + 0x260) = 0;
  *DAT_08011450 = 0;
  *(undefined2 *)(DAT_08011454 + 0x260) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f3d0 at 0x0800f3d0
// ---------------------------------------------------------------------------

void FUN_0800f3d0(undefined4 param_1)

{
  *DAT_0800f3d8 = param_1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f3dc at 0x0800f3dc
// ---------------------------------------------------------------------------

undefined4 FUN_0800f3dc(uint param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (((DAT_0800f3f8[5] & param_1) != 0) && ((*DAT_0800f3f8 & param_1) != 0)) {
    uVar1 = 1;
  }
  return uVar1;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f3fc at 0x0800f3fc
// ---------------------------------------------------------------------------

void FUN_0800f3fc(uint *param_1)

{
  uint *puVar1;
  uint *puVar2;
  uint *puVar3;
  
  puVar1 = DAT_0800f468;
  if (*(char *)((int)param_1 + 6) == '\0') {
    puVar1 = (uint *)((uint)(byte)param_1[1] + (int)DAT_0800f468);
    *puVar1 = *puVar1 & ~*param_1;
    return;
  }
  *DAT_0800f468 = *DAT_0800f468 & ~*param_1;
  puVar1[1] = puVar1[1] & ~*param_1;
  puVar2 = (uint *)((uint)(byte)param_1[1] + (int)puVar1);
  *puVar2 = *puVar2 | *param_1;
  puVar2 = DAT_0800f468;
  puVar3 = DAT_0800f468 + 2;
  *puVar3 = *puVar3 & ~*param_1;
  puVar2 = puVar2 + 3;
  *puVar2 = *puVar2 & ~*param_1;
  if (*(byte *)((int)param_1 + 5) == 0x10) {
    *puVar3 = *puVar3 | *param_1;
    *puVar2 = *puVar2 | *param_1;
    return;
  }
  puVar1 = (uint *)((int)puVar1 + (uint)*(byte *)((int)param_1 + 5));
  *puVar1 = *puVar1 | *param_1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f46c at 0x0800f46c
// ---------------------------------------------------------------------------

void FUN_0800f46c(void)

{
  if (*(char *)(DAT_0800f47c + 2) == '\x01') {
    *(undefined1 *)(DAT_0800f47c + 2) = 0;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f480 at 0x0800f480
// ---------------------------------------------------------------------------

void FUN_0800f480(void)

{
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f482 at 0x0800f482
// ---------------------------------------------------------------------------

void FUN_0800f482(void)

{
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f484 at 0x0800f484
// ---------------------------------------------------------------------------

void FUN_0800f484(void)

{
  *DAT_0800f48c = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f490 at 0x0800f490
// ---------------------------------------------------------------------------

void FUN_0800f490(void)

{
  *DAT_0800f498 = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f49c at 0x0800f49c
// ---------------------------------------------------------------------------

void FUN_0800f49c(void)

{
  FUN_0800db18(0xf);
  *DAT_0800f4ac = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f4b0 at 0x0800f4b0
// ---------------------------------------------------------------------------

void FUN_0800f4b0(void)

{
  *DAT_0800f4b8 = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f4bc at 0x0800f4bc
// ---------------------------------------------------------------------------

void FUN_0800f4bc(void)

{
  *DAT_0800f4c4 = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f4c8 at 0x0800f4c8
// ---------------------------------------------------------------------------

void FUN_0800f4c8(void)

{
  *DAT_0800f4e0 = 0;
  FUN_0800db18(1);
  *(undefined4 *)(DAT_0800f4e4 + 0x14) = 0x1000;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f4e8 at 0x0800f4e8
// ---------------------------------------------------------------------------

void FUN_0800f4e8(uint param_1)

{
  *(uint *)(DAT_0800f4f4 + 0xc) = *(uint *)(DAT_0800f4f4 + 0xc) | param_1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f4f8 at 0x0800f4f8
// ---------------------------------------------------------------------------

void FUN_0800f4f8(void)

{
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f4fc at 0x0800f4fc
// ---------------------------------------------------------------------------

void FUN_0800f4fc(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  FUN_0800f4e8(0x7c);
  iVar2 = FUN_0800f5ec(0xb0000);
  iVar1 = DAT_0800f53c;
  if (iVar2 == 6) {
    *(uint *)(DAT_0800f53c + 0x10) = *(uint *)(DAT_0800f53c + 0x10) | 2;
    *(undefined4 *)(iVar1 + 0x14) = param_1;
    *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) | 0x40;
    FUN_0800f5ec(0xb0000);
    *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) & 0x3ffd;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f540 at 0x0800f540
// ---------------------------------------------------------------------------

undefined4 FUN_0800f540(void)

{
  undefined4 uVar1;
  
  uVar1 = 6;
  if ((*(uint *)(DAT_0800f578 + 0xc) & 1) != 0) {
    return 1;
  }
  if (*(int *)(DAT_0800f578 + 0xc) << 0x1d < 0) {
    return 3;
  }
  if (*(int *)(DAT_0800f578 + 0xc) << 0x1c < 0) {
    return 4;
  }
  if (*(int *)(DAT_0800f578 + 0xc) << 0x1b < 0) {
    uVar1 = 5;
  }
  else if (*(int *)(DAT_0800f578 + 0xc) << 0x19 < 0) {
    return 7;
  }
  return uVar1;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f57c at 0x0800f57c
// ---------------------------------------------------------------------------

void FUN_0800f57c(void)

{
  *(uint *)(DAT_0800f588 + 0x10) = *(uint *)(DAT_0800f588 + 0x10) | 0x80;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f58c at 0x0800f58c
// ---------------------------------------------------------------------------

int FUN_0800f58c(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  if (((uint)param_1 & 3) == 0) {
    FUN_0800f4e8(0x7c);
    iVar2 = FUN_0800f5ec(0x2000);
    iVar1 = DAT_0800f5d0;
    if (iVar2 == 6) {
      *(uint *)(DAT_0800f5d0 + 0x10) = *(uint *)(DAT_0800f5d0 + 0x10) | 1;
      *param_1 = param_2;
      iVar2 = FUN_0800f5ec(0x2000);
      *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) & 0x3ffe;
      return iVar2;
    }
  }
  else {
    iVar2 = 9;
  }
  return iVar2;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f5d4 at 0x0800f5d4
// ---------------------------------------------------------------------------

void FUN_0800f5d4(void)

{
  int iVar1;
  
  iVar1 = DAT_0800f5e4;
  *(undefined4 *)(DAT_0800f5e4 + 4) = DAT_0800f5e0;
  *(undefined4 *)(iVar1 + 4) = DAT_0800f5e8;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f5ec at 0x0800f5ec
// ---------------------------------------------------------------------------

int FUN_0800f5ec(void)

{
  int iVar1;
  int extraout_r3;
  int extraout_r3_00;
  int iVar2;
  
  iVar1 = FUN_0800f540();
  iVar2 = extraout_r3;
  while (iVar1 == 1) {
    if (iVar2 == 0) goto LAB_0800f606;
    iVar1 = FUN_0800f540();
    iVar2 = extraout_r3_00 + -1;
  }
  if (iVar2 == 0) {
LAB_0800f606:
    iVar1 = 10;
  }
  return iVar1;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f610 at 0x0800f610
// ---------------------------------------------------------------------------

void FUN_0800f610(undefined1 param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = DAT_0800f66c;
  iVar1 = DAT_0800f668;
  puVar3 = DAT_0800f66c + -1;
  switch(param_1) {
  case 0:
    *(undefined4 *)(DAT_0800f668 + 0x14) = 0x100;
    break;
  case 1:
    *(undefined4 *)(DAT_0800f668 + 0x10) = 0x100;
    break;
  case 2:
    *(undefined4 *)(DAT_0800f668 + 0x10) = 0x100;
    *(undefined4 *)(iVar1 + 0x10) = 0x200;
    goto LAB_0800f63a;
  case 3:
    *(undefined4 *)(DAT_0800f668 + 0x10) = 0x100;
    *(undefined4 *)(iVar1 + 0x10) = 0x200;
    *puVar3 = 0x100;
    goto LAB_0800f63c;
  case 4:
    *(undefined4 *)(DAT_0800f668 + 0x10) = 0x100;
    *(undefined4 *)(iVar1 + 0x10) = 0x200;
    *puVar3 = 0x100;
    *puVar3 = 0x200;
    goto LAB_0800f656;
  case 5:
    *(undefined4 *)(DAT_0800f668 + 0x10) = 0x100;
    *(undefined4 *)(iVar1 + 0x10) = 0x200;
    *puVar3 = 0x100;
    *puVar3 = 0x200;
    *puVar3 = 0x400;
    return;
  default:
    goto switchD_0800f628_default;
  }
  *(undefined4 *)(iVar1 + 0x14) = 0x200;
LAB_0800f63a:
  *puVar2 = 0x100;
LAB_0800f63c:
  *puVar2 = 0x200;
LAB_0800f656:
  *puVar2 = 0x400;
switchD_0800f628_default:
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f670 at 0x0800f670
// ---------------------------------------------------------------------------

void FUN_0800f670(void)

{
  char *pcVar1;
  byte *pbVar2;
  int iVar3;
  float *pfVar4;
  
  pcVar1 = DAT_0800f838;
  pfVar4 = DAT_0800f834;
  iVar3 = DAT_0800f830;
  pbVar2 = DAT_0800f82c;
  if (((DAT_0800f82c[0x1b] != 0) && (DAT_0800f82c[0x12] != 0)) ||
     (*(float *)(DAT_0800f830 + 0xc) < *DAT_0800f834)) {
    *(short *)(DAT_0800f838 + 0x42) = *(short *)(DAT_0800f838 + 0x42) + 1;
    if (9 < *(ushort *)(pcVar1 + 0x42)) {
      pcVar1[0x42] = '\0';
      pcVar1[0x43] = '\0';
      if (pbVar2[0x46] == 0) {
        FUN_08019844(0,0x20);
      }
      pbVar2[0x46] = 1;
    }
  }
  else {
    pcVar1[0x42] = '\0';
    pcVar1[0x43] = '\0';
    pbVar2[0x46] = 0;
  }
  if ((*(short *)(DAT_0800f83c + 0x1e) < 0x78) && (-0x28 < *(short *)(DAT_0800f83c + 0x22))) {
    pcVar1[0x44] = '\0';
    pcVar1[0x45] = '\0';
    pbVar2[0x47] = 0;
  }
  else {
    *(short *)(pcVar1 + 0x44) = *(short *)(pcVar1 + 0x44) + 1;
    if (9 < *(ushort *)(pcVar1 + 0x44)) {
      pcVar1[0x44] = '\0';
      pcVar1[0x45] = '\0';
      if (pbVar2[0x47] == 0) {
        FUN_08019844(0,0x22);
      }
      pbVar2[0x47] = 1;
    }
  }
  if ((*DAT_0800f840 == '\x01') && (*DAT_0800f844 != '\0')) {
    if ((((pbVar2[0x12] == 0) && (((*pbVar2 & 1) == 0 && (-1 < (int)((uint)pbVar2[0x39] << 0x1d)))))
        || (pbVar2[0x3a] == 0)) || (pbVar2[0x4b] != 0)) {
      pcVar1[0x3e] = '\0';
      pcVar1[0x3f] = '\0';
      pbVar2[0x44] = 0;
    }
    else {
      *(short *)(pcVar1 + 0x3e) = *(short *)(pcVar1 + 0x3e) + 1;
      if (*(ushort *)(pcVar1 + 0x30) <= *(ushort *)(pcVar1 + 0x3e)) {
        pcVar1[0x3e] = '\0';
        pcVar1[0x3f] = '\0';
        if (pbVar2[0x44] != 1) {
          FUN_08019844(0,0x1e);
        }
        pbVar2[0x44] = 1;
      }
    }
    if ((pbVar2[0x4c] == 0) && (pbVar2[0x3b] != 0)) {
      *(short *)(pcVar1 + 0x40) = *(short *)(pcVar1 + 0x40) + 1;
      if (*(ushort *)(pcVar1 + 0x30) <= *(ushort *)(pcVar1 + 0x40)) {
        pcVar1[0x40] = '\0';
        pcVar1[0x41] = '\0';
        if (pbVar2[0x45] != 1) {
          FUN_08019844(0,0x1f);
        }
        pbVar2[0x45] = 1;
      }
    }
    else {
      pcVar1[0x40] = '\0';
      pcVar1[0x41] = '\0';
      pbVar2[0x45] = 0;
    }
  }
  if ((*pcVar1 != '\0') || (*pfVar4 <= *(float *)(iVar3 + 0xc))) {
    if ((*pcVar1 == '\0') || (*(float *)(iVar3 + 0xc) < *pfVar4 + DAT_0800f84c)) {
      pcVar1[0x46] = '\0';
      pcVar1[0x47] = '\0';
      return;
    }
    if (9 < *(ushort *)(pcVar1 + 0x46)) {
      pcVar1[0x46] = '\0';
      pcVar1[0x47] = '\0';
      *pcVar1 = '\0';
      FUN_0800acd8();
      return;
    }
  }
  else if (*DAT_0800f848 <= *(ushort *)(pcVar1 + 0x46)) {
    pcVar1[0x46] = '\0';
    pcVar1[0x47] = '\0';
    *pcVar1 = '\x01';
    FUN_0800ac9c();
    return;
  }
  *(short *)(pcVar1 + 0x46) = *(short *)(pcVar1 + 0x46) + 1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f850 at 0x0800f850
// ---------------------------------------------------------------------------

undefined4 FUN_0800f850(uint param_1,int param_2,ushort param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  ushort local_28;
  
  iVar1 = DAT_0800f960;
  if (*DAT_0800f950 == '\x01') {
    if ((*DAT_0800f954 == 0x200) || (*DAT_0800f954 == 0x100)) {
      iVar2 = *DAT_0800f958;
    }
    else {
      iVar2 = DAT_0800f95c;
    }
    if ((0x17f < param_1) && (param_1 < 0x800)) {
      for (local_28 = 0; local_28 < 0x800; local_28 = local_28 + 1) {
        *(undefined1 *)(iVar1 + (uint)local_28) = *(undefined1 *)(iVar2 + (uint)local_28);
      }
      for (local_28 = 0; local_28 < param_3; local_28 = local_28 + 1) {
        *(undefined1 *)(iVar1 + param_1 + local_28) = *(undefined1 *)(param_2 + (uint)local_28);
      }
      FUN_0800f4f8();
      disableIRQinterrupts();
      FUN_0800f5d4();
      iVar3 = FUN_0800f4fc(iVar2);
      if (iVar3 == 6) {
        local_28 = 0;
        while( true ) {
          if (0x1ff < local_28) {
            FUN_0800f57c();
            enableIRQinterrupts();
            return 1;
          }
          disableIRQinterrupts();
          iVar3 = FUN_0800f58c(iVar2 + (uint)local_28 * 4,
                               *(undefined4 *)(iVar1 + (uint)local_28 * 4));
          if (iVar3 != 6) break;
          enableIRQinterrupts();
          local_28 = local_28 + 1;
        }
      }
      FUN_0800f57c();
      enableIRQinterrupts();
    }
  }
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800f964 at 0x0800f964
// ---------------------------------------------------------------------------

void FUN_0800f964(uint param_1,int param_2,ushort param_3)

{
  undefined1 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int local_28;
  ushort local_24;
  
  if ((*DAT_0800fa54 == 0x200) || (*DAT_0800fa54 == 0x100)) {
    local_28 = *DAT_0800fa58;
  }
  else {
    local_28 = DAT_0800fa5c;
  }
  if (param_1 < 0x180) {
    if ((0x9f < param_1) && (param_1 < 0xc0)) goto LAB_0800f99e;
  }
  else if (param_1 < 0x1c0) {
LAB_0800f99e:
    local_28 = local_28 + 0x800;
  }
  else {
    local_28 = (((local_28 + param_1) - 0x1c0 >> 0xb) + 2) * 0x800;
  }
  uVar2 = param_1 - 0x1c0 & 0x7ff;
  if (*DAT_0800fa54 == 0x200) {
    if (param_1 < 0x1c1) goto LAB_0800fa10;
    uVar3 = local_28 + uVar2 + (uint)param_3;
    uVar4 = DAT_0800fa60;
  }
  else if (*DAT_0800fa54 == 0x100) {
    if (param_1 < 0x1c1) goto LAB_0800fa10;
    uVar3 = local_28 + uVar2 + (uint)param_3;
    uVar4 = DAT_0800fa64;
  }
  else {
    if (param_1 < 0x1c1) goto LAB_0800fa10;
    uVar3 = local_28 + uVar2 + (uint)param_3;
    uVar4 = DAT_0800fa68;
  }
  if (uVar4 < uVar3) {
    return;
  }
LAB_0800fa10:
  for (local_24 = 0; local_24 < param_3; local_24 = local_24 + 1) {
    if (param_1 < 0x1c0) {
      uVar1 = *(undefined1 *)((param_1 & 0x7ff) + local_28 + (uint)local_24);
    }
    else {
      uVar1 = *(undefined1 *)(local_28 + uVar2 + (uint)local_24);
    }
    *(undefined1 *)(param_2 + (uint)local_24) = uVar1;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800fa6c at 0x0800fa6c
// ---------------------------------------------------------------------------

undefined4 FUN_0800fa6c(uint param_1,int param_2,ushort param_3)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  ushort local_40;
  int local_3c;
  short local_30;
  
  iVar1 = DAT_0800fc40;
  if ((*DAT_0800fc28 == 0x200) || (*DAT_0800fc28 == 0x100)) {
    local_3c = *DAT_0800fc2c;
  }
  else {
    local_3c = DAT_0800fc30;
  }
  if (param_1 < 0x180) {
    if ((0x9f < param_1) && (param_1 < 0xc0)) goto LAB_0800faae;
  }
  else if (param_1 < 0x1c0) {
LAB_0800faae:
    local_3c = local_3c + 0x800;
  }
  else {
    local_3c = (((local_3c + param_1) - 0x1c0 >> 0xb) + 2) * 0x800;
  }
  uVar3 = param_1 - 0x1c0 & 0x7ff;
  if (*DAT_0800fc28 == 0x200) {
    if (param_1 < 0x1c1) goto LAB_0800fb2a;
    uVar6 = local_3c + uVar3 + (uint)param_3;
    uVar7 = DAT_0800fc34;
  }
  else if (*DAT_0800fc28 == 0x100) {
    if (param_1 < 0x1c1) goto LAB_0800fb2a;
    uVar6 = local_3c + uVar3 + (uint)param_3;
    uVar7 = DAT_0800fc38;
  }
  else {
    if (param_1 < 0x1c1) goto LAB_0800fb2a;
    uVar6 = local_3c + uVar3 + (uint)param_3;
    uVar7 = DAT_0800fc3c;
  }
  if (uVar7 < uVar6) {
    return 0;
  }
LAB_0800fb2a:
  for (local_40 = 0; local_40 < 0x800; local_40 = local_40 + 1) {
    *(undefined1 *)(iVar1 + (uint)local_40) = *(undefined1 *)(local_3c + (uint)local_40);
  }
  for (local_40 = 0; local_40 < param_3; local_40 = local_40 + 1) {
    uVar7 = uVar3;
    if (param_1 < 0x1c0) {
      uVar7 = param_1 & 0x7ff;
    }
    *(undefined1 *)(iVar1 + uVar7 + local_40) = *(undefined1 *)(param_2 + (uint)local_40);
  }
  disableIRQinterrupts();
  FUN_0800f4f8();
  puVar2 = DAT_0800fc44;
  local_30 = 10;
  do {
    bVar8 = local_30 == 0;
    local_30 = local_30 + -1;
    if (bVar8) break;
    FUN_0800f5d4();
    *puVar2 = 0xaaaa;
    iVar5 = FUN_0800f4fc(local_3c);
  } while (iVar5 != 6);
  enableIRQinterrupts();
  local_40 = 0;
  do {
    if (0x1ff < local_40) {
      FUN_0800f57c();
      enableIRQinterrupts();
      return 1;
    }
    uVar4 = *(undefined4 *)(iVar1 + (uint)local_40 * 4);
    local_30 = 10;
    do {
      bVar8 = local_30 == 0;
      local_30 = local_30 + -1;
      if (bVar8) break;
      *puVar2 = 0xaaaa;
      disableIRQinterrupts();
      iVar5 = FUN_0800f58c(local_3c + (uint)local_40 * 4,uVar4);
      enableIRQinterrupts();
    } while (iVar5 != 6);
    local_40 = local_40 + 1;
  } while( true );
}



// ---------------------------------------------------------------------------
// Function: FUN_0800fc48 at 0x0800fc48
// ---------------------------------------------------------------------------

void FUN_0800fc48(void)

{
  byte bVar1;
  
  bVar1 = *(byte *)(DAT_0800fd30 + 0x14) >> 1;
  if (*(char *)(DAT_0800fd34 + 0x3a) == '\0') {
    if (bVar1 < 0xb) goto LAB_0800fc7c;
    if ((bVar1 < 0x15) && (10 < bVar1)) goto LAB_0800fc94;
    if ((bVar1 < 0x29) && (0x14 < bVar1)) goto LAB_0800fca8;
    if ((bVar1 < 0x3d) && (0x28 < bVar1)) goto LAB_0800fcbc;
    if ((bVar1 < 0x51) && (0x3c < bVar1)) goto LAB_0800fcd0;
    if (100 < bVar1) {
      return;
    }
    if (bVar1 < 0x51) {
      return;
    }
  }
  else {
    if (bVar1 < 0x15) {
LAB_0800fc7c:
      *DAT_0800fd38 = 1;
      return;
    }
    if ((bVar1 < 0x29) && (0x14 < bVar1)) {
LAB_0800fc94:
      *DAT_0800fd38 = 2;
      return;
    }
    if ((bVar1 < 0x3d) && (0x28 < bVar1)) {
LAB_0800fca8:
      *DAT_0800fd38 = 3;
      return;
    }
    if ((bVar1 < 0x51) && (0x3c < bVar1)) {
LAB_0800fcbc:
      *DAT_0800fd38 = 4;
      return;
    }
    if ((bVar1 < 100) && (0x50 < bVar1)) {
LAB_0800fcd0:
      *DAT_0800fd38 = 5;
      return;
    }
  }
  *DAT_0800fd38 = 6;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800fd3c at 0x0800fd3c
// ---------------------------------------------------------------------------

void FUN_0800fd3c(void)

{
  int iVar1;
  
  iVar1 = DAT_0800fd5c;
  if (*(char *)(DAT_0800fd5c + 0xf) == '\x01') {
    *(char *)(DAT_0800fd5c + 0x10) = *(char *)(DAT_0800fd5c + 0x10) + '\x01';
    if (0x31 < *(byte *)(iVar1 + 0x10)) {
      *(undefined1 *)(iVar1 + 0x10) = 0;
      *(undefined1 *)(iVar1 + 0xf) = 0;
      return;
    }
  }
  else {
    *(undefined1 *)(DAT_0800fd5c + 0x10) = 0;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800fd60 at 0x0800fd60
// ---------------------------------------------------------------------------

void FUN_0800fd60(void)

{
  int iVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  uint local_18;
  uint local_14;
  
  puVar2 = DAT_0800fefc;
  iVar1 = DAT_0800fef8;
  if (*DAT_0800fef4 != '\x01') {
    if (*(char *)(DAT_0800fef8 + 0x34) == '\0') {
      *DAT_0800fefc = 0;
    }
    else {
      *DAT_0800fefc = 1;
    }
    if (*(char *)(iVar1 + 0x2a) == '\0') {
      puVar2[2] = 0;
    }
    else {
      puVar2[2] = 1;
    }
    if ((*(char *)(iVar1 + 0x48) == '\0') && (*(char *)(iVar1 + 0x49) == '\0')) {
      puVar2[4] = 0;
    }
    else {
      puVar2[4] = 1;
    }
    if (*(char *)(iVar1 + 0x2f) == '\0') {
      puVar2[6] = 0;
    }
    else {
      puVar2[6] = 1;
    }
    if (*(char *)(iVar1 + 0x25) == '\0') {
      puVar2[8] = 0;
    }
    else {
      puVar2[8] = 1;
    }
    puVar3 = DAT_0800fefc;
    if ((DAT_0800fefc[-0x21] == '\0') && (DAT_0800fefc[-0x1f] == '\0')) {
      puVar2[10] = 0;
    }
    else {
      puVar2[10] = 1;
    }
    if ((puVar3[-0x20] == '\0') && (puVar3[-0x1e] == '\0')) {
      puVar2[0xc] = 0;
    }
    else {
      puVar2[0xc] = 1;
    }
    if ((*(char *)(iVar1 + 0x3a) == '\0') ||
       ((*(char *)(iVar1 + 0x2f) == '\0' && (*(char *)(iVar1 + 0x34) == '\0')))) {
      puVar2[0xe] = 0;
    }
    else {
      puVar2[0xe] = 1;
    }
    if (*(char *)(iVar1 + 0x48) == '\0') {
      puVar2[0x10] = 0;
    }
    else {
      puVar2[0x10] = 1;
    }
    if ((~*(byte *)(iVar1 + 7) & 0x11) == 0) {
      puVar2[0x12] = 1;
    }
    else {
      puVar2[0x12] = 0;
    }
    if ((~*(byte *)(iVar1 + 7) & 0x21) == 0) {
      puVar2[0x14] = 1;
    }
    else {
      puVar2[0x14] = 0;
    }
    if (puVar3[-0x1d] == '\0') {
      puVar2[0x16] = 0;
    }
    else {
      puVar2[0x16] = 1;
    }
    if (puVar3[-0x1c] == '\0') {
      puVar2[0x18] = 0;
    }
    else {
      puVar2[0x18] = 1;
    }
    if (puVar3[-0x1b] == '\0') {
      puVar2[0x1a] = 0;
    }
    else {
      puVar2[0x1a] = 1;
    }
    if ((*(byte *)(iVar1 + 0x39) & 1) == 0) {
      puVar2[0x1c] = 0;
    }
    else {
      puVar2[0x1c] = 1;
    }
    if (*(char *)(iVar1 + 0x11) == '\0') {
      puVar2[0x20] = 0;
    }
    else {
      puVar2[0x20] = 1;
    }
    if (*(char *)(iVar1 + 0x45) == '\0') {
      puVar2[0x22] = 0;
    }
    else {
      puVar2[0x22] = 1;
    }
    if (*(char *)(iVar1 + 0x44) == '\0') {
      puVar2[0x24] = 0;
    }
    else {
      puVar2[0x24] = 1;
    }
    if (*(char *)(iVar1 + 0x47) == '\0') {
      puVar2[0x26] = 0;
    }
    else {
      puVar2[0x26] = 1;
    }
    if (*(char *)(iVar1 + 0x46) == '\0') {
      puVar2[0x28] = 0;
    }
    else {
      puVar2[0x28] = 1;
    }
    if (puVar3[-0x1a] == '\0') {
      puVar2[0x2a] = 0;
    }
    else {
      puVar2[0x2a] = 1;
    }
    iVar1 = DAT_0800ff00;
    local_14 = 0;
    local_18 = 0;
    while( true ) {
      if (0x17 < (byte)local_18) break;
      if (puVar2[local_18 * 2] == '\x01') {
        *(undefined1 *)(iVar1 + local_14) = puVar2[local_18 * 2 + 1];
        local_14 = (uint)(byte)((char)local_14 + 1);
      }
      local_18 = (uint)(byte)((byte)local_18 + 1);
    }
    puVar3[-0x17] = (char)local_14;
    if (puVar3[-0x17] == '\0') {
      puVar3[-0x18] = 0;
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800ff04 at 0x0800ff04
// ---------------------------------------------------------------------------

void FUN_0800ff04(void)

{
  char *pcVar1;
  int iVar2;
  
  pcVar1 = DAT_0800ff48;
  if (*DAT_0800ff48 == '\0') {
    DAT_0800ff48[1] = '\0';
    return;
  }
  DAT_0800ff48[1] = DAT_0800ff48[1] + '\x01';
  if (5 < (byte)pcVar1[1]) {
    pcVar1[1] = '\0';
    *pcVar1 = '\0';
    FUN_08017a30();
    iVar2 = DAT_0800ff4c;
    *(undefined2 *)(DAT_0800ff4c + 8) = 5000;
    *(undefined2 *)(iVar2 + 0x20) = 5000;
    if (*DAT_0800ff50 == '\0') {
      *DAT_0800ff54 = 0;
      if (*DAT_0800ff58 == '\x01') {
        *DAT_0800ff58 = '\0';
      }
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800ff5c at 0x0800ff5c
// ---------------------------------------------------------------------------

void FUN_0800ff5c(void)

{
  int iVar1;
  char *pcVar2;
  
  pcVar2 = DAT_0800ffa4;
  iVar1 = DAT_0800ffa0;
  if (*(char *)(DAT_0800ffa0 + 0x4c) != DAT_0800ffa4[0xe]) {
    if ((DAT_0800ffa4[0xe] == '\0') && (*(char *)(DAT_0800ffa0 + 0x4c) == '\x01')) {
      *DAT_0800ffa4 = '\x01';
      pcVar2[1] = '\0';
    }
    pcVar2[0xe] = *(char *)(iVar1 + 0x4c);
  }
  if (*pcVar2 == '\0') {
    pcVar2[1] = '\0';
    return;
  }
  pcVar2[1] = pcVar2[1] + '\x01';
  if (5 < (byte)pcVar2[1]) {
    pcVar2[1] = '\0';
    *pcVar2 = '\0';
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0800ffa8 at 0x0800ffa8
// ---------------------------------------------------------------------------

void FUN_0800ffa8(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined1 local_3c;
  undefined1 local_3b;
  undefined1 local_3a;
  undefined2 local_38;
  undefined1 local_35;
  int iStack_34;
  int local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  
  local_44 = 0;
  local_48 = 0;
  if (param_1 == DAT_0801017c) {
    local_48 = 0;
  }
  else {
    if (param_1 == DAT_08010180) {
      local_48 = 1;
LAB_0800fff2:
      if (param_1 != DAT_08010188) goto LAB_0800fffe;
      local_48 = 3;
    }
    else {
      if (param_1 != DAT_08010184) goto LAB_0800fff2;
      local_48 = 2;
LAB_0800fffe:
      if (param_1 == DAT_0801018c) {
        local_48 = 4;
        goto LAB_08010010;
      }
    }
    if (param_1 == DAT_08010190) {
      local_48 = 5;
    }
  }
LAB_08010010:
  iStack_34 = param_1;
  local_30 = param_2;
  uStack_2c = param_3;
  uStack_28 = param_4;
  if (param_2 == 0x100) {
    FUN_08010194(local_48,8);
    local_44 = 0x100;
LAB_08010166:
    uVar1 = 0x17;
  }
  else if (param_2 < 0x101) {
    if (param_2 == 0x10) {
      FUN_08010194(local_48,4);
      local_44 = 0x10;
      uVar1 = 10;
    }
    else {
      if (0x10 < param_2) {
        if (param_2 == 0x20) {
          FUN_08010194(local_48,5);
          local_44 = 0x20;
        }
        else if (param_2 == 0x40) {
          FUN_08010194(local_48,6);
          local_44 = 0x40;
        }
        else {
          if (param_2 != 0x80) goto LAB_080100aa;
          FUN_08010194(local_48,7);
          local_44 = 0x80;
        }
        goto LAB_08010166;
      }
      if (param_2 == 1) {
        FUN_08010194(local_48,0);
        uVar1 = 6;
        local_44 = 1;
      }
      else if (param_2 == 2) {
        FUN_08010194(local_48,1);
        uVar1 = 7;
        local_44 = 2;
      }
      else if (param_2 == 4) {
        FUN_08010194(local_48,2);
        uVar1 = 8;
        local_44 = 4;
      }
      else {
        if (param_2 != 8) goto LAB_080100aa;
        FUN_08010194(local_48,3);
        local_44 = 8;
        uVar1 = 9;
      }
    }
  }
  else {
    uVar2 = 0x1000;
    if (param_2 == 0x1000) {
      uVar1 = 0xc;
    }
    else if (param_2 < 0x1001) {
      if (param_2 == 0x200) {
        FUN_08010194(local_48,9);
        local_44 = 0x200;
        goto LAB_08010166;
      }
      uVar2 = 0x400;
      if (param_2 == 0x400) {
        uVar1 = 10;
      }
      else {
        uVar2 = 0x800;
        if (param_2 != 0x800) goto LAB_080100aa;
        uVar1 = 0xb;
      }
    }
    else {
      uVar2 = 0x2000;
      if (param_2 == 0x2000) {
        uVar1 = 0xd;
      }
      else {
        uVar2 = 0x4000;
        if (param_2 == 0x4000) {
          uVar1 = 0xe;
        }
        else {
          uVar2 = 0x8000;
          if (param_2 != 0x8000) goto LAB_080100aa;
          uVar1 = 0xf;
        }
      }
    }
    FUN_08010194(local_48,uVar1);
    uVar1 = 0x28;
    local_44 = uVar2;
  }
  FUN_08022f20(uVar1);
LAB_080100aa:
  local_38 = (undefined2)local_30;
  local_35 = (undefined1)param_3;
  FUN_0801031c(param_1,&local_38);
  local_3c = 0;
  local_40 = local_44;
  local_3b = (undefined1)param_4;
  local_3a = 1;
  FUN_0800f3fc(&local_40);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08010194 at 0x08010194
// ---------------------------------------------------------------------------

void FUN_08010194(int param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = DAT_080101ac + (param_2 & 0xfffffffc);
  *(uint *)(iVar1 + 8) = *(uint *)(iVar1 + 8) | param_1 << ((param_2 & 3) << 2);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080101b0 at 0x080101b0
// ---------------------------------------------------------------------------

void FUN_080101b0(uint param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  iVar1 = DAT_080102c4;
  if ((int)param_1 < 0) {
    uVar2 = *(uint *)(DAT_080102c4 + 0x1c);
  }
  else if ((int)(param_1 << 1) < 0) {
    uVar2 = *(uint *)(DAT_080102c4 + 0x20);
  }
  else if ((int)(param_1 << 2) < 0) {
    uVar2 = *(uint *)(DAT_080102c4 + 0x24);
  }
  else if ((int)(param_1 << 3) < 0) {
    uVar2 = *(uint *)(DAT_080102c4 + 0x28);
  }
  else {
    uVar2 = *(uint *)(DAT_080102c4 + 4);
  }
  iVar4 = ((param_1 & 0x3fffff) >> 0x15) << 4;
  uVar3 = (param_1 & 0xffff) << iVar4;
  if ((param_1 & DAT_080102c8) == 0x300000) {
    uVar2 = uVar2 & 0xf0ffffff;
    uVar5 = *(uint *)(DAT_080102c4 + 4) & 0xf0ffffff;
LAB_08010274:
    *(uint *)(DAT_080102c4 + 4) = uVar5;
LAB_0801029a:
    if (param_2 == 0) goto LAB_0801029e;
  }
  else {
    if ((int)(param_1 << 0xb) < 0) {
      uVar5 = 3 << ((param_1 & 0xfffff) >> 0x10);
      if ((int)(param_1 << 10) < 0) {
        uVar5 = uVar5 << 0x10;
      }
LAB_08010290:
      uVar2 = uVar2 & ~uVar5;
      if ((param_1 & 0x70000000) == 0) {
        uVar2 = uVar2 | 0xf000000;
      }
      goto LAB_0801029a;
    }
    if ((int)(param_1 << 7) < 0) {
      if ((int)(param_1 << 0x1d) < 0) {
        uVar2 = uVar2 & ~uVar3;
        if (-1 < (int)(param_1 << 6)) {
          uVar5 = *(uint *)(DAT_080102c4 + 4) & 0xfffffffe;
LAB_08010270:
          uVar5 = uVar5 | 0xf000000;
          goto LAB_08010274;
        }
      }
      else {
        uVar2 = uVar2 & ~((param_1 & 0xffff | 4) << iVar4);
      }
      if (param_2 == 0) {
        uVar3 = *(uint *)(DAT_080102c4 + 4) & 0xfffffffe;
LAB_08010286:
        *(uint *)(DAT_080102c4 + 4) = uVar3 | 0xf000000;
        goto LAB_0801029e;
      }
      uVar5 = *(uint *)(DAT_080102c4 + 4) | 1;
    }
    else {
      uVar5 = uVar3;
      if (-1 < (int)(param_1 << 5)) goto LAB_08010290;
      if ((int)(param_1 << 0x1c) < 0) {
        uVar2 = uVar2 & ~uVar3;
        if (-1 < (int)(param_1 << 6)) {
          uVar5 = *(uint *)(DAT_080102c4 + 4) & 0xfffffff7;
          goto LAB_08010270;
        }
      }
      else {
        uVar2 = uVar2 & ~((param_1 & 0xffff | 8) << iVar4);
      }
      if (param_2 == 0) {
        uVar3 = *(uint *)(DAT_080102c4 + 4) & 0xfffffff7;
        goto LAB_08010286;
      }
      uVar5 = *(uint *)(DAT_080102c4 + 4) | 8;
    }
    *(uint *)(DAT_080102c4 + 4) = uVar5 | 0xf000000;
  }
  uVar2 = uVar2 | uVar3;
LAB_0801029e:
  if ((int)param_1 < 0) {
    *(uint *)(iVar1 + 0x1c) = uVar2;
    return;
  }
  if ((int)(param_1 << 1) < 0) {
    *(uint *)(iVar1 + 0x20) = uVar2;
    return;
  }
  if ((int)(param_1 << 2) < 0) {
    *(uint *)(iVar1 + 0x24) = uVar2;
    return;
  }
  if ((int)(param_1 << 3) < 0) {
    *(uint *)(iVar1 + 0x28) = uVar2;
    return;
  }
  *(uint *)(iVar1 + 4) = uVar2;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080102cc at 0x080102cc
// ---------------------------------------------------------------------------

void FUN_080102cc(undefined4 param_1,uint param_2)

{
  uint *puVar1;
  undefined2 local_10;
  undefined1 local_d;
  undefined4 uStack_c;
  uint local_8;
  
  local_10 = (undefined2)param_2;
  local_d = 4;
  uStack_c = param_1;
  local_8 = param_2;
  FUN_0801031c(param_1,&local_10);
  puVar1 = DAT_08010318;
  *DAT_08010318 = *DAT_08010318 & ~local_8;
  *puVar1 = *puVar1 & ~local_8;
  puVar1 = DAT_08010318;
  DAT_08010318[2] = DAT_08010318[2] & ~local_8;
  puVar1[3] = puVar1[3] & ~local_8;
  DAT_08010318[5] = DAT_08010318[5] | local_8;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801031c at 0x0801031c
// ---------------------------------------------------------------------------

void FUN_0801031c(uint *param_1,ushort *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = 0;
  uVar1 = *(byte *)((int)param_2 + 3) & 0xf;
  if ((int)((uint)*(byte *)((int)param_2 + 3) << 0x1b) < 0) {
    uVar1 = uVar1 | (byte)param_2[1];
  }
  if ((char)*param_2 != '\0') {
    uVar2 = *param_1;
    do {
      uVar4 = 1 << (uVar3 & 0xff);
      if ((*param_2 & uVar4) == uVar4) {
        uVar2 = uVar1 << (uVar3 << 2 & 0xff) | uVar2 & ~(0xf << (uVar3 << 2 & 0xff));
        if (*(char *)((int)param_2 + 3) == '(') {
          param_1[5] = uVar4;
        }
        else if (*(char *)((int)param_2 + 3) == 'H') {
          param_1[4] = uVar4;
        }
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < 8);
    *param_1 = uVar2;
  }
  if (0xff < *param_2) {
    uVar3 = param_1[1];
    uVar2 = 0;
    do {
      uVar4 = 1 << (uVar2 + 8 & 0xff);
      if ((*param_2 & uVar4) == uVar4) {
        uVar3 = uVar3 & ~(0xf << (uVar2 << 2 & 0xff)) | uVar1 << (uVar2 << 2 & 0xff);
        if (*(char *)((int)param_2 + 3) == '(') {
          param_1[5] = uVar4;
        }
        if (*(char *)((int)param_2 + 3) == 'H') {
          param_1[4] = uVar4;
        }
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < 8);
    param_1[1] = uVar3;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080103be at 0x080103be
// ---------------------------------------------------------------------------

undefined4 FUN_080103be(void)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  char acStack_2c [32];
  byte bStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0x28e;
  if ((*DAT_080109c0 == 0x200) || (*DAT_080109c0 == 0x100)) {
    iVar3 = *DAT_080109c4;
  }
  else {
    iVar3 = DAT_080109c8;
  }
  for (bStack_c = 0; bStack_c < 5; bStack_c = bStack_c + 1) {
    acStack_2c[bStack_c] = *(char *)(iVar3 + 0x28e + (uint)bStack_c);
  }
  cVar1 = FUN_08016658(acStack_2c,4);
  if (cVar1 == acStack_2c[4]) {
    uVar2 = CONCAT31(CONCAT21(CONCAT11(acStack_2c[0],acStack_2c[1]),acStack_2c[2]),acStack_2c[3]);
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



// ---------------------------------------------------------------------------
// Function: FUN_080103c8 at 0x080103c8
// ---------------------------------------------------------------------------

float FUN_080103c8(byte param_1,int param_2,int param_3)

{
  float fVar1;
  byte bVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  uint local_40;
  byte local_3c;
  
  local_3c = 0;
  if (param_3 < 0) {
    param_2 = param_3;
  }
  if (100 < param_1) {
    local_40 = 0;
    goto LAB_08010546;
  }
  if (param_1 < 0x5f) {
    if (0x59 < param_1) {
      local_40 = 2;
      goto LAB_08010546;
    }
    if (param_1 < 0x55) {
      if (0x4f < param_1) {
        local_40 = 4;
        goto LAB_08010546;
      }
      if (0x4a < param_1) {
        local_40 = 5;
        goto LAB_08010546;
      }
      if (0x45 < param_1) {
        local_40 = 6;
        goto LAB_08010546;
      }
      if (param_1 < 0x41) {
        if (0x3b < param_1) {
          local_40 = 8;
          goto LAB_08010546;
        }
        if (0x36 < param_1) {
          local_40 = 9;
          goto LAB_08010546;
        }
        if (param_1 < 0x32) {
          if (param_1 < 0x2d) {
            if (0x27 < param_1) {
              local_40 = 0xc;
              goto LAB_08010546;
            }
            if (param_1 < 0x23) {
              if (param_1 < 0x1e) {
                if (param_1 < 0x19) {
                  if (param_1 < 0x14) {
                    if (param_1 < 0xf) {
                      if (param_1 < 10) {
                        if (param_1 < 5) {
                          bVar2 = 0x14;
                        }
                        else {
                          bVar2 = 0x13;
                        }
                      }
                      else {
                        bVar2 = 0x12;
                      }
                    }
                    else {
                      bVar2 = 0x11;
                    }
                  }
                  else {
                    bVar2 = 0x10;
                  }
                }
                else {
                  bVar2 = 0xf;
                }
              }
              else {
                bVar2 = 0xe;
              }
            }
            else {
              bVar2 = 0xd;
            }
          }
          else {
            bVar2 = 0xb;
          }
        }
        else {
          bVar2 = 10;
        }
      }
      else {
        bVar2 = 7;
      }
    }
    else {
      bVar2 = 3;
    }
  }
  else {
    bVar2 = 1;
  }
  local_40 = (uint)bVar2;
LAB_08010546:
  if (param_2 < 0x33) {
    if (param_2 < 0x2e) {
      if (param_2 < 0x2c) {
        if (param_2 < 0x28) {
          if (param_2 < 0x23) {
            if (param_2 < 0x1e) {
              if (param_2 < 0x19) {
                if (param_2 < 0x14) {
                  if (param_2 < 0xf) {
                    if (param_2 < 10) {
                      if (param_2 < 5) {
                        if (-1 < param_2) {
                          local_3c = 1;
                        }
                      }
                      else {
                        local_3c = 2;
                      }
                    }
                    else {
                      local_3c = 3;
                    }
                  }
                  else {
                    local_3c = 4;
                  }
                }
                else {
                  local_3c = 5;
                }
              }
              else {
                local_3c = 6;
              }
            }
            else {
              local_3c = 7;
            }
          }
          else {
            local_3c = 8;
          }
        }
        else {
          local_3c = 9;
        }
      }
      else {
        local_3c = 10;
      }
    }
    else {
      local_3c = 0xb;
    }
  }
  else {
    local_3c = 0xc;
  }
  uVar3 = FUN_08008548(*(undefined1 *)(local_40 * 0xd + DAT_0801063c + (uint)local_3c));
  uVar3 = FUN_08008364((int)uVar3,(int)((ulonglong)uVar3 >> 0x20),(int)DAT_08010640,
                       (int)((ulonglong)DAT_08010640 >> 0x20));
  uVar4 = FUN_080085d2(*DAT_08010648 / DAT_0801064c);
  FUN_08008364((int)uVar4,(int)((ulonglong)uVar4 >> 0x20),(int)uVar3,(int)((ulonglong)uVar3 >> 0x20)
              );
  fVar1 = (float)FUN_08008658();
  if (*(float *)(DAT_08010650 + 8) - 1.0 < fVar1) {
    fVar1 = *(float *)(DAT_08010650 + 8) - 1.0;
  }
  return fVar1;
}



// ---------------------------------------------------------------------------
// Function: FUN_08010654 at 0x08010654
// ---------------------------------------------------------------------------

byte FUN_08010654(void)

{
  short sVar1;
  byte bVar2;
  uint in_fpscr;
  undefined4 uVar3;
  float fVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  byte bVar7;
  undefined1 uVar8;
  byte local_34;
  
  uVar8 = 0;
  if (*(char *)(DAT_08010904 + 0xf) == '\x01') {
    return 1;
  }
  bVar2 = *(byte *)(DAT_08010908 + 5) >> 1;
  if (*(short *)(DAT_0801090c + 0x22) < 0) {
    sVar1 = *(short *)(DAT_0801090c + 0x22);
  }
  else {
    sVar1 = *(short *)(DAT_0801090c + 0x1e);
  }
  if (bVar2 < 100) {
    if (bVar2 < 0x5f) {
      if (bVar2 < 0x5a) {
        if (bVar2 < 0x55) {
          if (bVar2 < 0x50) {
            if (bVar2 < 0x4b) {
              if (bVar2 < 0x46) {
                if (bVar2 < 0x41) {
                  if (bVar2 < 0x3c) {
                    if (bVar2 < 0x37) {
                      if (bVar2 < 0x32) {
                        if (bVar2 < 0x2d) {
                          if (bVar2 < 0x28) {
                            if (bVar2 < 0x23) {
                              if (bVar2 < 0x1e) {
                                if (bVar2 < 0x19) {
                                  if (bVar2 < 0x14) {
                                    if (bVar2 < 0xf) {
                                      if (bVar2 < 10) {
                                        if (bVar2 < 5) {
                                          bVar7 = 0x14;
                                        }
                                        else {
                                          bVar7 = 0x13;
                                        }
                                      }
                                      else {
                                        bVar7 = 0x12;
                                      }
                                    }
                                    else {
                                      bVar7 = 0x11;
                                    }
                                  }
                                  else {
                                    bVar7 = 0x10;
                                  }
                                }
                                else {
                                  bVar7 = 0xf;
                                }
                              }
                              else {
                                bVar7 = 0xe;
                              }
                            }
                            else {
                              bVar7 = 0xd;
                            }
                          }
                          else {
                            bVar7 = 0xc;
                          }
                        }
                        else {
                          bVar7 = 0xb;
                        }
                      }
                      else {
                        bVar7 = 10;
                      }
                    }
                    else {
                      bVar7 = 9;
                    }
                  }
                  else {
                    bVar7 = 8;
                  }
                }
                else {
                  bVar7 = 7;
                }
              }
              else {
                bVar7 = 6;
              }
            }
            else {
              bVar7 = 5;
            }
          }
          else {
            bVar7 = 4;
          }
        }
        else {
          bVar7 = 3;
        }
      }
      else {
        bVar7 = 2;
      }
    }
    else {
      bVar7 = 1;
    }
  }
  else {
    bVar7 = 0;
  }
  if (sVar1 < 0x3c) {
    if (sVar1 < 0x37) {
      if (sVar1 < 0x32) {
        if (sVar1 < 0x2d) {
          if (sVar1 < 0x28) {
            if (sVar1 < 0x19) {
              if (sVar1 < 0xf) {
                if (sVar1 < 10) {
                  if (sVar1 < 0) {
                    if (sVar1 < -10) {
                      if (sVar1 < -0x14) {
                        local_34 = 0;
                      }
                      else {
                        local_34 = 1;
                      }
                    }
                    else {
                      local_34 = 2;
                    }
                  }
                  else {
                    local_34 = 3;
                  }
                }
                else {
                  local_34 = 4;
                }
              }
              else {
                local_34 = 5;
              }
            }
            else {
              local_34 = 6;
            }
          }
          else {
            local_34 = 7;
          }
        }
        else {
          local_34 = 8;
        }
      }
      else {
        local_34 = 9;
      }
    }
    else {
      local_34 = 10;
    }
  }
  else {
    local_34 = 0xb;
  }
  uVar5 = FUN_08008548(*(undefined1 *)(DAT_08010904 + 0x26 + (uint)bVar7 * 0xc + (uint)local_34));
  uVar5 = FUN_08008364((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),(int)DAT_08010910,
                       (int)((ulonglong)DAT_08010910 >> 0x20),bVar2,bVar7,uVar8);
  uVar6 = FUN_080085d2(*DAT_08010908 / DAT_08010918);
  FUN_08008364((int)uVar6,(int)((ulonglong)uVar6 >> 0x20),(int)uVar5,(int)((ulonglong)uVar5 >> 0x20)
              );
  bVar2 = FUN_080085a0();
  fVar4 = (float)VectorUnsignedToFloat((uint)bVar2,(byte)(in_fpscr >> 0x16) & 3);
  if (*(float *)(DAT_0801091c + 4) - 1.0 < fVar4) {
    uVar3 = VectorFloatToUnsigned(*(float *)(DAT_0801091c + 4) - 1.0,3);
    bVar2 = (byte)uVar3;
  }
  return bVar2;
}



// ---------------------------------------------------------------------------
// Function: FUN_08010920 at 0x08010920
// ---------------------------------------------------------------------------

undefined4 FUN_08010920(void)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  char local_2c [32];
  byte local_c;
  undefined4 local_8;
  
  local_8 = 0x293;
  if ((*DAT_080109c0 == 0x200) || (*DAT_080109c0 == 0x100)) {
    iVar3 = *DAT_080109c4;
  }
  else {
    iVar3 = DAT_080109c8;
  }
  for (local_c = 0; local_c < 5; local_c = local_c + 1) {
    local_2c[local_c] = *(char *)(iVar3 + 0x293 + (uint)local_c);
  }
  cVar1 = FUN_08016658(local_2c,4);
  if (cVar1 == local_2c[4]) {
    uVar2 = CONCAT31(CONCAT21(CONCAT11(local_2c[0],local_2c[1]),local_2c[2]),local_2c[3]);
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



// ---------------------------------------------------------------------------
// Function: FUN_080109cc at 0x080109cc
// ---------------------------------------------------------------------------

void FUN_080109cc(void)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  int iVar5;
  int iVar6;
  char cVar7;
  undefined1 uVar8;
  uint in_fpscr;
  float fVar9;
  undefined4 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined1 uVar13;
  
  iVar3 = DAT_08010de0;
  iVar2 = DAT_08010ddc;
  pcVar1 = DAT_08010dd8;
  uVar13 = 0;
  if (*DAT_08010dd8 == '\0') {
    if (*(int *)(DAT_08010ddc + 0xc) < DAT_08010de8) {
      DAT_08010dd8[0xf] = '\0';
    }
    else {
      DAT_08010dd8[0xf] = DAT_08010dd8[0xf] + '\x01';
      if (4 < (byte)pcVar1[0xf]) {
        pcVar1[0xf] = '\0';
        *pcVar1 = '\x01';
      }
    }
    pcVar1[0x10] = '\0';
  }
  else {
    if (*(int *)(DAT_08010de0 + 0xc) < DAT_08010de4) {
      DAT_08010dd8[0x10] = DAT_08010dd8[0x10] + '\x01';
      if (4 < (byte)pcVar1[0x10]) {
        pcVar1[0x10] = '\0';
        *pcVar1 = '\0';
      }
    }
    else {
      DAT_08010dd8[0x10] = '\0';
    }
    pcVar1[0xf] = '\0';
  }
  iVar5 = DAT_08010df0;
  puVar4 = DAT_08010dec;
  uVar8 = pcVar1[1] == '\0';
  cVar7 = '\x01';
  if ((bool)uVar8) {
    uVar11 = FUN_08008548(*DAT_08010dec);
    uVar11 = FUN_08008364((int)uVar11,(int)((ulonglong)uVar11 >> 0x20),(int)DAT_08010dfc,
                          (int)((ulonglong)DAT_08010dfc >> 0x20));
    uVar12 = FUN_080085d2(*(undefined4 *)(iVar5 + 0x114));
    FUN_08008628((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),(int)uVar11,
                 (int)((ulonglong)uVar11 >> 0x20));
    if ((bool)cVar7 && !(bool)uVar8) {
      pcVar1[0x11] = '\0';
    }
    else {
      pcVar1[0x11] = pcVar1[0x11] + '\x01';
      if (4 < (byte)pcVar1[0x11]) {
        pcVar1[0x11] = '\0';
        pcVar1[1] = '\x01';
      }
    }
    pcVar1[0x12] = '\0';
  }
  else {
    uVar11 = FUN_08008548(*DAT_08010dec);
    uVar11 = FUN_08008364((int)uVar11,(int)((ulonglong)uVar11 >> 0x20),(int)DAT_08010df4,
                          (int)((ulonglong)DAT_08010df4 >> 0x20),uVar13);
    uVar12 = FUN_080085d2(*(undefined4 *)(iVar5 + 0x114));
    FUN_080085f8((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),(int)uVar11,
                 (int)((ulonglong)uVar11 >> 0x20));
    if (cVar7 == '\0') {
      pcVar1[0x12] = pcVar1[0x12] + '\x01';
      if (4 < (byte)pcVar1[0x12]) {
        pcVar1[0x12] = '\0';
        pcVar1[1] = '\0';
      }
    }
    else {
      pcVar1[0x12] = '\0';
    }
    pcVar1[0x11] = '\0';
  }
  if (pcVar1[2] == '\0') {
    if (DAT_08010e08 < *(int *)(iVar3 + 0xc)) {
      pcVar1[0x13] = '\0';
    }
    else {
      pcVar1[0x13] = pcVar1[0x13] + '\x01';
      if (4 < (byte)pcVar1[0x13]) {
        pcVar1[0x13] = '\0';
        pcVar1[2] = '\x01';
      }
    }
    pcVar1[0x14] = '\0';
  }
  else {
    if (DAT_08010e04 < *(int *)(iVar3 + 0xc)) {
      pcVar1[0x14] = pcVar1[0x14] + '\x01';
      if (4 < (byte)pcVar1[0x14]) {
        pcVar1[0x14] = '\0';
        pcVar1[2] = '\0';
      }
    }
    else {
      pcVar1[0x14] = '\0';
    }
    pcVar1[0x13] = '\0';
  }
  uVar13 = pcVar1[3] == '\0';
  cVar7 = '\x01';
  if ((bool)uVar13) {
    uVar11 = FUN_08008548(*puVar4);
    uVar11 = FUN_08008364((int)uVar11,(int)((ulonglong)uVar11 >> 0x20),(int)DAT_08010e14,
                          (int)((ulonglong)DAT_08010e14 >> 0x20));
    uVar12 = FUN_080085d2(*(undefined4 *)(iVar5 + 0x114));
    FUN_080085f8((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),(int)uVar11,
                 (int)((ulonglong)uVar11 >> 0x20));
    if ((bool)cVar7 && !(bool)uVar13) {
      pcVar1[0x15] = '\0';
    }
    else {
      pcVar1[0x15] = pcVar1[0x15] + '\x01';
      if (4 < (byte)pcVar1[0x15]) {
        pcVar1[0x15] = '\0';
        pcVar1[3] = '\x01';
      }
    }
    pcVar1[0x16] = '\0';
  }
  else {
    uVar11 = FUN_08008548(*puVar4);
    uVar11 = FUN_08008364((int)uVar11,(int)((ulonglong)uVar11 >> 0x20),(int)DAT_08010e0c,
                          (int)((ulonglong)DAT_08010e0c >> 0x20));
    uVar12 = FUN_080085d2(*(undefined4 *)(iVar5 + 0x114));
    FUN_08008628((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),(int)uVar11,
                 (int)((ulonglong)uVar11 >> 0x20));
    if (cVar7 == '\0') {
      pcVar1[0x16] = pcVar1[0x16] + '\x01';
      if (4 < (byte)pcVar1[0x16]) {
        pcVar1[0x16] = '\0';
        pcVar1[3] = '\0';
      }
    }
    else {
      pcVar1[0x16] = '\0';
    }
    pcVar1[0x15] = '\0';
  }
  iVar6 = DAT_08010e20;
  iVar5 = DAT_08010e1c;
  if (((*(char *)(DAT_08010e1c + 0x3a) == '\0') && (*DAT_08010e24 == '\0')) &&
     (*DAT_08010e28 == '\0')) {
    if (pcVar1[6] == '\0') {
      if (*(short *)(DAT_08010e20 + 0x1e) < 0x3c) {
        pcVar1[0x1b] = '\0';
      }
      else {
        pcVar1[0x1b] = pcVar1[0x1b] + '\x01';
        if (5 < (byte)pcVar1[0x1b]) {
          pcVar1[0x1b] = '\0';
          pcVar1[6] = '\x01';
        }
      }
      pcVar1[0x1c] = '\0';
    }
    else {
      if (*(short *)(DAT_08010e20 + 0x1e) < 0x34) {
        pcVar1[0x1c] = pcVar1[0x1c] + '\x01';
        if (5 < (byte)pcVar1[0x1c]) {
          pcVar1[0x1c] = pcVar1[0x1c] + '\x01';
          pcVar1[6] = '\0';
        }
      }
      else {
        pcVar1[0x1c] = '\0';
      }
      pcVar1[0x1b] = '\0';
    }
    if (pcVar1[7] == '\0') {
      if (*(short *)(iVar6 + 0x22) < -0xe) {
        pcVar1[0x1d] = pcVar1[0x1d] + '\x01';
        if (5 < (byte)pcVar1[0x1d]) {
          pcVar1[0x1d] = '\0';
          pcVar1[7] = '\x01';
        }
      }
      else {
        pcVar1[0x1d] = '\0';
      }
      pcVar1[0x1e] = '\0';
    }
    else {
      if (*(short *)(iVar6 + 0x22) < -9) {
        pcVar1[0x1e] = '\0';
      }
      else {
        pcVar1[0x1e] = pcVar1[0x1e] + '\x01';
        if (5 < (byte)pcVar1[0x1e]) {
          pcVar1[0x1e] = '\0';
          pcVar1[7] = '\0';
        }
      }
      pcVar1[0x1d] = '\0';
    }
    pcVar1[4] = '\0';
    pcVar1[5] = '\0';
    pcVar1[0x17] = '\0';
    pcVar1[0x18] = '\0';
    pcVar1[0x19] = '\0';
    pcVar1[0x1a] = '\0';
  }
  else {
    if (pcVar1[4] == '\0') {
      if (*(short *)(DAT_08010e20 + 0x1e) < 0x35) {
        pcVar1[0x17] = '\0';
      }
      else {
        pcVar1[0x17] = pcVar1[0x17] + '\x01';
        if (4 < (byte)pcVar1[0x17]) {
          pcVar1[0x17] = '\0';
          pcVar1[4] = '\x01';
        }
      }
      pcVar1[0x18] = '\0';
    }
    else {
      if (*(short *)(DAT_08010e20 + 0x1e) < 0x33) {
        pcVar1[0x18] = pcVar1[0x18] + '\x01';
        if (4 < (byte)pcVar1[0x18]) {
          pcVar1[0x18] = '\0';
          pcVar1[4] = '\0';
        }
      }
      else {
        pcVar1[0x18] = '\0';
      }
      pcVar1[0x17] = '\0';
    }
    if (pcVar1[5] == '\0') {
      if (*(short *)(iVar6 + 0x22) < 3) {
        pcVar1[0x19] = pcVar1[0x19] + '\x01';
        if (4 < (byte)pcVar1[0x19]) {
          pcVar1[0x19] = '\0';
          pcVar1[5] = '\x01';
        }
      }
      else {
        pcVar1[0x19] = '\0';
      }
      pcVar1[0x1a] = '\0';
    }
    else {
      if (*(short *)(iVar6 + 0x22) < 6) {
        pcVar1[0x1a] = '\0';
      }
      else {
        pcVar1[0x1a] = pcVar1[0x1a] + '\x01';
        if (4 < (byte)pcVar1[0x1a]) {
          pcVar1[0x1a] = '\0';
          pcVar1[5] = '\0';
        }
      }
      pcVar1[0x19] = '\0';
    }
    pcVar1[6] = '\0';
    pcVar1[7] = '\0';
    pcVar1[0x1b] = '\0';
    pcVar1[0x1c] = '\0';
    pcVar1[0x1d] = '\0';
    pcVar1[0x1e] = '\0';
  }
  fVar9 = *(float *)(iVar2 + 0xc) - *(float *)(iVar3 + 0xc);
  if (pcVar1[8] == '\0') {
    if ((int)fVar9 < 0x3f000000) {
      pcVar1[0x1f] = '\0';
    }
    else {
      pcVar1[0x1f] = pcVar1[0x1f] + '\x01';
      if (5 < (byte)pcVar1[0x1f]) {
        pcVar1[0x1f] = '\0';
        pcVar1[8] = '\x01';
      }
    }
    pcVar1[0x20] = '\0';
  }
  else {
    if ((int)fVar9 < 0x3f000000) {
      pcVar1[0x20] = pcVar1[0x20] + '\x01';
      if (5 < (byte)pcVar1[0x20]) {
        pcVar1[0x20] = '\0';
        pcVar1[8] = '\0';
      }
    }
    else {
      pcVar1[0x20] = '\0';
    }
    pcVar1[0x1f] = '\0';
  }
  if ((int)*(short *)(iVar6 + 0x1e) - (int)*(short *)(iVar6 + 0x22) < 0x10) {
    pcVar1[9] = '\0';
  }
  else {
    pcVar1[9] = '\x01';
  }
  if (DAT_08010e2c[1] != 0.0) {
    fVar9 = (float)VectorUnsignedToFloat(DAT_08010e2c[1],(byte)(in_fpscr >> 0x16) & 3);
    uVar10 = VectorFloatToUnsigned(*DAT_08010e2c / fVar9,3);
    if (0x3b < (byte)uVar10) {
      pcVar1[10] = '\0';
      goto LAB_08010d7e;
    }
  }
  pcVar1[10] = '\x01';
LAB_08010d7e:
  if (pcVar1[0xb] == '\0') {
    if (DAT_08010e30 < *(int *)(iVar3 + 0xc)) {
      pcVar1[0x21] = '\0';
    }
    else {
      pcVar1[0x21] = pcVar1[0x21] + '\x01';
      if (5 < (byte)pcVar1[0x21]) {
        pcVar1[0x21] = '\0';
        pcVar1[0xb] = '\x01';
        if (*(char *)(iVar5 + 0x4d) != '\0') {
          FUN_0800ac9c();
        }
        *DAT_08010e34 = 0;
        *DAT_08010eb8 = 0;
      }
    }
    pcVar1[0x22] = '\0';
  }
  else {
    if (DAT_08010e30 < *(int *)(iVar3 + 0xc)) {
      pcVar1[0x22] = pcVar1[0x22] + '\x01';
      if (5 < (byte)pcVar1[0x22]) {
        pcVar1[0x22] = '\0';
        pcVar1[0xb] = '\0';
      }
    }
    else {
      pcVar1[0x22] = '\0';
    }
    pcVar1[0x21] = '\0';
  }
  if (pcVar1[0xc] == '\0') {
    if (*(short *)(iVar6 + 0x40) < 0x5a) {
      pcVar1[0x23] = '\0';
    }
    else {
      pcVar1[0x23] = pcVar1[0x23] + '\x01';
      if (5 < (byte)pcVar1[0x23]) {
        pcVar1[0x23] = '\0';
        pcVar1[0xc] = '\x01';
      }
    }
    pcVar1[0x24] = '\0';
  }
  else {
    if (*(short *)(iVar6 + 0x40) < 0x4b) {
      pcVar1[0x24] = pcVar1[0x24] + '\x01';
      if ((byte)pcVar1[0x24] < 5) {
        pcVar1[0x24] = '\0';
        pcVar1[0xc] = '\0';
      }
    }
    else {
      pcVar1[0x24] = '\0';
    }
    pcVar1[0x23] = '\0';
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08010ebc at 0x08010ebc
// ---------------------------------------------------------------------------

undefined4 FUN_08010ebc(void)

{
  return DAT_08010ec0;
}



// ---------------------------------------------------------------------------
// Function: FUN_08010ec4 at 0x08010ec4
// ---------------------------------------------------------------------------

undefined4 FUN_08010ec4(void)

{
  return DAT_08010ec8;
}



// ---------------------------------------------------------------------------
// Function: FUN_08010ecc at 0x08010ecc
// ---------------------------------------------------------------------------

undefined4 FUN_08010ecc(void)

{
  return DAT_08010ed0;
}



// ---------------------------------------------------------------------------
// Function: FUN_08010ed4 at 0x08010ed4
// ---------------------------------------------------------------------------

undefined4 FUN_08010ed4(void)

{
  return DAT_08010ed8;
}



// ---------------------------------------------------------------------------
// Function: FUN_08010edc at 0x08010edc
// ---------------------------------------------------------------------------

undefined1 FUN_08010edc(void)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = DAT_08010f0c;
  if (*(char *)(DAT_08010f0c + 0xe) == '\0') {
    return 0;
  }
  uVar1 = *(undefined1 *)(DAT_08010f10 + (uint)*(byte *)(DAT_08010f0c + 0xd));
  *(char *)(DAT_08010f0c + 0xd) = *(char *)(DAT_08010f0c + 0xd) + '\x01';
  if (*(byte *)(iVar2 + 0xe) <= *(byte *)(iVar2 + 0xd)) {
    *(undefined1 *)(iVar2 + 0xd) = 0;
  }
  return uVar1;
}



// ---------------------------------------------------------------------------
// Function: FUN_08010f14 at 0x08010f14
// ---------------------------------------------------------------------------

void FUN_08010f14(void)

{
  int iVar1;
  
  if ((*(char *)(DAT_08010f30 + 0x3a) == '\0') && (*(char *)(DAT_08010f30 + 0x3b) == '\0')) {
    iVar1 = *(int *)(DAT_08010f34 + 0x18) + 1;
  }
  else {
    iVar1 = 0;
  }
  *(int *)(DAT_08010f34 + 0x18) = iVar1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08010f38 at 0x08010f38
// ---------------------------------------------------------------------------

void FUN_08010f38(void)

{
  int iVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  char *pcVar6;
  int iVar7;
  char cVar8;
  undefined4 uVar9;
  
  FUN_08009024();
  FUN_0800c78c();
  FUN_0800b050();
  FUN_0800963c();
  if (*DAT_08011254 != '\0') {
    return;
  }
  FUN_08011a60();
  iVar7 = DAT_08011270;
  pcVar6 = DAT_0801126c;
  puVar5 = DAT_08011268;
  puVar4 = DAT_08011264;
  puVar3 = DAT_08011260;
  puVar2 = DAT_0801125c;
  iVar1 = DAT_08011258;
  if (((*(char *)(DAT_08011258 + 1) == '\0') && (*(char *)(DAT_08011258 + 2) == '\0')) &&
     (*DAT_08011274 == '\0')) {
    *(undefined1 *)(DAT_08011258 + 5) = 0;
    *(undefined1 *)(iVar1 + 6) = 0;
    *DAT_08011280 = 0;
    *DAT_08011284 = 0;
    *DAT_08011288 = 0;
    uVar9 = DAT_0801128c;
    *DAT_08011290 = DAT_0801128c;
    *DAT_08011294 = uVar9;
    *DAT_08011298 = 0;
    *(undefined1 *)(iVar1 + 7) = 0;
    *(undefined1 *)(iVar1 + 8) = 0;
    if (*(char *)(iVar1 + 3) == '\0') {
      *pcVar6 = '\0';
      *puVar5 = 1;
      FUN_0800ac9c();
      FUN_0800c8f4();
      *(undefined1 *)(iVar1 + 0x38) = 0;
      *(undefined1 *)(iVar1 + 0x39) = 0;
      *puVar3 = 0;
      *puVar2 = 0;
      *(undefined1 *)(iVar1 + 10) = 0;
      *(undefined1 *)(iVar1 + 0x25) = 0;
      *(undefined1 *)(iVar1 + 0x26) = 0;
      *puVar4 = 0;
      *DAT_0801127c = 0;
      *(undefined1 *)(iVar1 + 0xc) = 0xff;
      *(undefined1 *)(iVar1 + 0xd) = 0xff;
      *(undefined1 *)(iVar1 + 0x27) = 0;
      *(undefined1 *)(iVar1 + 0x28) = 0;
      *DAT_0801129c = 0;
      *DAT_080112a0 = 0;
      return;
    }
    *(undefined1 *)(iVar1 + 10) = 0;
    *puVar4 = 0;
    if (*(char *)(iVar7 + 0x4d) != '\0') {
      FUN_0800ac9c();
    }
    *puVar2 = 0;
    *(undefined1 *)(iVar1 + 0x39) = 0;
    if (*(byte *)(iVar1 + 0x29) < 10) {
      *(char *)(iVar1 + 0x29) = *(char *)(iVar1 + 0x29) + '\x01';
    }
    else {
      *puVar3 = 1;
      *(undefined1 *)(iVar1 + 0x38) = 1;
      if (*(char *)(iVar7 + 0x4c) == '\0') {
        FUN_0800c940();
      }
    }
    *(undefined1 *)(iVar1 + 0xc) = 0xff;
    *(undefined1 *)(iVar1 + 0xd) = 0xff;
    return;
  }
  if (*DAT_0801126c == '\0') {
    if (*DAT_08011278 == '\0') {
      *(char *)(DAT_08011258 + 0x24) = *(char *)(DAT_08011258 + 0x24) + '\x01';
      if (*(byte *)(iVar1 + 0x24) < 6) {
        return;
      }
      *(undefined1 *)(iVar1 + 0x24) = 0;
      FUN_0801ca08();
      goto LAB_08011192;
    }
    FUN_0801ca08();
    cVar8 = FUN_0800c108();
    if ((cVar8 == '\0') || (cVar8 == '\x01')) {
      *(char *)(iVar1 + 6) = *(char *)(iVar1 + 6) + '\x01';
      if (*(byte *)(iVar1 + 6) < 0x14) goto LAB_08011192;
      *(undefined1 *)(iVar1 + 5) = 0;
      *(undefined1 *)(iVar1 + 6) = 0;
      cVar8 = '\x14';
    }
    else {
      if (cVar8 == '\x02') {
        *puVar2 = 0;
        *(undefined1 *)(iVar1 + 0x39) = 0;
        if (*(char *)(iVar7 + 0x4d) != '\0') {
          FUN_0800ac9c();
        }
        *puVar3 = 0;
        *(undefined1 *)(iVar1 + 0x38) = 0;
        if (*(char *)(iVar7 + 0x4c) != '\0') {
          FUN_0800c8f4();
        }
        goto LAB_08011192;
      }
      *(char *)(iVar1 + 6) = *(char *)(iVar1 + 6) + '\x01';
      if (*(byte *)(iVar1 + 6) < 0x14) goto LAB_08011192;
      *(undefined1 *)(iVar1 + 5) = 0;
      *(undefined1 *)(iVar1 + 6) = 0;
    }
    *pcVar6 = cVar8;
LAB_0801110a:
    FUN_0800c108();
  }
  else {
    *(char *)(DAT_08011258 + 0x24) = *(char *)(DAT_08011258 + 0x24) + '\x01';
    if (*(byte *)(iVar1 + 0x24) < 2) {
      return;
    }
    *(undefined1 *)(iVar1 + 0x24) = 0;
    if (*pcVar6 == '\x14') {
      cVar8 = *(char *)(iVar1 + 5);
      if (cVar8 == '\0') {
        if (0xe < *(byte *)(iVar1 + 6)) {
LAB_08011110:
          *(undefined1 *)(iVar1 + 6) = 0;
          *(undefined1 *)(iVar1 + 5) = 1;
          goto LAB_08011192;
        }
        *(char *)(iVar1 + 6) = *(char *)(iVar1 + 6) + '\x01';
        FUN_08011868(0x47,0);
        goto LAB_0801110a;
      }
      if (cVar8 != '\x01') {
        if (cVar8 != '\x02') goto LAB_08011192;
        *(undefined1 *)(iVar1 + 6) = 0;
        if (*(byte *)(iVar1 + 7) < 0xc) {
          *(char *)(iVar1 + 7) = *(char *)(iVar1 + 7) + '\x01';
          FUN_08011868(0x48,*(undefined1 *)(iVar1 + 0xc),*(undefined1 *)(iVar1 + 0xd));
          *(undefined1 *)(iVar1 + 0x25) = 0;
          *(undefined1 *)(iVar1 + 0x26) = 0;
          goto LAB_08011192;
        }
        *(undefined1 *)(iVar1 + 7) = 0;
        *(undefined1 *)(iVar1 + 5) = 1;
        *(undefined1 *)(iVar1 + 0x25) = 1;
        *(undefined1 *)(iVar1 + 0x26) = 0;
        *puVar4 = 0;
        uVar9 = 0xb5;
LAB_0801118c:
        FUN_08019844(0,uVar9);
        goto LAB_08011192;
      }
      if (*(char *)(iVar1 + 9) != '\0') goto LAB_08011192;
      if (((*(char *)(iVar1 + 0x25) != '\x01') &&
          (FUN_0800c614(), *(char *)(iVar1 + 0x10) == '\x01')) &&
         ((*(char *)(iVar7 + 0x4c) == '\0' &&
          (*(undefined1 *)(iVar1 + 0x10) = 0, (*(byte *)(iVar7 + 0x39) & 3) == 0)))) {
        FUN_0801789c();
      }
      FUN_08011868(0x47,*(undefined1 *)(iVar1 + 0xc),*(undefined1 *)(iVar1 + 0xd));
    }
    else {
      if (*pcVar6 != '\x1d') goto LAB_08011192;
      cVar8 = *(char *)(iVar1 + 5);
      if (cVar8 == '\0') {
        if (0xe < *(byte *)(iVar1 + 6)) goto LAB_08011110;
        *(char *)(iVar1 + 6) = *(char *)(iVar1 + 6) + '\x01';
        FUN_0801f044(199);
        goto LAB_0801110a;
      }
      if (cVar8 != '\x01') {
        if (cVar8 != '\x02') goto LAB_08011192;
        if (*(byte *)(iVar1 + 8) < 10) {
          *(char *)(iVar1 + 8) = *(char *)(iVar1 + 8) + '\x01';
          *(undefined1 *)(iVar1 + 0x27) = 0;
          *(undefined1 *)(iVar1 + 0x28) = 0;
          goto LAB_08011192;
        }
        *(undefined1 *)(iVar1 + 8) = 0;
        *(undefined1 *)(iVar1 + 5) = 1;
        *(undefined1 *)(iVar1 + 0x27) = 1;
        *(undefined1 *)(iVar1 + 0x28) = 0;
        if (-1 < (int)((uint)*DAT_0801127c << 0x1e)) goto LAB_08011192;
        *DAT_0801127c = 0;
        uVar9 = 0xb7;
        goto LAB_0801118c;
      }
      if (*(char *)(iVar1 + 0x27) == '\0') {
        *puVar5 = 1;
        FUN_0800c614();
        if (((*(char *)(iVar1 + 0x10) == '\x01') && (*(char *)(iVar7 + 0x4c) == '\0')) &&
           (*(undefined1 *)(iVar1 + 0x10) = 0, (*(byte *)(iVar7 + 0x39) & 3) == 0)) {
          FUN_0801789c();
        }
      }
      FUN_0801f044(199);
    }
    cVar8 = FUN_0800c108();
    if ((cVar8 != '\0') && (cVar8 != '\x01')) {
      *pcVar6 = '\0';
    }
  }
LAB_08011192:
  *(undefined1 *)(iVar1 + 0x29) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080112a4 at 0x080112a4
// ---------------------------------------------------------------------------

undefined4 FUN_080112a4(void)

{
  float fVar1;
  undefined4 uVar2;
  
  if (*DAT_080112dc == '\0') {
    fVar1 = *(float *)(DAT_080112e4 + 0xc);
  }
  else {
    fVar1 = *(float *)(DAT_080112e0 + 0x114);
  }
  uVar2 = VectorFloatToUnsigned(fVar1 * DAT_080112e8,3);
  return uVar2;
}



// ---------------------------------------------------------------------------
// Function: FUN_080112ec at 0x080112ec
// ---------------------------------------------------------------------------

undefined4 FUN_080112ec(void)

{
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_080112f0 at 0x080112f0
// ---------------------------------------------------------------------------

undefined4 FUN_080112f0(void)

{
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_080112f4 at 0x080112f4
// ---------------------------------------------------------------------------

undefined4 FUN_080112f4(void)

{
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_080112f8 at 0x080112f8
// ---------------------------------------------------------------------------

undefined4 FUN_080112f8(void)

{
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_080112fc at 0x080112fc
// ---------------------------------------------------------------------------

/* WARNING: Removing unreachable block (ram,0x08017aca) */

void FUN_080112fc(void)

{
  uint *puVar1;
  
  puVar1 = DAT_08017ae4;
  *DAT_08017ae4 = *DAT_08017ae4 & 0xfffffffc;
  puVar1[2] = puVar1[2] | 1;
  puVar1 = DAT_08017ae8;
  *DAT_08017ae8 = *DAT_08017ae8 | 4;
  *DAT_08017aec = 0;
  WaitForInterrupt();
  *puVar1 = *puVar1 & 0xfffffffb;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08011458 at 0x08011458
// ---------------------------------------------------------------------------

void FUN_08011458(void)

{
  *DAT_08011460 = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08011464 at 0x08011464
// ---------------------------------------------------------------------------

void FUN_08011464(void)

{
  *DAT_0801146c = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: HardFault_Handler at 0x08011470
// ---------------------------------------------------------------------------

void HardFault_Handler(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ---------------------------------------------------------------------------
// Function: FUN_08011474 at 0x08011474
// ---------------------------------------------------------------------------

void FUN_08011474(void)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  float fVar3;
  undefined1 *puVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  char cVar8;
  byte bVar9;
  uint in_r3;
  uint in_fpscr;
  float fVar10;
  uint uVar11;
  
  puVar2 = DAT_08011844;
  puVar1 = DAT_0801182c;
  if ((*(int *)(DAT_0801182c + 0x20) == 0) && (*(int *)(DAT_0801182c + 0x24) == 0)) {
    return;
  }
  if (((*DAT_08011830 == '\0') && (*DAT_08011834 == '\0')) && (*DAT_08011838 == '\0')) {
    *(undefined4 *)(DAT_0801182c + 0x20) = 0;
    goto LAB_08011824;
  }
  if ((*DAT_0801183c == '\0') && (*DAT_08011840 != '\0')) {
    if (*(int *)(DAT_0801182c + 0x20) == 0x101) {
      cVar8 = '\x1d';
    }
    else {
      if ((*(int *)(DAT_0801182c + 0x20) != 0x102) && (*(int *)(DAT_0801182c + 0x24) != 0x103))
      goto LAB_080117d2;
      cVar8 = '\x14';
    }
    *DAT_0801183c = cVar8;
  }
  else if (*DAT_0801183c == '\x14') {
    if (*(int *)(DAT_0801182c + 0x20) == 0x102) {
      if (DAT_0801182c[0x30] == -0x39) {
        *DAT_08011844 = 2;
        bVar9 = puVar1[9] | 1;
LAB_0801151a:
        puVar1[9] = bVar9;
      }
      else if (DAT_0801182c[0x30] == -0x38) {
        *DAT_08011848 = 0;
        bVar9 = puVar1[9] | 2;
        goto LAB_0801151a;
      }
      if ((puVar1[0x31] & 1) == 0) {
        puVar1[3] = 0;
      }
      else {
        puVar1[3] = 1;
      }
      if ((int)((uint)(byte)puVar1[0x31] << 0x1e) < 0) {
        puVar1[2] = 1;
      }
      else {
        puVar1[2] = 0;
      }
      if ((int)((uint)(byte)puVar1[0x31] << 0x1d) < 0) {
        *puVar1 = 1;
      }
      else {
        *puVar1 = 0;
      }
      if ((int)((uint)(byte)puVar1[0x31] << 0x1c) < 0) {
        puVar1[1] = 1;
      }
      else {
        puVar1[1] = 0;
      }
      if ((int)((uint)(byte)puVar1[0x31] << 0x1b) < 0) {
        puVar1[4] = 1;
      }
      else {
        puVar1[4] = 0;
      }
      if ((int)((uint)(byte)puVar1[0x31] << 0x1a) < 0) {
        puVar1[5] = 1;
      }
      else {
        puVar1[5] = 0;
      }
      puVar1[0xe] = (char)(((byte)puVar1[0x32] & 0xf) >> 2);
      if ((int)((uint)(byte)puVar1[0x32] << 0x18) < 0) {
        puVar1[7] = 1;
      }
      else {
        puVar1[7] = 0;
      }
      if ((int)((uint)(byte)puVar1[0x32] << 0x19) < 0) {
        puVar1[8] = 1;
      }
      else {
        puVar1[8] = 0;
      }
      puVar1[6] = puVar1[0x33];
      *(uint *)(puVar1 + 0x18) = (byte)puVar1[0x34] - 0x28;
      *(uint *)(puVar1 + 0x1c) = (byte)puVar1[0x35] - 0x28;
    }
    if (*(int *)(puVar1 + 0x24) == 0x103) {
      if (-1 < (int)((uint)(byte)puVar1[9] << 0x1d)) {
        puVar1[9] = puVar1[9] | 4;
        FUN_08019844(0,0xb4,puVar2,0x103,0,in_r3 & 0xffffff00);
      }
      fVar3 = DAT_0801184c;
      puVar2 = DAT_0801182c;
      fVar10 = (float)VectorUnsignedToFloat
                                (*(undefined4 *)(DAT_0801182c + 0x38),(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(puVar1 + 0x10) = fVar10 / DAT_0801184c;
      fVar10 = (float)VectorSignedToFloat(*(int *)(puVar2 + 0x3c),(byte)(in_fpscr >> 0x16) & 3);
      if (fVar10 < 0.0) {
        fVar10 = (float)VectorSignedToFloat(~(*(int *)(puVar2 + 0x3c) - 1U),
                                            (byte)((in_fpscr & 0xfffffff) >> 0x16) & 3);
      }
      *(float *)(puVar1 + 0x14) = fVar10 / fVar3;
    }
  }
  else if ((*DAT_0801183c == '\x1d') && (*(int *)(DAT_0801182c + 0x20) == 0x101)) {
    if (DAT_0801182c[0x30] == 'G') {
      *DAT_08011850 = 0;
      puVar1[10] = puVar1[10] | 1;
      uVar7 = 199;
    }
    else {
      if (DAT_0801182c[0x30] != 'H') goto LAB_080117d2;
      *DAT_08011850 = 0;
      *DAT_08011854 = 0;
      *puVar2 = 2;
      if (-1 < (int)((uint)(byte)puVar1[10] << 0x1e)) {
        puVar1[10] = puVar1[10] | 2;
        FUN_08019844(0,0xb6,puVar2,0x48,0,in_r3 & 0xffffff00);
      }
      if ((puVar1[0x31] & 1) == 0) {
        puVar1[0xb] = 0;
      }
      else {
        puVar1[0xb] = 1;
      }
      if ((int)((uint)(byte)puVar1[0x31] << 0x1e) < 0) {
        puVar1[0xc] = 1;
      }
      else {
        puVar1[0xc] = 0;
      }
      if ((int)((uint)(byte)puVar1[0x31] << 0x1e) < 0) {
        puVar1[0xd] = 1;
      }
      else {
        puVar1[0xd] = 0;
      }
      puVar1[6] = puVar1[0x35];
      iVar6 = DAT_08011864;
      iVar5 = DAT_08011860;
      puVar4 = DAT_0801185c;
      puVar2 = DAT_08011858;
      switch(puVar1[0x33]) {
      case 0:
        if (*(char *)(DAT_08011864 + 0x4c) != '\0') {
          FUN_0800c8f4();
        }
        *puVar2 = 0;
      case 4:
        if (*(char *)(iVar6 + 0x4d) != '\0') {
          FUN_0800ac9c();
        }
        *puVar4 = 0;
        break;
      case 1:
        if ((puVar1[0x34] == -0x7b) && (*(char *)(DAT_08011864 + 0x3a) == '\0')) {
          if ((*(byte *)(DAT_08011864 + 0x1b) & 1) != 0) {
            *(undefined1 *)(DAT_08011864 + 0x1c) = 0;
            *(undefined2 *)(iVar5 + 0x12) = 0;
            *(undefined1 *)(iVar6 + 0x1e) = 0;
            *(byte *)(iVar6 + 0x1b) = *(byte *)(iVar6 + 0x1b) & 0xfe;
          }
          if ((int)((uint)*(byte *)(iVar6 + 0x1b) << 0x1e) < 0) {
            *(undefined1 *)(iVar6 + 0x21) = 0;
            *(undefined2 *)(iVar5 + 0x24) = 0;
            *(undefined1 *)(iVar6 + 0x23) = 0;
            *(byte *)(iVar6 + 0x1b) = *(byte *)(iVar6 + 0x1b) & 0xfd;
          }
        }
        *puVar2 = 1;
        if (*(char *)(iVar6 + 0x4c) == '\0') {
          FUN_0800c940();
        }
        break;
      case 3:
        *DAT_08011858 = 1;
        if (*(char *)(iVar6 + 0x4c) == '\0') {
          FUN_0800c940();
        }
      case 2:
        *puVar4 = 1;
        if (*(char *)(iVar6 + 0x4d) == '\0') {
          FUN_0800acd8();
        }
        break;
      case 5:
        if (*(char *)(DAT_08011864 + 0x4c) != '\0') {
          FUN_0800c8f4();
        }
        *puVar2 = 0;
        break;
      case 6:
        if (*(char *)(DAT_08011864 + 0x4d) != '\0') {
          FUN_0800ac9c();
        }
        *puVar4 = 0;
        if ((*(byte *)(iVar6 + 0x1b) & 1) != 0) {
          *(undefined1 *)(iVar6 + 0x1c) = 0;
          *(undefined2 *)(iVar5 + 0x12) = 0;
          *(undefined1 *)(iVar6 + 0x1e) = 0;
          *(byte *)(iVar6 + 0x1b) = *(byte *)(iVar6 + 0x1b) & 0xfe;
        }
        if ((int)((uint)*(byte *)(iVar6 + 0x1b) << 0x1e) < 0) {
          *(undefined1 *)(iVar6 + 0x21) = 0;
          *(undefined2 *)(iVar5 + 0x24) = 0;
          *(undefined1 *)(iVar6 + 0x23) = 0;
          *(byte *)(iVar6 + 0x1b) = *(byte *)(iVar6 + 0x1b) & 0xfd;
        }
        if (*(char *)(iVar6 + 0x4c) == '\0') {
          FUN_0800c940();
        }
        *puVar2 = 1;
      }
      uVar7 = 200;
    }
    FUN_0801f044(uVar7);
  }
LAB_080117d2:
  puVar2 = DAT_0801182c;
  if (*(int *)(puVar1 + 0x20) != 0) {
    for (uVar11 = 0; (byte)uVar11 < 8; uVar11 = (uint)(byte)((byte)uVar11 + 1)) {
      puVar2[uVar11 + 0x30] = 0;
    }
    *(undefined4 *)(puVar1 + 0x20) = 0;
  }
  puVar2 = DAT_0801182c;
  if (*(int *)(puVar1 + 0x24) == 0) {
    return;
  }
  for (uVar11 = 0; (byte)uVar11 < 8; uVar11 = (uint)(byte)((byte)uVar11 + 1)) {
    puVar2[uVar11 + 0x38] = 0;
  }
LAB_08011824:
  *(undefined4 *)(puVar1 + 0x24) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08011868 at 0x08011868
// ---------------------------------------------------------------------------

void FUN_08011868(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  int iVar2;
  byte *pbVar3;
  char *pcVar4;
  byte bVar5;
  
  puVar1 = DAT_08011a14;
  *DAT_08011a14 = param_1;
  pcVar4 = DAT_08011a28;
  pbVar3 = DAT_08011a20;
  iVar2 = DAT_08011a18;
  bVar5 = *(char *)(DAT_08011a18 + 0x4d) != '\0';
  if (*(char *)(DAT_08011a18 + 0x4c) != '\0') {
    bVar5 = bVar5 | 2;
  }
  if ((*DAT_08011a1c != '\0') && (*DAT_08011a20 == 0)) {
    bVar5 = bVar5 | 4;
  }
  if (((*DAT_08011a24 != '\0') && (*DAT_08011a2c != '\x11')) && (*DAT_08011a28 == '\0')) {
    bVar5 = bVar5 | 8;
  }
  if ((*DAT_08011a30 != '\0') || (*(char *)(DAT_08011a18 + 0x44) != '\0')) {
    bVar5 = bVar5 | 0x10;
  }
  if ((*DAT_08011a34 != '\0') || (*(char *)(DAT_08011a18 + 0x45) != '\0')) {
    bVar5 = bVar5 | 0x20;
  }
  puVar1[1] = bVar5;
  bVar5 = *DAT_08011a38 != '\0';
  if (*DAT_08011a3c != '\0') {
    bVar5 = bVar5 | 2;
  }
  if (*(char *)(iVar2 + 0x3a) != '\0') {
    bVar5 = bVar5 | 4;
  }
  if (*(char *)(iVar2 + 0x3b) != '\0') {
    bVar5 = bVar5 | 8;
  }
  if ((*(byte *)(iVar2 + 0x12) & 0x13) != 0) {
    bVar5 = bVar5 | 0x80;
  }
  if ((*(byte *)(iVar2 + 0x1b) & 3) != 0) {
    bVar5 = bVar5 | 0x40;
  }
  if (*DAT_08011a40 != '\0') {
    bVar5 = bVar5 | 0x20;
  }
  if (*DAT_08011a44 != '\0') {
    bVar5 = bVar5 | 0x10;
  }
  puVar1[2] = bVar5;
  puVar1[3] = param_2;
  puVar1[4] = param_3;
  puVar1[5] = *(byte *)(DAT_08011a48 + 0x14) >> 1;
  puVar1[6] = *DAT_08011a4c << 6 | *DAT_08011a50 << 4 | *DAT_08011a54 < 2 | *pcVar4 == '\0' |
              *pbVar3;
  puVar1[7] = *DAT_08011a58 | *DAT_08011a5c << 4;
  FUN_0800a670(DAT_08011a14,8,0x101,0,4);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08011a60 at 0x08011a60
// ---------------------------------------------------------------------------

void FUN_08011a60(void)

{
  byte bVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  byte *pbVar6;
  undefined1 *puVar7;
  int iVar8;
  undefined1 uVar9;
  undefined1 *puVar10;
  undefined1 *puVar11;
  bool bVar12;
  
  puVar11 = DAT_0801215c;
  puVar7 = DAT_08011e84;
  pbVar6 = DAT_08011e80;
  pcVar5 = DAT_08011e7c;
  pcVar4 = DAT_08011e78;
  pcVar3 = DAT_08011e70;
  pcVar2 = DAT_08011e6c;
  if (*DAT_08011e60 != '\0') {
    return;
  }
  if (*DAT_08011e64 < 7) {
    return;
  }
  puVar10 = (undefined1 *)0x2;
  uVar9 = 2;
  bVar12 = *DAT_08011e68 == '\x14';
  do {
    if (!bVar12) goto LAB_08011eb2;
    bVar12 = DAT_08011e84[2] == '\0';
  } while (((!bVar12) || (bVar12 = *DAT_08011e74 == '\0', !bVar12)) ||
          (bVar12 = DAT_08011e84[5] == '\x02', !bVar12));
  if (DAT_08011e84[9] == '\x05') {
LAB_08011eb2:
    if (*DAT_08011e68 != '\x14') {
      return;
    }
    if ((DAT_0801215c[2] == '\0') && (*DAT_08011e74 == '\0')) {
      return;
    }
    if (DAT_0801215c[5] != '\x02') {
      return;
    }
    if (DAT_0801215c[9] == '\x05') {
      return;
    }
    if (DAT_0801215c[0x2a] == '\0') {
      DAT_0801215c[0x2a] = 1;
      puVar11[10] = 0;
      *pcVar4 = '\0';
      puVar11[0x2e] = 0;
      puVar11[0x2b] = 0;
      puVar11[0x2f] = 0;
    }
    pcVar4 = DAT_08012160;
    if (((puVar11[0xf] != '\0') || (puVar11[0xe] != '\0')) || (pbVar6[0x45] != 0)) {
      puVar11[0xc] = 0;
      puVar11[0xd] = 0x80;
      goto LAB_08011f10;
    }
    if ((*pcVar2 != '\0') || (*pcVar3 != '\0')) {
      puVar11[0x38] = 0;
      puVar11[0x39] = 0;
      if (pbVar6[0x4d] != 0) {
        FUN_0800ac9c();
      }
      if (pbVar6[0x4c] != 0) {
        FUN_0800c8f4();
      }
      puVar11[0xc] = 3;
      puVar11[0xd] = 0x81;
      goto LAB_08011b34;
    }
    if (puVar11[10] != '\0') {
      if (puVar11[10] == '\x01') {
        if (puVar11[0x2e] == '\0') {
          puVar11[0x39] = 0;
          FUN_0800ac9c();
          puVar11[0xc] = 4;
          puVar11[0xd] = 0x82;
          pcVar2 = DAT_08012170;
          if (*DAT_08012170 == '\0') {
            puVar11[0x38] = 1;
            FUN_0800c940();
            puVar11[0xc] = 0;
            puVar11[0xd] = 0x83;
            if ((*pcVar2 == '\0') && (*DAT_08012174 == '\0')) {
              puVar11[0x2e] = 1;
            }
          }
        }
        else if (puVar11[0x2e] == '\x01') {
          FUN_0800c614();
          puVar11[0xc] = 0;
          puVar11[0xd] = 0x84;
          if (*pcVar5 == '\x01') {
            *pcVar5 = '\x02';
          }
        }
        if ((((-1 < (int)((uint)pbVar6[0x39] << 0x1d)) && ((pbVar6[0x12] & 0x13) == 0)) &&
            ((*pbVar6 & 1) == 0)) && ((-1 < (int)((uint)pbVar6[0x51] << 0x1d) && (*pcVar4 == '\0')))
           ) {
          bVar12 = *DAT_08012164 == '\0';
          uVar9 = 2;
          goto LAB_0801209e;
        }
      }
      else {
        if (puVar11[10] != '\x02') {
          return;
        }
        if (puVar11[0x2e] == '\0') {
          puVar11[0x39] = 0;
          FUN_0800ac9c();
          puVar11[0xc] = 4;
          puVar11[0xd] = 0x85;
          puVar10 = puVar11;
          if ((pbVar6[0x4d] == 0) && (*DAT_08012170 == '\0')) {
            puVar11[0xc] = 6;
            puVar11[0xd] = 0x86;
            if (*DAT_08012174 != '\0') {
              puVar11[0x38] = 0;
              puVar10 = puVar11 + 0x2e;
              FUN_0800c8f4();
              *puVar10 = 1;
            }
          }
        }
        else if (puVar11[0x2e] == '\x01') {
          puVar11[0xc] = 3;
          puVar11[0xd] = 0x87;
          if (*pcVar5 == '\x01') {
            *pcVar5 = '\x02';
          }
        }
        if ((((((*DAT_08012178 == '\0') && (-1 < (int)((uint)pbVar6[0x39] << 0x1d))) &&
              ((pbVar6[0x12] & 0x13) == 0)) &&
             (((*pbVar6 & 1) == 0 && (-1 < (int)((uint)pbVar6[0x51] << 0x1d))))) &&
            (*pcVar4 == '\0')) && (*DAT_08012164 == '\0')) {
          puVar11[10] = 1;
          goto LAB_08012154;
        }
        if (*DAT_0801217c < 10) {
          return;
        }
        bVar12 = puVar11[0x2f] == '\0';
        uVar9 = (char)puVar10;
        if (!bVar12) {
          puVar11[10] = 1;
          puVar11[0x2e] = 0;
          puVar11[0x2f] = 0;
          return;
        }
LAB_0801209e:
        if (bVar12) {
          return;
        }
      }
      if (*DAT_08012178 == '\0') {
        return;
      }
      puVar11[10] = uVar9;
LAB_08012154:
      puVar11[0x2e] = 0;
      return;
    }
    if ((((int)((uint)pbVar6[0x39] << 0x1d) < 0) || ((pbVar6[0x12] & 0x13) != 0)) ||
       (((*pbVar6 & 1) != 0 ||
        ((((int)((uint)pbVar6[0x51] << 0x1d) < 0 || (*DAT_08012160 != '\0')) ||
         (*DAT_08012164 != '\0')))))) {
      puVar11[10] = 2;
    }
    else if ((*DAT_08012168 == '\0') || ((pbVar6[0x1b] & 3) == 0)) {
      bVar1 = pbVar6[0x1b];
      puVar11[10] = 1;
      if ((bVar1 & 3) != 0) {
        puVar11[0x2f] = 1;
        iVar8 = DAT_0801216c;
        if ((pbVar6[0x1b] & 1) != 0) {
          pbVar6[0x1c] = 0;
          *(undefined2 *)(iVar8 + 0x12) = 0;
          pbVar6[0x1e] = 0;
          pbVar6[0x1b] = pbVar6[0x1b] & 0xfe;
        }
        if ((int)((uint)pbVar6[0x1b] << 0x1e) < 0) {
          pbVar6[0x21] = 0;
          *(undefined2 *)(iVar8 + 0x24) = 0;
          pbVar6[0x23] = 0;
          pbVar6[0x1b] = pbVar6[0x1b] & 0xfd;
        }
        puVar11[0x2e] = 0;
      }
    }
    else {
      puVar11[10] = 2;
      puVar11[0x2f] = 1;
    }
LAB_08012000:
    puVar11[0x2e] = 0;
  }
  else {
    if (DAT_08011e84[0x2b] == '\0') {
      DAT_08011e84[0x2b] = 1;
      puVar7[10] = 0;
      *pcVar4 = '\0';
      puVar7[0x2e] = 0;
      puVar7[0x2a] = 0;
    }
    puVar10 = DAT_08011e88;
    puVar11 = puVar7;
    if (((puVar7[0xf] == '\0') && (puVar7[0xe] == '\0')) && (pbVar6[0x45] == 0)) {
      if ((*pcVar2 == '\0') && (*pcVar3 == '\0')) {
        if (puVar7[10] != '\0') {
          if (puVar7[10] == '\x01') {
            if (*pcVar4 == '\x01') {
              *pcVar4 = '\0';
              if (*(byte *)(DAT_08011e94 + 0x14) >> 1 < 5) {
                puVar7[0x2c] = 1;
                return;
              }
              return;
            }
            if (*pcVar4 == '\x02') {
              *pcVar4 = '\0';
              if (*DAT_08011e90 != '\x01') {
                *pcVar5 = '\x03';
                return;
              }
              puVar7[10] = 2;
              puVar7[0x2e] = 0;
              puVar7[0x2c] = 0;
              if (*DAT_08011e98 < 5) {
                puVar7[0x2d] = 1;
              }
              else {
                puVar7[0x2d] = 0;
              }
              uVar9 = 6;
            }
            else {
              if (puVar7[0x2e] == '\0') {
                *DAT_08011e88 = 0;
                puVar7[0x39] = 0;
                FUN_0800ac9c();
                puVar7[0xc] = 4;
                puVar7[0xd] = 3;
                pcVar2 = DAT_08011e9c;
                if (*DAT_08011e9c == '\0') {
                  puVar7[0x38] = 1;
                  FUN_0800c940();
                  puVar7[0xc] = 0;
                  puVar7[0xd] = 4;
                  if ((*pcVar2 == '\0') && (*DAT_08011ea0 == '\0')) {
                    puVar7[0x2e] = 1;
                  }
                }
              }
              else if (puVar7[0x2e] == '\x01') {
                FUN_0800c614();
                puVar7[0xc] = 0;
                puVar7[0xd] = 5;
                *puVar10 = 1;
                if (*pcVar5 == '\x01') {
                  *pcVar5 = '\x02';
                }
              }
              if (((((4 < *(byte *)(DAT_08011e94 + 0x14) >> 1) || (puVar7[0x2c] != '\0')) &&
                   ((pbVar6[0x39] & 3) == 0)) &&
                  (((pbVar6[0x1b] & 3) == 0 && (-1 < (int)((uint)*pbVar6 << 0x1e))))) &&
                 ((-1 < (int)((uint)pbVar6[0x51] << 0x1d) &&
                  (((pbVar6[0x10] & 3) == 0 && (*DAT_08011e8c == '\0')))))) {
                return;
              }
              if (4 < *DAT_08011e98) {
                puVar7[10] = 2;
                puVar7[0x2e] = 0;
              }
              uVar9 = 7;
            }
            puVar7[0xb] = uVar9;
            FUN_08011868(0x48,puVar7[0xc],puVar7[0xd]);
            return;
          }
          if (puVar7[10] != '\x02') {
            return;
          }
          if (*pcVar4 == '\x01') {
            *pcVar4 = '\0';
            if (((((pbVar6[0x39] & 3) == 0) && ((pbVar6[0x1b] & 3) == 0)) &&
                (-1 < (int)((uint)*pbVar6 << 0x1e))) &&
               (((-1 < (int)((uint)pbVar6[0x51] << 0x1d) && ((pbVar6[0x10] & 3) == 0)) &&
                (*DAT_08011e8c == '\0')))) {
              puVar7[10] = 1;
              puVar7[0x2e] = 0;
              puVar7[0x2d] = 0;
              if (*(byte *)(DAT_08011e94 + 0x14) >> 1 < 5) {
                puVar7[0x2c] = 1;
              }
              else {
                puVar7[0x2c] = 0;
              }
              puVar7[0xb] = 8;
              FUN_08011868(0x48,puVar7[0xc],puVar7[0xd]);
            }
            else {
              *pcVar5 = '\x03';
            }
          }
          else if (*pcVar4 == '\x02') {
            *pcVar5 = '\x02';
            *pcVar4 = '\0';
            if (*DAT_08011e98 < 5) {
              puVar7[0x2d] = 1;
            }
          }
          if (puVar7[0x2e] == '\0') {
            *puVar10 = 0;
            puVar7[0x39] = 0;
            FUN_0800ac9c();
            puVar7[0xc] = 4;
            puVar7[0xd] = 6;
            puVar7[0x2e] = 1;
            uVar9 = 9;
          }
          else {
            if (puVar7[0x2e] != '\x01') {
              if (puVar7[0x2e] == '\x02') {
                puVar7[0xc] = 3;
                puVar7[0xd] = 8;
                *puVar10 = 1;
                if (*pcVar5 == '\x01') {
                  *pcVar5 = '\x02';
                }
              }
              goto LAB_08011e28;
            }
            if (pbVar6[0x4d] != 0) {
              *puVar10 = 0;
              puVar7[0x39] = 0;
              FUN_0800ac9c();
            }
            if ((pbVar6[0x4d] != 0) || (*DAT_08011e9c != '\0')) goto LAB_08011e28;
            puVar7[0xc] = 6;
            puVar7[0xd] = 7;
            puVar7[0xb] = 10;
            FUN_08011868(0x48,puVar7[0xc],puVar7[0xd]);
            if (*DAT_08011ea0 == '\0') goto LAB_08011e28;
            puVar7[0x38] = 0;
            FUN_0800c8f4();
            puVar7[0x2e] = 2;
            uVar9 = 0xb;
          }
          puVar7[0xb] = uVar9;
          FUN_08011868(0x48,puVar7[0xc],puVar7[0xd]);
LAB_08011e28:
          if (((*DAT_08011e98 < 5) && (puVar7[0x2d] == '\0')) || (*DAT_08011e90 == '\0')) {
            if (4 < *(byte *)(DAT_08011e94 + 0x14) >> 1) {
              puVar7[10] = 1;
              puVar7[0x2e] = 0;
            }
            puVar7[0xb] = 0xc;
            FUN_08011868(0x48,puVar7[0xc],puVar7[0xd]);
          }
          if (*pcVar5 == '\x01') {
            *pcVar5 = '\x02';
            return;
          }
          return;
        }
        if ((((pbVar6[0x39] & 3) == 0) && ((pbVar6[0x1b] & 3) == 0)) &&
           (((-1 < (int)((uint)*pbVar6 << 0x1e) &&
             ((-1 < (int)((uint)pbVar6[0x51] << 0x1d) && ((pbVar6[0x10] & 3) == 0)))) &&
            (*DAT_08011e8c == '\0')))) {
          if (*DAT_08011e90 == '\0') {
            puVar7[10] = 1;
            puVar7[0xb] = 2;
            goto LAB_08011bdc;
          }
          uVar9 = 5;
          if (4 < *(byte *)(DAT_08011e94 + 0x14) >> 1) {
            puVar7[10] = 1;
            uVar9 = 3;
LAB_08011bd8:
            puVar7[0xb] = uVar9;
            goto LAB_08011bdc;
          }
          if (4 < *DAT_08011e98) {
            puVar7[10] = 2;
            uVar9 = 4;
            goto LAB_08011bd8;
          }
          if (*DAT_08011e98 < 5) {
            puVar7[10] = 1;
            goto LAB_08011bd8;
          }
        }
        else {
          puVar7[10] = 2;
          puVar7[0xb] = 1;
LAB_08011bdc:
          FUN_08011868(0x48,puVar7[0xc],puVar7[0xd]);
        }
        puVar7[0x2c] = 0;
        puVar7[0x2d] = 0;
        goto LAB_08012000;
      }
      puVar7[10] = 0;
      puVar7[0x38] = 0;
      puVar7[0x39] = 0;
      if (pbVar6[0x4d] != 0) {
        FUN_0800ac9c();
      }
      if (pbVar6[0x4c] != 0) {
        FUN_0800c8f4();
      }
      puVar7[0xc] = 3;
      puVar7[0xd] = 2;
    }
    else {
      puVar7[10] = 0;
      puVar7[0xc] = 0;
      puVar7[0xd] = 1;
LAB_08011f10:
      FUN_0800c614();
    }
LAB_08011b34:
    puVar11[9] = 0;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08012180 at 0x08012180
// ---------------------------------------------------------------------------

void FUN_08012180(void)

{
  char cVar1;
  char *pcVar2;
  undefined4 *puVar3;
  
  pcVar2 = DAT_080121b4;
  if (*DAT_080121b0 != 8) {
    *DAT_080121b4 = (char)(*DAT_080121b0 - 8 >> 3);
    puVar3 = DAT_080121b8;
    while (cVar1 = *pcVar2, *pcVar2 = cVar1 + -1, cVar1 != '\0') {
      *puVar3 = 0xaaaa;
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080121bc at 0x080121bc
// ---------------------------------------------------------------------------

void FUN_080121bc(void)

{
  char cVar1;
  char *pcVar2;
  undefined4 *puVar3;
  
  pcVar2 = DAT_08012204;
  if (*DAT_08012200 != 8) {
    *DAT_08012204 = (char)(*DAT_08012200 - 8 >> 3);
    puVar3 = DAT_08012208;
    while (cVar1 = *pcVar2, *pcVar2 = cVar1 + -1, cVar1 != '\0') {
      *puVar3 = 0xaaaa;
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801220c at 0x0801220c
// ---------------------------------------------------------------------------

char FUN_0801220c(void)

{
  byte *pbVar1;
  char cVar2;
  char cVar3;
  uint *puVar4;
  
  pbVar1 = DAT_08012278;
  cVar3 = '\b';
  cVar2 = '\0';
  puVar4 = (uint *)(DAT_08012278 + -8);
  do {
    *puVar4 = ((*puVar4 & 0xffffff0f) + 0x40 & 0xfffffff0) + 4;
    FUN_08012180();
    if ((int)((uint)*pbVar1 << 0x1e) < 0) {
      cVar2 = cVar2 * '\x02' + '\x01';
    }
    else {
      cVar2 = cVar2 << 1;
    }
    FUN_08012180();
    *puVar4 = (*puVar4 & 0xfffffff0) + 3;
    FUN_08012180();
    FUN_08012180();
    cVar3 = cVar3 + -1;
  } while (cVar3 != '\0');
  return cVar2;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801227c at 0x0801227c
// ---------------------------------------------------------------------------

char FUN_0801227c(void)

{
  ushort *puVar1;
  char cVar2;
  char cVar3;
  uint *puVar4;
  
  puVar1 = DAT_080122ec;
  cVar3 = '\b';
  cVar2 = '\0';
  puVar4 = (uint *)(DAT_080122ec + -2);
  do {
    *puVar4 = ((*puVar4 & 0xffff0fff) + 0x4000 & 0xfffff0ff) + 0x400;
    FUN_080121bc();
    if ((int)((uint)*puVar1 << 0x14) < 0) {
      cVar2 = cVar2 * '\x02' + '\x01';
    }
    else {
      cVar2 = cVar2 << 1;
    }
    FUN_080121bc();
    *puVar4 = (*puVar4 & 0xfffff0ff) + 0x300;
    FUN_080121bc();
    FUN_080121bc();
    cVar3 = cVar3 + -1;
  } while (cVar3 != '\0');
  return cVar2;
}



// ---------------------------------------------------------------------------
// Function: FUN_080122f0 at 0x080122f0
// ---------------------------------------------------------------------------

bool FUN_080122f0(undefined1 param_1,undefined4 param_2,undefined1 param_3)

{
  int iVar1;
  char local_18;
  
  local_18 = '\x05';
  do {
    iVar1 = FUN_0801836c(param_1,param_2,param_3);
    if (iVar1 != 0) break;
    local_18 = local_18 + -1;
  } while (local_18 != '\0');
  return local_18 != '\0';
}



// ---------------------------------------------------------------------------
// Function: FUN_08012330 at 0x08012330
// ---------------------------------------------------------------------------

void FUN_08012330(uint param_1,undefined1 *param_2,short param_3)

{
  uint *puVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  uint uVar4;
  bool bVar5;
  
  if (*DAT_0801241c != '\0') {
    FUN_0800f964(param_1,param_2,param_3);
    return;
  }
  FUN_08012528();
  if (param_1 < 0x10000) {
    uVar3 = 0xa0;
  }
  else {
    uVar3 = 0xa2;
  }
  FUN_08012648(uVar3);
  FUN_08012424();
  FUN_08012648((char)(param_1 >> 8));
  FUN_08012424();
  FUN_08012648(param_1 & 0xff);
  FUN_08012424();
  FUN_08012528();
  FUN_08012648(0xa1);
  FUN_08012424();
  puVar1 = DAT_08012420;
  while( true ) {
    bVar5 = param_3 == 0;
    param_3 = param_3 + -1;
    if (bVar5) break;
    uVar2 = FUN_0801220c();
    *param_2 = uVar2;
    if (param_3 == 0) {
      *puVar1 = ((*puVar1 & 0xffffff0f) + 0x40 & 0xfffffff0) + 4;
      FUN_08012180();
      FUN_08012180();
      uVar4 = ((*puVar1 & 0xfffffff0) + 3 & 0xffffff0f) + 0x30;
    }
    else {
      *puVar1 = (*puVar1 & 0xffffff0f) + 0x30;
      FUN_08012180();
      *puVar1 = (*puVar1 & 0xfffffff0) + 4;
      FUN_08012180();
      FUN_08012180();
      uVar4 = ((*puVar1 & 0xfffffff0) + 3 & 0xffffff0f) + 0x40;
    }
    *puVar1 = uVar4;
    FUN_08012180();
    FUN_08012180();
    param_2 = param_2 + 1;
  }
  FUN_080125d4();
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08012424 at 0x08012424
// ---------------------------------------------------------------------------

undefined4 FUN_08012424(void)

{
  uint *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  short local_10;
  undefined4 local_c;
  
  puVar1 = DAT_0801249c;
  local_c = 1;
  local_10 = 200;
  *DAT_0801249c = (*DAT_0801249c & 0xffffff0f) + 0x40;
  FUN_08012180();
  *puVar1 = (*puVar1 & 0xfffffff0) + 4;
  FUN_08012180();
  puVar2 = DAT_080124a0;
  uVar3 = DAT_0801249c[2];
  do {
    if (-1 < (int)(uVar3 << 0x1e)) goto LAB_0801247e;
    *puVar2 = 0xaaaa;
    local_10 = local_10 + -1;
  } while (0 < local_10);
  local_c = 0;
LAB_0801247e:
  FUN_08012180();
  *puVar1 = (*puVar1 & 0xfffffff0) + 3;
  FUN_08012180();
  FUN_08012180();
  return local_c;
}



// ---------------------------------------------------------------------------
// Function: FUN_080124a4 at 0x080124a4
// ---------------------------------------------------------------------------

undefined1 FUN_080124a4(void)

{
  undefined1 uVar1;
  uint *puVar2;
  undefined4 *puVar3;
  uint uVar4;
  short local_10;
  
  puVar2 = DAT_08012520;
  uVar1 = 0;
  local_10 = 100;
  *DAT_08012520 = (*DAT_08012520 & 0xffff0fff) + 0x4000;
  FUN_080121bc();
  *puVar2 = (*puVar2 & 0xfffff0ff) + 0x400;
  FUN_080121bc();
  puVar3 = DAT_08012524;
  uVar4 = puVar2[1];
  do {
    if (-1 < (int)(uVar4 << 0x14)) goto LAB_08012500;
    *puVar3 = 0xaaaa;
    local_10 = local_10 + -1;
  } while (0 < local_10);
  uVar1 = 1;
LAB_08012500:
  FUN_080121bc();
  *puVar2 = (*puVar2 & 0xfffff0ff) + 0x300;
  FUN_080121bc();
  FUN_080121bc();
  return uVar1;
}



// ---------------------------------------------------------------------------
// Function: FUN_08012528 at 0x08012528
// ---------------------------------------------------------------------------

void FUN_08012528(void)

{
  undefined4 *puVar1;
  uint *puVar2;
  
  puVar1 = DAT_08012574;
  *DAT_08012574 = 1;
  *puVar1 = 2;
  puVar2 = DAT_08012574 + -5;
  *puVar2 = ((*puVar2 & 0xffffff0f) + 0x40 & 0xfffffff0) + 4;
  FUN_08012180();
  FUN_08012180();
  *puVar2 = (*puVar2 & 0xffffff0f) + 0x30;
  FUN_08012180();
  FUN_08012180();
  *puVar2 = (*puVar2 & 0xfffffff0) + 3;
  FUN_08012180();
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08012578 at 0x08012578
// ---------------------------------------------------------------------------

void FUN_08012578(void)

{
  int *piVar1;
  uint *puVar2;
  
  piVar1 = DAT_080125d0;
  *DAT_080125d0 = 0x400;
  *piVar1 = (int)piVar1 >> 0x13;
  puVar2 = (uint *)(DAT_080125d0 + -4);
  *puVar2 = ((*puVar2 & 0xffff0fff) + 0x4000 & 0xfffff0ff) + 0x400;
  FUN_080121bc();
  FUN_080121bc();
  *puVar2 = (*puVar2 & 0xffff0fff) + 0x3000;
  FUN_080121bc();
  FUN_080121bc();
  *puVar2 = (*puVar2 & 0xfffff0ff) + 0x300;
  FUN_080121bc();
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080125d4 at 0x080125d4
// ---------------------------------------------------------------------------

void FUN_080125d4(void)

{
  uint *puVar1;
  
  puVar1 = DAT_08012608;
  *DAT_08012608 = ((*DAT_08012608 & 0xffffff0f) + 0x30 & 0xfffffff0) + 4;
  FUN_08012180();
  FUN_08012180();
  *puVar1 = (*puVar1 & 0xffffff0f) + 0x40;
  FUN_08012180();
  FUN_08012180();
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801260c at 0x0801260c
// ---------------------------------------------------------------------------

void FUN_0801260c(void)

{
  uint *puVar1;
  
  puVar1 = DAT_08012644;
  *DAT_08012644 = ((*DAT_08012644 & 0xffff0fff) + 0x3000 & 0xfffff0ff) + 0x400;
  FUN_080121bc();
  FUN_080121bc();
  *puVar1 = (*puVar1 & 0xffff0fff) + 0x4000;
  FUN_080121bc();
  FUN_080121bc();
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08012648 at 0x08012648
// ---------------------------------------------------------------------------

void FUN_08012648(byte param_1)

{
  uint *puVar1;
  uint uVar2;
  bool bVar3;
  char local_10;
  
  puVar1 = DAT_080126ac;
  local_10 = '\b';
  do {
    if ((int)((uint)param_1 << 0x18) < 0) {
      uVar2 = (*puVar1 & 0xffffff0f) + 0x40;
    }
    else {
      uVar2 = (*puVar1 & 0xffffff0f) + 0x30;
    }
    *puVar1 = uVar2;
    FUN_08012180();
    FUN_08012180();
    *puVar1 = (*puVar1 & 0xfffffff0) + 4;
    FUN_08012180();
    FUN_08012180();
    *puVar1 = (*puVar1 & 0xfffffff0) + 3;
    param_1 = param_1 << 1;
    bVar3 = local_10 != '\x01';
    local_10 = local_10 + -1;
  } while (bVar3);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080126b0 at 0x080126b0
// ---------------------------------------------------------------------------

void FUN_080126b0(byte param_1)

{
  uint *puVar1;
  uint uVar2;
  bool bVar3;
  char local_10;
  
  puVar1 = DAT_0801271c;
  local_10 = '\b';
  do {
    if ((int)((uint)param_1 << 0x18) < 0) {
      uVar2 = (*puVar1 & 0xffff0fff) + 0x4000;
    }
    else {
      uVar2 = (*puVar1 & 0xffff0fff) + 0x3000;
    }
    *puVar1 = uVar2;
    FUN_080121bc();
    FUN_080121bc();
    *puVar1 = (*puVar1 & 0xfffff0ff) + 0x400;
    FUN_080121bc();
    FUN_080121bc();
    *puVar1 = (*puVar1 & 0xfffff0ff) + 0x300;
    param_1 = param_1 << 1;
    bVar3 = local_10 != '\x01';
    local_10 = local_10 + -1;
  } while (bVar3);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08012720 at 0x08012720
// ---------------------------------------------------------------------------

bool FUN_08012720(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  int iVar1;
  char local_18;
  
  local_18 = '\x05';
  do {
    iVar1 = FUN_08021b70(param_1,param_2,param_3);
    if (iVar1 != 0) break;
    local_18 = local_18 + -1;
  } while (local_18 != '\0');
  return local_18 != '\0';
}



// ---------------------------------------------------------------------------
// Function: FUN_08012760 at 0x08012760
// ---------------------------------------------------------------------------

bool FUN_08012760(undefined1 param_1,undefined4 param_2,undefined1 param_3)

{
  int iVar1;
  char local_18;
  
  local_18 = '\x05';
  do {
    iVar1 = FUN_08021c10(param_1,param_2,param_3);
    if (iVar1 != 0) break;
    local_18 = local_18 + -1;
  } while (local_18 != '\0');
  return local_18 != '\0';
}



// ---------------------------------------------------------------------------
// Function: FUN_080127a0 at 0x080127a0
// ---------------------------------------------------------------------------

bool FUN_080127a0(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  int iVar1;
  char local_18;
  
  local_18 = '\x05';
  do {
    iVar1 = FUN_08021d1c(param_1,param_2,param_3);
    if (iVar1 != 0) break;
    local_18 = local_18 + -1;
  } while (local_18 != '\0');
  return local_18 != '\0';
}



// ---------------------------------------------------------------------------
// Function: FUN_080127e0 at 0x080127e0
// ---------------------------------------------------------------------------

void FUN_080127e0(uint param_1,int param_2,ushort param_3)

{
  int iVar1;
  byte local_28;
  byte local_24;
  
  iVar1 = DAT_08012888;
  if (*DAT_08012884 != '\0') {
    FUN_0800fa6c(param_1,param_2,param_3);
    return;
  }
  if ((uint)param_3 <= ((param_1 >> 5) + 1) * 0x20 - param_1) {
    for (local_24 = 0; local_24 < 5; local_24 = local_24 + 1) {
      FUN_08022ea0(param_1 & 0xffff,param_2,param_3);
      FUN_08012330(param_1,DAT_08012888,param_3);
      for (local_28 = 0;
          (local_28 < param_3 &&
          (*(char *)(param_2 + (uint)local_28) == *(char *)(iVar1 + (uint)local_28)));
          local_28 = local_28 + 1) {
      }
      if (param_3 <= local_28) {
        return;
      }
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801288c at 0x0801288c
// ---------------------------------------------------------------------------

void FUN_0801288c(undefined4 param_1)

{
  *(undefined4 *)(DAT_08012894 + 8) = param_1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080128a8 at 0x080128a8
// ---------------------------------------------------------------------------

void FUN_080128a8(void)

{
  *DAT_080128b4 = 0xaaaa;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080128b8 at 0x080128b8
// ---------------------------------------------------------------------------

void FUN_080128b8(undefined4 param_1)

{
  *(undefined4 *)(DAT_080128c0 + 4) = param_1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080128c4 at 0x080128c4
// ---------------------------------------------------------------------------

void FUN_080128c4(undefined4 param_1)

{
  *DAT_080128cc = param_1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080128d0 at 0x080128d0
// ---------------------------------------------------------------------------

void FUN_080128d0(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  float fVar4;
  
  iVar2 = DAT_08012980;
  iVar1 = DAT_08012974;
  if (*(char *)(DAT_08012970 + 0x17) != '\0') {
    fVar4 = *(float *)(DAT_08012978 + 0xc) - *(float *)(DAT_0801297c + 0xc);
    if (*(char *)(DAT_08012974 + 0x50) == '\0') {
      if (*(float *)(DAT_08012970 + 0x18) <= fVar4) {
        *(char *)(DAT_08012980 + 0x25) = *(char *)(DAT_08012980 + 0x25) + '\x01';
        if (*(byte *)(iVar2 + 0x25) < 0x33) {
          return;
        }
        *(undefined1 *)(iVar2 + 0x25) = 0;
        if (*(char *)(iVar1 + 0x50) == '\x01') {
          return;
        }
        *(undefined1 *)(iVar1 + 0x50) = 1;
        uVar3 = 0x5a;
        goto LAB_08012968;
      }
    }
    else if (fVar4 <= *(float *)(DAT_08012970 + 0x1c)) {
      *(char *)(DAT_08012980 + 0x25) = *(char *)(DAT_08012980 + 0x25) + '\x01';
      if (*(byte *)(iVar2 + 0x25) < 0x33) {
        return;
      }
      *(undefined1 *)(iVar2 + 0x25) = 0;
      if (*(char *)(iVar1 + 0x50) == '\0') {
        return;
      }
      *(undefined1 *)(iVar1 + 0x50) = 0;
      uVar3 = 0x5b;
LAB_08012968:
      FUN_08019844(0,uVar3);
      return;
    }
    *(undefined1 *)(DAT_08012980 + 0x25) = 0;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08012984 at 0x08012984
// ---------------------------------------------------------------------------

void FUN_08012984(void)

{
  uint in_r3;
  uint local_8;
  
  local_8 = in_r3;
  FUN_08008914(DAT_080129a8);
  FUN_08008914(DAT_080129ac);
  local_8 = CONCAT22(local_8._2_2_,0x30);
  local_8 = local_8 & 0xffffff;
  FUN_0801031c(DAT_080129b0,&local_8);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080129b4 at 0x080129b4
// ---------------------------------------------------------------------------

void FUN_080129b4(void)

{
  uint uVar1;
  int iVar2;
  uint in_fpscr;
  undefined4 uVar3;
  undefined4 uVar4;
  uint local_18;
  
  local_18 = 0;
  FUN_08012330(0x180,&local_18,4);
  iVar2 = DAT_08012a70;
  uVar4 = DAT_08012a6c;
  uVar1 = DAT_08012a68;
  if (local_18 < DAT_08012a68) {
    uVar3 = VectorUnsignedToFloat(local_18,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(DAT_08012a70 + 8) = uVar3;
  }
  else {
    *(undefined4 *)(DAT_08012a70 + 8) = DAT_08012a6c;
  }
  FUN_08012330(0x184,&local_18,4);
  if (local_18 < uVar1) {
    uVar3 = VectorUnsignedToFloat(local_18,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(iVar2 + 0xc) = uVar3;
  }
  else {
    *(undefined4 *)(iVar2 + 0xc) = uVar4;
  }
  FUN_08012330(0x188,&local_18,4);
  if (local_18 < uVar1) {
    uVar3 = VectorUnsignedToFloat(local_18,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(iVar2 + 0x10) = uVar3;
  }
  else {
    *(undefined4 *)(iVar2 + 0x10) = uVar4;
  }
  FUN_08012330(0x18c,&local_18,4);
  if (local_18 < uVar1) {
    uVar4 = VectorUnsignedToFloat(local_18,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(iVar2 + 0x14) = uVar4;
  }
  else {
    *(undefined4 *)(iVar2 + 0x14) = uVar4;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08012a74 at 0x08012a74
// ---------------------------------------------------------------------------

void FUN_08012a74(void)

{
  byte bVar1;
  ushort uVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  uint in_fpscr;
  float fVar9;
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  undefined8 uVar14;
  byte local_38;
  
  for (local_38 = 0; local_38 < 10; local_38 = local_38 + 1) {
    FUN_08012330(0x140,DAT_08012e98,0x18);
    iVar6 = FUN_08018354(0x15d);
    iVar7 = FUN_0800ba48(DAT_08012e98,0x18);
    if (iVar6 == iVar7) break;
  }
  iVar6 = DAT_08012e9c;
  pbVar3 = DAT_08012e98;
  if (local_38 == 10) {
    local_38 = 0;
    iVar7 = *(int *)(DAT_08012e9c + 0x68);
    for (; local_38 < 0x18; local_38 = local_38 + 1) {
      pbVar3[local_38] = *(byte *)(iVar7 + (uint)local_38);
    }
  }
  uVar10 = DAT_08012ea4;
  iVar7 = DAT_08012ea0;
  uVar2 = (ushort)*pbVar3;
  bVar1 = pbVar3[9];
  if (((*pbVar3 & 1) == 0) || (bVar1 == 0xff)) {
    *(undefined1 *)(DAT_08012ea0 + 0x28) = 0;
    *(undefined4 *)(iVar7 + 0x3c) = uVar10;
    *(undefined4 *)(iVar7 + 0x2c) = uVar10;
    *(undefined1 *)(iVar7 + -0x24) = 0;
    *(undefined4 *)(iVar7 + -0x10) = uVar10;
    *(undefined4 *)(iVar7 + -0x20) = uVar10;
    *pbVar3 = *pbVar3 & 0xfe;
  }
  else {
    *(undefined1 *)(DAT_08012ea0 + 0x28) = 1;
    uVar14 = FUN_08008548(CONCAT11(pbVar3[3],pbVar3[4]));
    FUN_08008448((int)uVar14,(int)((ulonglong)uVar14 >> 0x20),(int)DAT_08012ea8,
                 (int)((ulonglong)DAT_08012ea8 >> 0x20));
    uVar8 = FUN_08008658();
    *(undefined4 *)(iVar7 + 0x3c) = uVar8;
    fVar9 = DAT_08012eb0;
    *(float *)(iVar7 + 0x40) = *(float *)(iVar7 + 0x3c) + DAT_08012eb0;
    fVar11 = (float)VectorUnsignedToFloat((uint)pbVar3[6],(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(iVar7 + 0x2c) = fVar11 / 10.0 + DAT_08012eb4;
    fVar11 = DAT_08012eb8;
    *(float *)(iVar7 + 0x30) = *(float *)(iVar7 + 0x2c) + DAT_08012eb8;
    *(undefined2 *)(iVar7 + 0x44) = 1000;
    *(undefined2 *)(iVar7 + 0x46) = 1000;
    *(undefined2 *)(iVar7 + 0x34) = 1000;
    *(undefined2 *)(iVar7 + 0x36) = 1000;
    *(undefined1 *)(iVar7 + -0x24) = 1;
    fVar12 = (float)VectorUnsignedToFloat
                              ((uint)CONCAT11(pbVar3[1],pbVar3[2]),(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(iVar7 + -0x10) = fVar12 / DAT_08012ebc;
    *(float *)(iVar7 + -0xc) = *(float *)(iVar7 + -0x10) - fVar9;
    fVar9 = (float)VectorUnsignedToFloat((uint)pbVar3[5],(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(iVar7 + -0x20) = fVar9 / 20.0 + 2.0;
    *(float *)(iVar7 + -0x1c) = *(float *)(iVar7 + -0x20) - fVar11;
    *(undefined2 *)(iVar7 + -8) = 2000;
    *(undefined2 *)(iVar7 + -6) = 2000;
    *(undefined2 *)(iVar7 + -0x18) = 2000;
    *(undefined2 *)(iVar7 + -0x16) = 2000;
  }
  iVar7 = DAT_08012ea0;
  if ((-1 < (int)((uint)uVar2 << 0x1e)) || (bVar1 == 0xff)) {
    *(undefined1 *)(DAT_08012ea0 + 0x6c) = 0;
    *(undefined4 *)(iVar7 + 0x70) = uVar10;
    *(undefined4 *)(iVar7 + 0x74) = uVar10;
    *pbVar3 = *pbVar3 & 0xfd;
    goto LAB_08012d2e;
  }
  *(undefined1 *)(DAT_08012ea0 + 0x6c) = 1;
  if (*(char *)(iVar6 + 6) == '\x01') {
    uVar14 = FUN_08008548(pbVar3[7]);
    uVar8 = (undefined4)((ulonglong)DAT_08012ec0 >> 0x20);
    uVar13 = (undefined4)DAT_08012ec0;
    uVar14 = FUN_08008364((int)uVar14,(int)((ulonglong)uVar14 >> 0x20),uVar13,uVar8);
    FUN_08008216((int)uVar14,(int)((ulonglong)uVar14 >> 0x20),uVar13,uVar8);
    uVar10 = FUN_08008658();
    *(undefined4 *)(iVar7 + 0x70) = uVar10;
    uVar14 = FUN_08008548(pbVar3[8]);
    uVar14 = FUN_08008364((int)uVar14,(int)((ulonglong)uVar14 >> 0x20),uVar13,uVar8);
    FUN_08008216((int)uVar14,(int)((ulonglong)uVar14 >> 0x20),uVar13,uVar8);
LAB_08012d10:
    uVar10 = FUN_08008658();
  }
  else {
    if (*(char *)(iVar6 + 6) == '\x02') {
      uVar14 = FUN_08008548();
      FUN_08008364((int)uVar14,(int)((ulonglong)uVar14 >> 0x20),(int)DAT_08012ec8,
                   (int)((ulonglong)DAT_08012ec8 >> 0x20));
      uVar10 = FUN_08008658();
      *(undefined4 *)(iVar7 + 0x70) = uVar10;
      uVar14 = FUN_08008548(pbVar3[8] + 1);
      FUN_08008364((int)uVar14,(int)((ulonglong)uVar14 >> 0x20),(int)DAT_08012ed0,
                   (int)((ulonglong)DAT_08012ed0 >> 0x20));
      goto LAB_08012d10;
    }
    uVar10 = VectorUnsignedToFloat(pbVar3[7] + 1,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(iVar7 + 0x70) = uVar10;
    uVar10 = VectorUnsignedToFloat(pbVar3[8] + 1,(byte)(in_fpscr >> 0x16) & 3);
  }
  *(undefined4 *)(iVar7 + 0x74) = uVar10;
LAB_08012d2e:
  iVar4 = DAT_08012ea0;
  if (((int)((uint)uVar2 << 0x1d) < 0) && (bVar1 != 0xff)) {
    *(undefined1 *)(DAT_08012ea0 + -0x83) = 1;
    *(ushort *)(iVar4 + -0x82) = pbVar3[9] + 0x1e;
    *(ushort *)(iVar4 + -0x80) = pbVar3[10] - 0x28;
    *(ushort *)(iVar4 + -0x7e) = pbVar3[0xb] + 0x1e;
    *(ushort *)(iVar4 + -0x7c) = pbVar3[0xc] - 0x28;
    *(undefined2 *)(iVar4 + -0x7a) = 5000;
    *(undefined2 *)(iVar4 + -0x78) = 5000;
  }
  else {
    *(undefined1 *)(DAT_08012ea0 + -0x83) = 0;
    *(undefined2 *)(iVar4 + -0x82) = 0;
    *(undefined2 *)(iVar4 + -0x80) = 0;
    *(undefined2 *)(iVar4 + -0x7e) = 0;
    *(undefined2 *)(iVar4 + -0x7c) = 0;
    *pbVar3 = *pbVar3 & 0xfb;
  }
  if (((int)((uint)uVar2 << 0x1c) < 0) && (bVar1 != 0xff)) {
    *(undefined1 *)(iVar4 + -0x4e) = 1;
    *(ushort *)(iVar4 + -0x52) = pbVar3[0xd] - 0x28;
    *(ushort *)(iVar4 + -0x50) = pbVar3[0xe] - 0x28;
  }
  else {
    *(undefined1 *)(iVar4 + -0x4e) = 0;
    *pbVar3 = *pbVar3 & 0xf7;
  }
  iVar5 = DAT_08012ea0;
  if (((int)((uint)uVar2 << 0x1b) < 0) && (bVar1 != 0xff)) {
    *(undefined1 *)(DAT_08012ea0 + -0xb5) = 1;
    uVar14 = FUN_08008548(CONCAT11(pbVar3[0xf],pbVar3[0x10]));
    uVar8 = (undefined4)((ulonglong)DAT_08012ed8 >> 0x20);
    uVar13 = (undefined4)DAT_08012ed8;
    FUN_08008448((int)uVar14,(int)((ulonglong)uVar14 >> 0x20),uVar13,uVar8);
    uVar10 = FUN_08008658();
    *(undefined4 *)(iVar5 + -0xb4) = uVar10;
    uVar14 = FUN_08008548(CONCAT11(pbVar3[0x11],pbVar3[0x12]));
    FUN_08008448((int)uVar14,(int)((ulonglong)uVar14 >> 0x20),uVar13,uVar8);
    uVar10 = FUN_08008658();
    *(undefined4 *)(iVar5 + -0xb0) = uVar10;
  }
  else {
    *(undefined1 *)(DAT_08012ea0 + -0xb5) = 0;
    *pbVar3 = *pbVar3 & 0xef;
  }
  if (((int)((uint)uVar2 << 0x1a) < 0) && (bVar1 != 0xff)) {
    *(undefined1 *)(iVar4 + -0x60) = 1;
    *(ushort *)(iVar4 + -0x5e) = pbVar3[0x13] + 0x1e;
    *(ushort *)(iVar4 + -0x5c) = pbVar3[0x14] - 0x28;
  }
  else {
    *(undefined1 *)(iVar4 + -0x60) = 0;
    *(undefined2 *)(iVar4 + -0x5e) = 0x4b;
    *(undefined2 *)(iVar4 + -0x5c) = 0xffe2;
    *pbVar3 = *pbVar3 & 0xdf;
  }
  iVar5 = DAT_08012ee0;
  if (((int)((uint)uVar2 << 0x19) < 0) && (bVar1 != 0xff)) {
    *(undefined1 *)(DAT_08012ee0 + 0x4c) = 1;
    *(byte *)(iVar5 + 0x4d) = pbVar3[0x15];
  }
  else {
    *(undefined1 *)(DAT_08012ee0 + 0x4c) = 0;
    *(undefined1 *)(iVar5 + 0x4d) = 0;
    *pbVar3 = *pbVar3 & 0xbf;
  }
  if (((int)((uint)uVar2 << 0x18) < 0) && (bVar1 != 0xff)) {
    *(ushort *)(iVar6 + 0x16) = pbVar3[0x16] - 0x28;
    *(ushort *)(iVar6 + 0x18) = pbVar3[0x17] - 0x28;
  }
  else {
    *pbVar3 = *pbVar3 & 0x7f;
  }
  *(short *)(iVar6 + 0x1a) = *(short *)(iVar4 + -0x82) + -2;
  *(short *)(iVar6 + 0x1c) = *(short *)(iVar4 + -0x80) + 2;
  *(short *)(iVar6 + 0x1e) = *(short *)(iVar4 + -0x7e) + -2;
  *(short *)(iVar6 + 0x20) = *(short *)(iVar4 + -0x7c) + 2;
  *(undefined2 *)(iVar6 + 0x22) = 5;
  *(undefined2 *)(iVar6 + 0x24) = 5;
  *(undefined2 *)(iVar6 + 0x26) = 5;
  *(short *)(iVar6 + 0x28) = *(short *)(iVar4 + -0x5e) + -2;
  *(undefined2 *)(iVar6 + 0x2a) = 5;
  *(undefined2 *)(iVar6 + 0x2c) = 5;
  *(short *)(iVar6 + 0x2e) = *(short *)(iVar4 + -0x5c) + 2;
  *(undefined2 *)(iVar6 + 0x30) = 5;
  fVar9 = DAT_08012f94;
  *(float *)(iVar6 + 0x54) = *(float *)(iVar7 + 0x70) * DAT_08012f94;
  *(undefined2 *)(iVar6 + 0x32) = 5;
  *(undefined2 *)(iVar6 + 0x34) = 5;
  *(float *)(iVar6 + 0x58) = *(float *)(iVar7 + 0x74) * fVar9;
  *(undefined2 *)(iVar6 + 0x36) = 5;
  *(undefined2 *)(iVar6 + 0x38) = 5;
  *(undefined2 *)(iVar6 + 0x3a) = 5;
  *(undefined2 *)(iVar6 + 0x3c) = 5;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08012f98 at 0x08012f98
// ---------------------------------------------------------------------------

void FUN_08012f98(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  
  iVar1 = DAT_08012ff8;
  uVar3 = FUN_08008548(*(undefined1 *)(DAT_08012ff8 + 0x13));
  uVar3 = FUN_08008448((int)uVar3,(int)((ulonglong)uVar3 >> 0x20),(int)DAT_08012ffc,
                       (int)((ulonglong)DAT_08012ffc >> 0x20));
  FUN_08008216((int)uVar3,(int)((ulonglong)uVar3 >> 0x20),(int)DAT_08013004,
               (int)((ulonglong)DAT_08013004 >> 0x20));
  uVar2 = FUN_08008658();
  *(undefined4 *)(iVar1 + -800) = uVar2;
  uVar3 = FUN_08008548(*(undefined1 *)(iVar1 + 0x12));
  uVar3 = FUN_08008364((int)uVar3,(int)((ulonglong)uVar3 >> 0x20),(int)DAT_0801300c,
                       (int)((ulonglong)DAT_0801300c >> 0x20));
  FUN_08008216((int)uVar3,(int)((ulonglong)uVar3 >> 0x20),(int)DAT_08013014,
               (int)((ulonglong)DAT_08013014 >> 0x20));
  uVar2 = FUN_08008658();
  *(undefined4 *)(iVar1 + -0x31c) = uVar2;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801301c at 0x0801301c
// ---------------------------------------------------------------------------

void FUN_0801301c(void)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint in_r3;
  uint local_28;
  uint local_20;
  
  local_20 = in_r3 & 0xffffff00;
  for (bVar1 = 0; bVar1 < 10; bVar1 = bVar1 + 1) {
    FUN_08012330(0x20,DAT_08013280);
    iVar3 = FUN_08018354(0x15f);
    iVar5 = FUN_0800ba48(DAT_08013280,0x20);
    if (iVar3 == iVar5) break;
  }
  iVar5 = DAT_08013284;
  iVar3 = DAT_08013280;
  if (bVar1 == 10) {
    local_28 = 0;
    iVar4 = *(int *)(DAT_08013284 + 0x5c);
    while ((byte)local_28 < 0x20) {
      *(undefined1 *)(iVar3 + local_28) = *(undefined1 *)(iVar4 + local_28);
      local_28 = (uint)(byte)((byte)local_28 + 1);
    }
    FUN_080127e0(0x20,DAT_08013280);
    uVar2 = FUN_0800ba48(DAT_08013280,0x20);
    local_20._0_1_ = uVar2;
    FUN_080127e0(0x15f,&local_20,1);
    local_28 = 0;
    iVar4 = *(int *)(iVar5 + 0x60);
    iVar6 = DAT_08013280 + 0x20;
    while ((byte)local_28 < 0x1e) {
      *(undefined1 *)(iVar6 + local_28) = *(undefined1 *)(iVar4 + local_28);
      local_28 = (uint)(byte)((byte)local_28 + 1);
    }
    FUN_080127e0(0x120,DAT_08013280 + 0x20,0x1e);
    local_20._0_1_ = FUN_0800ba48(DAT_08013280 + 0x20,0x1e);
    FUN_080127e0(0x15e,&local_20,1);
    local_28 = 0;
    iVar4 = *(int *)(iVar5 + 0x68);
    iVar6 = DAT_08013280 + 0x40;
    while ((byte)local_28 < 0x18) {
      *(undefined1 *)(iVar6 + local_28) = *(undefined1 *)(iVar4 + local_28);
      local_28 = (uint)(byte)((byte)local_28 + 1);
    }
    FUN_080127e0(0x140,DAT_08013280 + 0x40,0x18);
    local_20._0_1_ = FUN_0800ba48(DAT_08013280 + 0x40,0x18);
    FUN_080127e0(0x15d,&local_20,1);
    local_28 = 0;
    iVar4 = *(int *)(iVar5 + 100);
    iVar6 = DAT_08013280 + 0x60;
    while ((byte)local_28 < 0xb) {
      *(undefined1 *)(iVar6 + local_28) = *(undefined1 *)(iVar4 + local_28);
      local_28 = (uint)(byte)((byte)local_28 + 1);
    }
    FUN_080127e0(0xb4,DAT_08013280 + 0x60,0xb);
    local_20._0_1_ = FUN_0800ba48(DAT_08013280 + 0x60,0xb);
    FUN_080127e0(0x15c,&local_20,1);
    iVar4 = DAT_08013280 + 0x80;
    local_28 = 0;
    while ((byte)local_28 < 0x20) {
      *(undefined1 *)(iVar4 + local_28) = 0;
      local_28 = (uint)(byte)((byte)local_28 + 1);
    }
    FUN_080127e0(0xc0,DAT_08013280 + 0x80,0x20);
    uVar2 = FUN_0800ba48(DAT_08013280 + 0x80,0x20);
    local_20 = CONCAT31(local_20._1_3_,uVar2);
    FUN_080127e0(0x15b,&local_20,1);
  }
  for (bVar1 = 0; bVar1 < 10; bVar1 = bVar1 + 1) {
    FUN_08012330(0x20,DAT_08013280);
    iVar4 = FUN_08018354(0x15f);
    iVar6 = FUN_0800ba48(DAT_08013280,0x20);
    if (iVar4 == iVar6) break;
  }
  if (bVar1 == 10) {
    local_28 = 0;
    iVar5 = *(int *)(iVar5 + 0x5c);
    while (local_28 < 0x20) {
      *(undefined1 *)(iVar3 + local_28) = *(undefined1 *)(iVar5 + local_28);
      local_28 = (uint)(byte)((byte)local_28 + 1);
    }
  }
  FUN_0801571c();
  FUN_08015768();
  FUN_08015f2c();
  FUN_08012f98();
  FUN_080155cc();
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08013374 at 0x08013374
// ---------------------------------------------------------------------------

void FUN_08013374(void)

{
  int iVar1;
  ushort *puVar2;
  undefined4 uVar3;
  uint in_fpscr;
  float fVar4;
  
  uVar3 = FUN_08010ec4();
  iVar1 = DAT_0801342c;
  *(undefined4 *)(DAT_0801342c + 0x5c) = uVar3;
  uVar3 = FUN_08010ecc();
  *(undefined4 *)(iVar1 + 0x60) = uVar3;
  uVar3 = FUN_08010ed4();
  *(undefined4 *)(iVar1 + 100) = uVar3;
  uVar3 = FUN_08010ebc();
  *(undefined4 *)(iVar1 + 0x68) = uVar3;
  FUN_080146f4();
  FUN_0801301c();
  FUN_080141cc();
  FUN_080153bc();
  FUN_08012a74();
  FUN_08014b50();
  FUN_0801375c();
  FUN_08016000();
  FUN_08013448();
  FUN_080136a4();
  FUN_080159fc();
  FUN_08014060();
  puVar2 = DAT_08013430;
  if (*(char *)(iVar1 + 4) == '\0') {
    fVar4 = (float)VectorUnsignedToFloat
                             (*(undefined4 *)(DAT_0801343c + 4),(byte)(in_fpscr >> 0x16) & 3);
    fVar4 = ((fVar4 * DAT_08013440) / (*(float *)(iVar1 + 0x44) * DAT_08013444)) * 9.0;
  }
  else {
    fVar4 = (float)VectorUnsignedToFloat((uint)*(byte *)(iVar1 + 4),(byte)(in_fpscr >> 0x16) & 3);
    fVar4 = fVar4 * DAT_08013434 * 0.25;
  }
  uVar3 = VectorFloatToUnsigned(fVar4,3);
  *DAT_08013430 = (ushort)uVar3;
  if (900 < *puVar2) {
    *puVar2 = 900;
  }
  *DAT_08013438 = *puVar2;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08013448 at 0x08013448
// ---------------------------------------------------------------------------

void FUN_08013448(void)

{
  float fVar1;
  int iVar2;
  float fVar3;
  float *pfVar4;
  int iVar5;
  undefined1 *puVar6;
  float *pfVar7;
  float *pfVar8;
  float *pfVar9;
  short sVar10;
  float fVar11;
  undefined4 uVar12;
  uint in_fpscr;
  float fVar13;
  undefined4 uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  byte local_30;
  
  pfVar4 = DAT_08013664;
  fVar3 = DAT_08013660;
  iVar2 = DAT_0801365c;
  fVar1 = DAT_08013658;
  fVar11 = DAT_08013654;
  for (local_30 = 0; local_30 < 10; local_30 = local_30 + 1) {
    sVar10 = FUN_08018768(0x40);
    fVar13 = (float)VectorSignedToFloat((int)sVar10,(byte)(in_fpscr >> 0x16) & 3);
    if ((((uint)fVar13 < (uint)fVar1) && ((int)fVar13 < iVar2)) && (fVar13 != fVar3)) {
      *pfVar4 = fVar13 / fVar11;
      break;
    }
  }
  iVar5 = DAT_08013668;
  if (local_30 < 10) {
    *(undefined1 *)(DAT_08013668 + 1) = 1;
  }
  else {
    *pfVar4 = 2.0;
  }
  for (local_30 = 0; local_30 < 10; local_30 = local_30 + 1) {
    sVar10 = FUN_08018768(0x42);
    fVar13 = (float)VectorSignedToFloat((int)sVar10,(byte)(in_fpscr >> 0x16) & 3);
    if ((((uint)fVar13 < (uint)fVar1) && ((int)fVar13 < iVar2)) && (fVar13 != fVar3)) {
      pfVar4[1] = fVar13 / fVar11;
      break;
    }
  }
  if (local_30 < 10) {
    if (*(char *)(iVar5 + 1) == '\x01') {
      *(undefined1 *)(iVar5 + 1) = 2;
    }
  }
  else {
    pfVar4[1] = 2.0;
  }
  iVar5 = DAT_0801367c;
  iVar2 = DAT_08013678;
  uVar16 = DAT_08013670;
  puVar6 = DAT_0801366c;
  local_30 = 0;
  while( true ) {
    uVar14 = (undefined4)uVar16;
    uVar12 = (undefined4)((ulonglong)uVar16 >> 0x20);
    if (9 < local_30) break;
    FUN_08018768(0x44);
    uVar15 = FUN_08008548();
    FUN_08008448((int)uVar15,(int)((ulonglong)uVar15 >> 0x20),uVar14,uVar12);
    fVar11 = (float)FUN_08008658();
    if ((iVar2 < (int)fVar11) && ((int)fVar11 < iVar5)) {
      pfVar4[2] = fVar11;
      *puVar6 = 0;
      break;
    }
    local_30 = local_30 + 1;
  }
  if (9 < local_30) {
    pfVar4[2] = 1.0;
    *puVar6 = 1;
  }
  local_30 = 0;
  do {
    if (9 < local_30) {
LAB_080135d0:
      if (9 < local_30) {
        pfVar4[3] = pfVar4[2];
      }
      FUN_08013fb8();
      iVar2 = DAT_0801369c;
      pfVar9 = DAT_08013698;
      pfVar7 = DAT_0801368c;
      fVar11 = DAT_08013684;
      pfVar4 = DAT_08013680;
      *DAT_0801368c = *DAT_08013688 / (*DAT_08013680 * DAT_08013684);
      pfVar8 = DAT_08013694;
      *DAT_08013694 = *DAT_08013690 / (*pfVar4 * fVar11);
      if ((int)*pfVar9 <= iVar2) {
        *pfVar9 = *pfVar7;
      }
      if ((int)*DAT_080136a0 <= iVar2) {
        *DAT_080136a0 = *pfVar8;
      }
      return;
    }
    FUN_08018768(0x4a);
    uVar16 = FUN_08008548();
    FUN_08008448((int)uVar16,(int)((ulonglong)uVar16 >> 0x20),uVar14,uVar12);
    fVar11 = (float)FUN_08008658();
    if ((iVar2 < (int)fVar11) && ((int)fVar11 < iVar5)) {
      pfVar4[3] = fVar11;
      goto LAB_080135d0;
    }
    local_30 = local_30 + 1;
  } while( true );
}



// ---------------------------------------------------------------------------
// Function: FUN_080136a4 at 0x080136a4
// ---------------------------------------------------------------------------

void FUN_080136a4(undefined4 param_1,uint param_2,uint param_3,uint param_4)

{
  byte *pbVar1;
  byte bVar2;
  char cVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  char cVar7;
  undefined4 local_20;
  uint local_1c;
  uint local_18;
  
  pbVar1 = DAT_08013758;
  local_18 = param_4 & 0xffffff00;
  local_20 = param_2;
  local_1c = param_3;
  if (*(char *)(DAT_08013754 + 3) != '\0') {
    bVar2 = FUN_080165a8();
    cVar3 = FUN_080165b8();
    cVar4 = FUN_080165c8();
    cVar5 = FUN_080165d8();
    cVar6 = FUN_080165e8();
    cVar7 = FUN_080165f8();
    local_20._0_1_ =
         ~(bVar2 | cVar3 << 1 | cVar4 << 2 | cVar5 << 3 | cVar6 << 4 | cVar7 << 5) & 0x3f;
LAB_08013750:
    *pbVar1 = (byte)local_20;
    return;
  }
  if (*(char *)(DAT_08013754 + 5) == '\x01') {
    if (*DAT_08013758 != 0xfe) {
      return;
    }
    do {
      local_1c = local_1c & 0xffffff00;
      while ((byte)local_1c < 3) {
        FUN_08012330(0x48,(int)&local_20 + (local_1c & 0xff),1);
        local_1c = CONCAT31(local_1c._1_3_,(byte)local_1c + '\x01');
      }
    } while (((local_20 & 0xff) != (uint)local_20._1_1_) || (local_20._1_1_ != local_20._2_1_));
    if ((byte)local_20 < 0x65) goto LAB_08013750;
  }
  *pbVar1 = 1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801375c at 0x0801375c
// ---------------------------------------------------------------------------

void FUN_0801375c(void)

{
  byte bVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined2 uVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  float *pfVar9;
  uint in_fpscr;
  float fVar10;
  float fVar11;
  float fVar12;
  uint local_30;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined1 local_2a;
  undefined1 local_29;
  ushort local_28;
  
  iVar2 = DAT_080139d8;
  local_28 = 0;
  *(undefined4 *)(DAT_080139d8 + 8) = 0xffffff;
  *(undefined4 *)(iVar2 + 0xc) = 0xffffff;
  *(undefined4 *)(iVar2 + 4) = 0xffffff;
  uVar5 = FUN_08018768(0xa8);
  pfVar9 = (float *)(iVar2 + -0x20);
  *(undefined4 *)(iVar2 + -0x14) = uVar5;
  fVar11 = DAT_080139e0;
  puVar3 = DAT_080139dc;
  if (*(int *)(iVar2 + -0x14) == 0xffff) {
    fVar10 = (float)VectorUnsignedToFloat(*DAT_080139dc,(byte)(in_fpscr >> 0x16) & 3);
    *pfVar9 = fVar10;
    fVar10 = (float)VectorUnsignedToFloat(*puVar3,(byte)(in_fpscr >> 0x16) & 3);
    *(int *)(iVar2 + -0x18) = (int)(fVar10 * 0.75);
    uVar5 = VectorFloatToUnsigned(*pfVar9 / fVar11,3);
    *(undefined4 *)(iVar2 + -0x1c) = uVar5;
    *(undefined1 *)(iVar2 + -0xe) = 0x96;
    *(undefined1 *)(iVar2 + -0xd) = 0x96;
    *(undefined2 *)(iVar2 + -0x10) = 0;
    *(undefined4 *)(iVar2 + -0x14) = 1;
    *(undefined2 *)(iVar2 + 0x20) = 0;
    *(undefined2 *)(iVar2 + 0x22) = 0;
    puVar3 = DAT_080139e8;
    *(undefined4 *)(iVar2 + 0x28) = *DAT_080139e4;
    *(undefined4 *)(iVar2 + 0x2c) = *puVar3;
    *(undefined4 *)(iVar2 + 0x30) = DAT_080139ec;
    *(undefined4 *)(iVar2 + 0x34) = DAT_080139f0;
    *(undefined4 *)(iVar2 + 0x38) = DAT_080139f4;
    FUN_0801975c();
    goto LAB_080139b6;
  }
  uVar6 = FUN_08018768(0xaa);
  *(uint *)(iVar2 + -0x14) = uVar6 | *(int *)(iVar2 + -0x14) << 0x10;
  local_28 = FUN_08018768(0xa0);
  if (local_28 == 0xffff) {
LAB_0801388c:
    fVar10 = (float)VectorUnsignedToFloat(*puVar3,(byte)(in_fpscr >> 0x16) & 3);
    *pfVar9 = fVar10;
    uVar5 = VectorFloatToUnsigned(*pfVar9 / fVar11,3);
    *(undefined4 *)(iVar2 + -0x1c) = uVar5;
  }
  else {
    uVar6 = (uint)local_28;
    uVar7 = FUN_08018768(0xa2);
    fVar10 = (float)VectorUnsignedToFloat(uVar7 | uVar6 << 0x10,(byte)(in_fpscr >> 0x16) & 3);
    *pfVar9 = fVar10;
    uVar5 = FUN_08018768(0xae);
    *(undefined4 *)(iVar2 + -0x1c) = uVar5;
    fVar12 = *pfVar9;
    fVar10 = (float)VectorUnsignedToFloat
                              ((*DAT_080139f8 + 100) * *(int *)(iVar2 + -0x1c),
                               (byte)(in_fpscr >> 0x16) & 3);
    uVar6 = in_fpscr & 0xfffffff | (uint)(fVar12 < fVar10) << 0x1f |
            (uint)(fVar12 == fVar10) << 0x1e;
    in_fpscr = uVar6 | (uint)(NAN(fVar12) || NAN(fVar10)) << 0x1c;
    bVar1 = (byte)(uVar6 >> 0x18);
    if (!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) goto LAB_0801388c;
    if (((int)*pfVar9 < DAT_080139fc) || (*(uint *)(iVar2 + -0x1c) < 2)) goto LAB_0801388c;
  }
  local_28 = FUN_08018768(0xa6);
  if (local_28 == 0xffff) {
LAB_080138f0:
    *(int *)(iVar2 + -0x18) = (int)(*pfVar9 * 0.75);
  }
  else {
    *(uint *)(iVar2 + -0x18) = (uint)local_28;
    iVar8 = FUN_08018768(0xa4);
    *(uint *)(iVar2 + -0x18) = *(uint *)(iVar2 + -0x18) | iVar8 << 0x10;
    fVar11 = (float)VectorSignedToFloat(*(undefined4 *)(iVar2 + -0x18),(byte)(in_fpscr >> 0x16) & 3)
    ;
    if (*pfVar9 < fVar11) goto LAB_080138f0;
  }
  uVar4 = FUN_08018768(0xac);
  *(undefined2 *)(iVar2 + -0x10) = uVar4;
  if (*(short *)(iVar2 + -0x10) == -1) {
    *(undefined2 *)(iVar2 + -0x10) = 0;
  }
  uVar4 = FUN_08018768(0xb0);
  *(undefined2 *)(iVar2 + 0x20) = uVar4;
  if (*(short *)(iVar2 + 0x20) == -1) {
    *(undefined2 *)(iVar2 + 0x20) = 0;
  }
  uVar4 = FUN_08018768(0xb2);
  *(undefined2 *)(iVar2 + 0x22) = uVar4;
  if (*(short *)(iVar2 + 0x22) == -1) {
    *(undefined2 *)(iVar2 + 0x22) = 0;
  }
  FUN_08012330(0x1ec,&local_2c,4);
  local_30 = CONCAT31(CONCAT21(CONCAT11(local_2c,local_2b),local_2a),local_29);
  if (0x3fffff < local_30) {
    local_30 = 0;
  }
  *(uint *)(iVar2 + 0x50) = local_30;
  FUN_08012330(0x1f0,&local_2c,4);
  local_30 = CONCAT31(CONCAT21(CONCAT11(local_2c,local_2b),local_2a),local_29);
  if (0x3fffff < local_30) {
    local_30 = 0;
  }
  *(uint *)(iVar2 + 0x54) = local_30;
LAB_080139b6:
  FUN_08014824();
  uVar5 = DAT_08013a00;
  iVar2 = DAT_080139d8;
  *(undefined4 *)(DAT_080139d8 + 0x84) = DAT_08013a00;
  *(undefined4 *)(iVar2 + 0x88) = uVar5;
  FUN_0800b460();
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08013a04 at 0x08013a04
// ---------------------------------------------------------------------------

void FUN_08013a04(void)

{
  byte *pbVar1;
  byte *pbVar2;
  char cVar3;
  char local_48 [32];
  ushort local_28;
  int local_24;
  
  if (*DAT_08013b2c != '\x01') {
    return;
  }
  if ((*DAT_08013b30 == 0x200) || (*DAT_08013b30 == 0x100)) {
    local_24 = *DAT_08013b34;
  }
  else {
    local_24 = DAT_08013b38;
  }
  for (local_28 = 0; local_28 < 4; local_28 = local_28 + 1) {
    local_48[local_28] = *(char *)(local_24 + (uint)local_28 + 0x28a);
  }
  cVar3 = FUN_08016658(local_48,3);
  pbVar2 = DAT_08013b44;
  pbVar1 = DAT_08013b3c;
  if (cVar3 != local_48[3]) {
    if (*DAT_08013b40 == 0x464) {
      local_48[0] = '\x18';
    }
    if (*DAT_08013b40 == 0x45d) {
      local_48[0] = '\x11';
    }
    if (*DAT_08013b40 == 0x45a) {
      local_48[0] = '\x0e';
    }
    local_48[1] = *DAT_08013b3c;
    local_48[2] = 0;
    local_48[3] = FUN_08016658(local_48,3);
    FUN_0800f850(0x28a,local_48,4);
    return;
  }
  if (local_48[0] == '\x0e') {
    *DAT_08013b40 = 0x45a;
    if (0xe < (byte)local_48[1]) {
LAB_08013ae2:
      *pbVar2 = 0xe;
      *pbVar1 = 0xe;
      return;
    }
  }
  else if (local_48[0] == '\x11') {
    *DAT_08013b40 = 0x45d;
    if (0x11 < (byte)local_48[1]) {
      local_48[1] = 0x11;
      *pbVar2 = 0x11;
      goto LAB_08013ad4;
    }
  }
  else {
    if (local_48[0] != '\x18') {
      *DAT_08013b40 = 0x45a;
      goto LAB_08013ae2;
    }
    *DAT_08013b40 = 0x464;
    if (0x18 < (byte)local_48[1]) {
      *pbVar2 = 0x18;
      *pbVar1 = 0x18;
      return;
    }
  }
  *pbVar2 = local_48[1];
LAB_08013ad4:
  *pbVar1 = local_48[1];
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08013b48 at 0x08013b48
// ---------------------------------------------------------------------------

void FUN_08013b48(void)

{
  short sVar1;
  float fVar2;
  float fVar3;
  char cVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  uint in_fpscr;
  float fVar8;
  float fVar9;
  byte local_18;
  char local_14 [16];
  
  sVar1 = *DAT_08013d38;
  if ((sVar1 == 0x200) || (*DAT_08013d38 == 0x100)) {
    iVar5 = *DAT_08013d3c;
  }
  else {
    iVar5 = DAT_08013d40;
  }
  piVar7 = DAT_08013d3c;
  for (local_18 = 0; local_18 < 0x10; local_18 = local_18 + 1) {
    piVar7 = (int *)(uint)local_18;
    local_14[(int)piVar7] = *(char *)(iVar5 + (uint)local_18 + 0x29b);
  }
  cVar4 = FUN_08016658(local_14,0xf,piVar7,sVar1,0);
  if (cVar4 == local_14[0xf]) {
    *DAT_08013d44 = local_14[0];
    *DAT_08013d48 = local_14[1];
    *DAT_08013d4c = local_14[2];
    *DAT_08013d50 = local_14[3];
    *DAT_08013d54 = local_14[4];
    fVar3 = DAT_08013d60;
    fVar2 = DAT_08013d5c;
    fVar9 = (float)VectorUnsignedToFloat
                             (CONCAT11(local_14[5],local_14[6]) & 0x7fff,
                              (byte)(in_fpscr >> 0x16) & 3);
    fVar8 = DAT_08013d60;
    if ((int)((uint)CONCAT11(local_14[5],local_14[6]) << 0x10) < 0) {
      fVar8 = DAT_08013d5c;
    }
    *DAT_08013d58 = fVar9 / fVar8;
    fVar9 = (float)VectorUnsignedToFloat
                             (CONCAT11(local_14[7],local_14[8]) & 0x7fff,
                              (byte)(in_fpscr >> 0x16) & 3);
    fVar8 = fVar3;
    if ((int)((uint)CONCAT11(local_14[7],local_14[8]) << 0x10) < 0) {
      fVar8 = fVar2;
    }
    *DAT_08013d64 = fVar9 / fVar8;
    fVar9 = (float)VectorUnsignedToFloat
                             (CONCAT11(local_14[9],local_14[10]) & 0x7fff,
                              (byte)(in_fpscr >> 0x16) & 3);
    fVar8 = fVar3;
    if ((int)((uint)CONCAT11(local_14[9],local_14[10]) << 0x10) < 0) {
      fVar8 = fVar2;
    }
    *DAT_08013d68 = fVar9 / fVar8;
    fVar9 = (float)VectorUnsignedToFloat
                             (CONCAT11(local_14[0xb],local_14[0xc]) & 0x7fff,
                              (byte)(in_fpscr >> 0x16) & 3);
    fVar8 = fVar3;
    if ((int)((uint)CONCAT11(local_14[0xb],local_14[0xc]) << 0x10) < 0) {
      fVar8 = fVar2;
    }
    *DAT_08013d6c = fVar9 / fVar8;
    uVar6 = CONCAT11(local_14[0xd],local_14[0xe]) & 0x7fff;
    if ((int)((uint)CONCAT11(local_14[0xd],local_14[0xe]) << 0x10) < 0) {
      fVar8 = (float)VectorUnsignedToFloat(uVar6,(byte)(in_fpscr >> 0x16) & 3);
      fVar8 = fVar8 / fVar2;
    }
    else {
      fVar8 = (float)VectorUnsignedToFloat(uVar6,(byte)(in_fpscr >> 0x16) & 3);
      fVar8 = fVar8 / fVar3;
    }
    *DAT_08013d70 = fVar8;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08013f88 at 0x08013f88
// ---------------------------------------------------------------------------

void FUN_08013f88(void)

{
  uint in_r3;
  uint local_10;
  
  local_10 = in_r3 & 0xffff0000;
  FUN_08012330(0x18e,&local_10,2);
  if ((short)local_10 == 0x55aa) {
    *(undefined1 *)(DAT_08013fb4 + 2) = 0x11;
    return;
  }
  *(undefined1 *)(DAT_08013fb4 + 2) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08013fb8 at 0x08013fb8
// ---------------------------------------------------------------------------

void FUN_08013fb8(undefined4 param_1,uint param_2,uint param_3)

{
  char cVar1;
  uint in_fpscr;
  float fVar2;
  undefined4 local_10;
  uint local_c;
  int local_8;
  
  if ((*DAT_08014044 == 0x200) || (*DAT_08014044 == 0x100)) {
    local_8 = *DAT_08014048;
  }
  else {
    local_8 = DAT_0801404c;
  }
  local_c = param_3 & 0xffffff00;
  local_10 = param_2;
  while ((byte)local_c < 3) {
    *(undefined1 *)((int)&local_10 + (local_c & 0xff)) =
         *(undefined1 *)(local_8 + (local_c & 0xff) + 0x298);
    local_c = CONCAT31(local_c._1_3_,(byte)local_c + '\x01');
  }
  cVar1 = FUN_08016658(&local_10,2);
  if (cVar1 == local_10._2_1_) {
    fVar2 = (float)VectorUnsignedToFloat
                             (local_10 >> 8 & 0xff | (local_10 & 0xff) << 8,
                              (byte)(in_fpscr >> 0x16) & 3);
    *DAT_08014054 = fVar2 / DAT_08014050;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08014058 at 0x08014058
// ---------------------------------------------------------------------------

undefined4 FUN_08014058(void)

{
  return DAT_0801405c;
}



// ---------------------------------------------------------------------------
// Function: FUN_08014060 at 0x08014060
// ---------------------------------------------------------------------------

void FUN_08014060(void)

{
  ushort uVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  byte bVar6;
  uint uVar7;
  uint uVar8;
  uint local_20;
  uint local_18;
  
  for (bVar6 = 0; bVar6 < 10; bVar6 = bVar6 + 1) {
    FUN_08012330(0xc0,DAT_080141c8,0x20);
    iVar4 = FUN_08018354(0x15b);
    iVar5 = FUN_0800ba48(DAT_080141c8,0x20);
    if (iVar4 == iVar5) break;
  }
  pbVar2 = DAT_080141c8;
  if (bVar6 == 10) {
    local_20 = 0;
    while ((byte)local_20 < 0x20) {
      pbVar2[local_20] = 0;
      local_20 = (uint)(byte)((byte)local_20 + 1);
    }
  }
  pbVar3 = DAT_080141c8;
  uVar1 = (ushort)*pbVar2;
  if (((int)((uint)uVar1 << 0x1a) < 0) && (uVar1 != 0xff)) {
    DAT_080141c8[-0xe0] = 1;
    if (((int)((uint)uVar1 << 0x19) < 0) && (uVar1 != 0xff)) {
      pbVar3[-0xdf] = 1;
      goto LAB_08014112;
    }
  }
  else {
    DAT_080141c8[-0xe0] = 0;
  }
  pbVar3[-0xdf] = 2;
LAB_08014112:
  pbVar3[-0xde] = pbVar2[0x14];
  pbVar3[-0xdd] = pbVar2[0x15];
  pbVar3[-0xdc] = pbVar2[0x16];
  pbVar3[-0xdb] = pbVar2[0x17];
  pbVar3[-0xda] = pbVar2[0x18];
  pbVar3[-0xd9] = pbVar2[0x19];
  pbVar3[-0xd8] = pbVar2[0x1a];
  pbVar3[-0xd7] = pbVar2[0x1b];
  pbVar3[-0xd6] = pbVar2[0x1c];
  pbVar3[-0xd5] = pbVar2[0x1d];
  local_18 = (uint)CONCAT11(pbVar2[0x1e],pbVar2[0x1f]);
  *(uint *)(pbVar3 + -0xd4) = local_18;
  uVar7 = (uint)pbVar3[-0xdd] * 0x1000000 + (uint)pbVar3[-0xdc] * 0x10000;
  uVar8 = uVar7 + (uint)pbVar3[-0xdb] * 0x100;
  *(uint *)(pbVar3 + -0xd0) = uVar8 + pbVar3[-0xda];
  *(uint *)(pbVar3 + -0xcc) =
       (uint)pbVar3[-0xde] +
       (uint)CARRY4((uint)pbVar3[-0xdd] * 0x1000000,(uint)pbVar3[-0xdc] * 0x10000) +
       (uint)CARRY4(uVar7,(uint)pbVar3[-0xdb] * 0x100) + (uint)CARRY4(uVar8,(uint)pbVar3[-0xda]);
  uVar7 = (uint)pbVar3[-0xd8] * 0x1000000 + (uint)pbVar3[-0xd7] * 0x10000;
  uVar8 = uVar7 + (uint)pbVar3[-0xd6] * 0x100;
  *(uint *)(pbVar3 + -200) = uVar8 + pbVar3[-0xd5];
  *(uint *)(pbVar3 + -0xc4) =
       (uint)pbVar3[-0xd9] +
       (uint)CARRY4((uint)pbVar3[-0xd8] * 0x1000000,(uint)pbVar3[-0xd7] * 0x10000) +
       (uint)CARRY4(uVar7,(uint)pbVar3[-0xd6] * 0x100) + (uint)CARRY4(uVar8,(uint)pbVar3[-0xd5]);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080141cc at 0x080141cc
// ---------------------------------------------------------------------------

void FUN_080141cc(void)

{
  undefined1 *puVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  byte bVar6;
  undefined4 uVar7;
  char *pcVar8;
  float *pfVar9;
  float *pfVar10;
  uint in_fpscr;
  undefined8 uVar11;
  undefined4 uVar12;
  undefined8 unaff_d8;
  undefined8 uVar13;
  ushort uVar14;
  short sVar15;
  undefined2 uVar16;
  undefined4 uStack_28;
  
  uVar7 = (undefined4)unaff_d8;
  uStack_28 = (undefined4)((ulonglong)unaff_d8 >> 0x20);
  for (bVar6 = 0; uVar16 = (undefined2)uVar7, bVar6 < 10; bVar6 = bVar6 + 1) {
    FUN_08012330(0x120,DAT_0801454c,0x1e);
    iVar3 = FUN_08018354(0x15e);
    iVar4 = FUN_0800ba48(DAT_0801454c,0x1e);
    uVar16 = (undefined2)uVar7;
    if (iVar3 == iVar4) break;
  }
  iVar3 = DAT_08014550;
  puVar1 = DAT_0801454c;
  if (bVar6 == 10) {
    iVar4 = *(int *)(DAT_08014550 + 0x60);
    for (bVar6 = 0; bVar6 < 0x1e; bVar6 = bVar6 + 1) {
      puVar1[bVar6] = *(undefined1 *)(iVar4 + (uint)bVar6);
    }
  }
  pfVar9 = DAT_08014554;
  uVar14 = CONCAT11(*puVar1,puVar1[1]);
  pfVar10 = DAT_08014554 + 0x13;
  if (((puVar1[1] & 1) == 0) || (uVar14 == 0xffff)) {
    *(undefined1 *)(DAT_08014554 + 0x3c) = 0;
    puVar1[1] = puVar1[1] & 0xfe;
    fVar5 = (float)VectorUnsignedToFloat((uint)*(byte *)(iVar3 + 9),(byte)(in_fpscr >> 0x16) & 3);
    pfVar9[6] = *pfVar9 * fVar5;
    fVar5 = (float)VectorUnsignedToFloat((uint)*(byte *)(iVar3 + 9),(byte)(in_fpscr >> 0x16) & 3);
    pfVar9[7] = pfVar9[1] * fVar5;
    fVar5 = (float)VectorUnsignedToFloat((uint)*(byte *)(iVar3 + 9),(byte)(in_fpscr >> 0x16) & 3);
    pfVar9[0x19] = *pfVar10 * fVar5;
    fVar5 = (float)VectorUnsignedToFloat((uint)*(byte *)(iVar3 + 9),(byte)(in_fpscr >> 0x16) & 3);
    pfVar9[0x1a] = pfVar9[0x14] * fVar5;
    *(undefined2 *)(pfVar9 + 8) = *(undefined2 *)(pfVar9 + 2);
    *(undefined2 *)(pfVar9 + 0x1b) = *(undefined2 *)(pfVar9 + 0x15);
    *(undefined2 *)((int)pfVar9 + 0x22) = 5000;
    *(undefined2 *)((int)pfVar9 + 0x6e) = 5000;
  }
  else {
    *(undefined1 *)(DAT_08014554 + 0x3c) = 1;
    uVar13 = FUN_08008548(CONCAT11(puVar1[2],puVar1[3]));
    uVar7 = (undefined4)((ulonglong)DAT_08014558 >> 0x20);
    uVar12 = (undefined4)DAT_08014558;
    FUN_08008448((int)uVar13,(int)((ulonglong)uVar13 >> 0x20),uVar12,uVar7);
    fVar5 = (float)FUN_08008658();
    pfVar9[6] = fVar5;
    uVar13 = FUN_08008548(CONCAT11(puVar1[4],puVar1[5]));
    FUN_08008448((int)uVar13,(int)((ulonglong)uVar13 >> 0x20),uVar12,uVar7);
    fVar5 = (float)FUN_08008658();
    pfVar9[7] = fVar5;
    uVar13 = FUN_08008548(CONCAT11(puVar1[6],puVar1[7]));
    FUN_08008448((int)uVar13,(int)((ulonglong)uVar13 >> 0x20),uVar12,uVar7);
    fVar5 = (float)FUN_08008658();
    pfVar9[0x19] = fVar5;
    uVar13 = FUN_08008548(CONCAT11(puVar1[8],puVar1[9]));
    FUN_08008448((int)uVar13,(int)((ulonglong)uVar13 >> 0x20),uVar12,uVar7);
    fVar5 = (float)FUN_08008658();
    pfVar9[0x1a] = fVar5;
    *(ushort *)(pfVar9 + 8) = ((byte)puVar1[10] & 0x7f) * 100;
    *(ushort *)(pfVar9 + 0x1b) = ((byte)puVar1[0xb] & 0x7f) * 100;
    *(ushort *)((int)pfVar9 + 0x22) = ((byte)puVar1[0x12] + 1) * 1000;
    *(ushort *)((int)pfVar9 + 0x6e) = ((byte)puVar1[0x13] + 1) * 1000;
  }
  pfVar10 = DAT_08014554;
  sVar15 = CONCAT11(puVar1[0xd],puVar1[0xe]);
  if (sVar15 == -1) {
    *(undefined1 *)(DAT_08014554 + 0x2b) = 0;
    *(undefined1 *)((int)pfVar10 + 0xad) = 10;
    *(undefined1 *)((int)pfVar10 + 0xae) = 0;
    puVar1[0xc] = 9;
    puVar1[0xd] = 0;
  }
  else {
    *(undefined1 *)(DAT_08014554 + 0x2b) = 1;
    *(char *)((int)pfVar10 + 0xad) = puVar1[0xc] + '\x01';
    *(undefined1 *)((int)pfVar10 + 0xae) = puVar1[0xd];
  }
  if (((int)((uint)uVar14 << 0x1e) < 0) && (uVar14 != 0xffff)) {
    *(undefined1 *)((int)pfVar10 + 0xaf) = 1;
  }
  else {
    *(undefined1 *)((int)pfVar10 + 0xaf) = 0;
    puVar1[1] = puVar1[1] & 0xfd;
  }
  if (((int)((uint)uVar14 << 0x1d) < 0) && (uVar14 != 0xffff)) {
    *(undefined1 *)(pfVar10 + 0x2c) = 1;
    *(char *)((int)pfVar10 + 0xb1) = puVar1[0xe] + '\x01';
    *(undefined1 *)((int)pfVar10 + 0xb2) = puVar1[0xf];
  }
  else {
    *(undefined1 *)(pfVar10 + 0x2c) = 0;
    puVar1[1] = puVar1[1] & 0xfb;
  }
  if (((int)((uint)uVar14 << 0x1c) < 0) && (uVar14 != 0xffff)) {
    *(undefined1 *)((int)pfVar10 + 0xb3) = 1;
  }
  else {
    *(undefined1 *)((int)pfVar10 + 0xb3) = 0;
    puVar1[1] = puVar1[1] & 0xf7;
  }
  pfVar2 = DAT_08014554;
  if (((int)((uint)uVar14 << 0x1b) < 0) && (uVar14 != 0xffff)) {
    *(undefined1 *)((int)DAT_08014554 + -0x6a) = 1;
    *(ushort *)(pfVar2 + -0x1b) = ((byte)puVar1[0x10] + 1) * 0xf;
  }
  else {
    *(undefined1 *)((int)DAT_08014554 + -0x6a) = 0;
    puVar1[1] = puVar1[1] & 0xef;
  }
  if ((((int)((uint)uVar14 << 0x1a) < 0) && (uVar14 != 0xffff)) && (*(char *)(iVar3 + 8) != '\0')) {
    *(undefined1 *)((int)pfVar9 + 0x11a) = 1;
    *(char *)((int)pfVar10 + 0xce) = puVar1[0x11] + '\x01';
  }
  else {
    *(undefined1 *)((int)pfVar9 + 0x11a) = 0;
    *(undefined1 *)((int)pfVar10 + 0xce) = 0;
    puVar1[1] = puVar1[1] & 0xdf;
    puVar1[0x11] = 0;
    FUN_0800acd8();
  }
  iVar4 = DAT_08013f5c;
  iVar3 = DAT_08013f58;
  uVar14 = (ushort)*(byte *)(DAT_08013f58 + 0x14);
  pfVar9 = (float *)(DAT_08013f58 + -0x274);
  pcVar8 = (char *)(DAT_08013f58 + -0x20);
  if (uVar14 == 0xff) {
    *(float *)(DAT_08013f58 + -0x228) = *pfVar9;
    *(undefined4 *)(iVar3 + -0x224) = 10;
    *(undefined2 *)(iVar3 + -0x2da) = 0x5a;
    *(undefined2 *)(iVar3 + -0x2d8) = 0x46;
    *(undefined2 *)(iVar3 + -0x2d6) = 5;
    if ((int)*pfVar9 < 0x40000001) {
      *(undefined1 *)(iVar3 + 0x14) = 0;
    }
    else {
      uVar7 = VectorFloatToUnsigned((*pfVar9 - 2.0) * 20.0,3);
      *(char *)(iVar3 + 0x14) = (char)uVar7;
    }
    *(undefined1 *)(iVar3 + 0x15) = 0;
    *(undefined1 *)(iVar3 + 0x16) = 10;
    *(char *)(iVar3 + 0x17) = (char)*(undefined2 *)(iVar3 + -0x2da) + -1;
    *(char *)(iVar3 + 0x18) = (char)*(undefined2 *)(iVar3 + -0x2d8) + '\x01';
    *(undefined2 *)(iVar3 + -0x2d6) = 1;
    *(undefined1 *)(iVar3 + 0x19) = 1;
    *(undefined4 *)(iVar4 + 0x40) = 0x3f800000;
    *pcVar8 = '\n';
  }
  else {
    uVar12 = (undefined4)DAT_08013f60;
    uVar7 = (undefined4)((ulonglong)DAT_08013f60 >> 0x20);
    if (uVar14 < 0x3d) {
      uVar13 = FUN_08008548();
      uVar13 = FUN_08008448((int)uVar13,(int)((ulonglong)uVar13 >> 0x20),uVar12,uVar7,uVar14,sVar15,
                            uVar16,uStack_28);
      uVar11 = DAT_08013f68;
    }
    else if (uVar14 < 0x47) {
      uVar13 = FUN_08008526(uVar14 - 0x3c);
      uVar13 = FUN_08008448((int)uVar13,(int)((ulonglong)uVar13 >> 0x20),uVar12,uVar7);
      uVar11 = DAT_08013f70;
    }
    else {
      uVar13 = FUN_08008526(uVar14 - 0x46);
      uVar13 = FUN_08008448((int)uVar13,(int)((ulonglong)uVar13 >> 0x20),uVar12,uVar7);
      uVar11 = DAT_08013f78;
    }
    FUN_08008216((int)uVar13,(int)((ulonglong)uVar13 >> 0x20),(int)uVar11,
                 (int)((ulonglong)uVar11 >> 0x20));
    uVar7 = FUN_08008658();
    *(undefined4 *)(iVar3 + -0x228) = uVar7;
    if ((*pcVar8 == '\0') || (*pcVar8 == -1)) {
      *(undefined4 *)(iVar4 + 0x40) = 0x3f800000;
      *pcVar8 = '\n';
    }
    else {
      uVar13 = FUN_08008548(*pcVar8);
      FUN_08008364((int)uVar13,(int)((ulonglong)uVar13 >> 0x20),(int)DAT_08013f80,
                   (int)((ulonglong)DAT_08013f80 >> 0x20));
      uVar7 = FUN_08008658();
      *(undefined4 *)(iVar4 + 0x40) = uVar7;
    }
    *(uint *)(iVar3 + -0x224) =
         (uint)CONCAT11(*(undefined1 *)(iVar3 + 0x15),*(undefined1 *)(iVar3 + 0x16));
    *(ushort *)(iVar3 + -0x2da) = *(byte *)(iVar3 + 0x17) + 1;
    *(ushort *)(iVar3 + -0x2d8) = *(byte *)(iVar3 + 0x18) + 1;
    *(ushort *)(iVar3 + -0x2d6) = *(byte *)(iVar3 + 0x19) + 1;
  }
  if (*(byte *)(iVar3 + -5) == 0xff) {
    *(undefined2 *)(iVar3 + -0x2ce) = 0x46;
    *(undefined2 *)(iVar3 + -0x2cc) = 0x41;
    *(undefined2 *)(iVar3 + -0x2ca) = 0xffe7;
    *(undefined2 *)(iVar3 + -0x2c8) = 0xffec;
    *(char *)(iVar3 + -5) = (char)*(undefined2 *)(iVar3 + -0x2ce) + -0x1e;
    *(char *)(iVar3 + -4) = (char)*(undefined2 *)(iVar3 + -0x2cc) + -0x1e;
    *(char *)(iVar3 + -3) = (char)*(undefined2 *)(iVar3 + -0x2ca) + '(';
    *(char *)(iVar3 + -2) = (char)*(undefined2 *)(iVar3 + -0x2c8) + '(';
  }
  else {
    *(ushort *)(iVar3 + -0x2ce) = *(byte *)(iVar3 + -5) + 0x1e;
    *(ushort *)(iVar3 + -0x2cc) = *(byte *)(iVar3 + -4) + 0x1e;
    *(ushort *)(iVar3 + -0x2ca) = *(byte *)(iVar3 + -3) - 0x28;
    *(ushort *)(iVar3 + -0x2c8) = *(byte *)(iVar3 + -2) - 0x28;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08014560 at 0x08014560
// ---------------------------------------------------------------------------

void FUN_08014560(void)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  undefined2 *puVar5;
  undefined4 *puVar6;
  float fVar7;
  uint in_fpscr;
  float fVar8;
  uint local_c;
  
  puVar1 = DAT_08014678;
  *DAT_0801467c = *DAT_08014678;
  puVar2 = DAT_08014680;
  if (puVar1[2] == '\0') {
    *DAT_08014680 = 0;
  }
  else {
    *DAT_08014680 = puVar1[1];
  }
  puVar3 = DAT_08014684;
  *DAT_08014684 = puVar1[3];
  puVar5 = DAT_0801468c;
  uVar4 = DAT_08014688;
  if (puVar1[2] != '\0') {
    *(undefined2 *)(puVar2 + 2) = *DAT_0801468c;
    *(undefined2 *)(puVar2 + 4) = puVar5[1];
    *(undefined2 *)(puVar2 + 6) = puVar5[2];
    *(undefined2 *)(puVar2 + 8) = puVar5[3];
    *(undefined2 *)(puVar2 + 10) = puVar5[4];
    *(undefined2 *)(puVar2 + 0xc) = puVar5[5];
    puVar6 = DAT_08014690;
    *(undefined4 *)(puVar2 + 0x10) = *DAT_08014690;
    *(undefined4 *)(puVar2 + 0x14) = puVar6[1];
    *(undefined4 *)(puVar2 + 0x18) = puVar6[2];
    *(undefined4 *)(puVar2 + 0x1c) = puVar6[3];
    *(undefined4 *)(puVar2 + 0x20) = puVar6[4];
    *(undefined4 *)(puVar2 + 0x24) = puVar6[5];
    fVar7 = DAT_08014694;
    local_c = 0;
    while ((byte)local_c < 5) {
      if (*(short *)(puVar2 + local_c * 2 + 4) == *(short *)(puVar2 + local_c * 2 + 2)) {
        *(undefined4 *)(puVar2 + local_c * 4 + 0x28) = uVar4;
      }
      else {
        fVar8 = (float)VectorSignedToFloat((int)*(short *)(puVar2 + local_c * 2 + 4) -
                                           (int)*(short *)(puVar2 + local_c * 2 + 2),
                                           (byte)(in_fpscr >> 0x16) & 3);
        *(float *)(puVar2 + local_c * 4 + 0x28) =
             ((*(float *)(puVar2 + local_c * 4 + 0x14) - *(float *)(puVar2 + local_c * 4 + 0x10)) /
             fVar7) / fVar8;
      }
      local_c = (uint)(byte)((byte)local_c + 1);
    }
  }
  *(undefined4 *)(puVar3 + 0xc) = uVar4;
  *(undefined4 *)(puVar3 + 8) = uVar4;
  puVar3[7] = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08014698 at 0x08014698
// ---------------------------------------------------------------------------

void FUN_08014698(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  FUN_0800a634();
  FUN_08015b28(1,0x2580);
  FUN_08015b28(2,0x2580);
  FUN_08015b28(4,0x2580);
  iVar1 = DAT_080146e4;
  *(undefined4 *)(DAT_080146e4 + 0x10) = 0x20;
  *(undefined4 *)(iVar1 + 0x14) = 1;
  *(undefined4 *)(iVar1 + 0x14) = 0x80;
  *(int *)(iVar1 + 0x14) = iVar1 >> 0x12;
  puVar2 = DAT_080146e8;
  *DAT_080146e8 = 0x10;
  *DAT_080146ec = 0x8000;
  *puVar2 = 8;
  *DAT_080146f0 = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080146f4 at 0x080146f4
// ---------------------------------------------------------------------------

void FUN_080146f4(void)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  
  puVar1 = DAT_0801480c;
  *DAT_0801480c = 0;
  puVar1[1] = 0;
  puVar1[2] = 0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[5] = 0;
  puVar1[6] = 0;
  puVar1[7] = 0;
  puVar1[8] = 0;
  puVar1[9] = 0;
  puVar1[10] = 0;
  puVar1[0xb] = 0;
  puVar1[0xc] = 0;
  puVar1[0xd] = 0;
  puVar1[0xe] = 0;
  puVar1[0x12] = 0;
  puVar1[0x13] = 0;
  puVar1[0x14] = 0;
  puVar1[0x15] = 0;
  puVar1[0x16] = 0;
  puVar1[0x17] = 0;
  puVar1[0x18] = 0;
  puVar1[0x19] = 0;
  puVar1[0x1a] = 0;
  puVar1[0x1b] = 0;
  puVar1[0x1c] = 0;
  puVar1[0x1d] = 0;
  puVar1[0x1e] = 0;
  puVar1[0x1f] = 0;
  puVar1[0x21] = 0;
  puVar1[0x22] = 0;
  puVar1[0x23] = 0;
  puVar1[0x24] = 0;
  puVar1[0x25] = 0;
  puVar1[0x26] = 0;
  puVar1[0x27] = 0;
  puVar1[0x28] = 0;
  puVar1[0x29] = 0;
  puVar1[0x2a] = 0;
  puVar1[0x2b] = 0;
  puVar1[0x2c] = 0;
  puVar1[0x2d] = 0;
  puVar1[0x2e] = 0;
  puVar1[0x39] = 0;
  puVar1[0x3a] = 0;
  puVar1[0x3b] = 0;
  puVar1[0x3c] = 0;
  puVar1[0x3d] = 0;
  puVar1[0x3e] = 0;
  puVar1[0x3f] = 0;
  puVar1[0x40] = 0;
  puVar1[0x41] = 0;
  puVar1[0x42] = 0;
  puVar1[0x43] = 0;
  puVar1[0x44] = 0;
  puVar1[0x45] = 0;
  puVar1[0x46] = 0;
  puVar1[0x47] = 0;
  puVar1[0x48] = 0;
  puVar1[0x49] = 0;
  puVar2 = DAT_08014810;
  *DAT_08014810 = 0;
  *(undefined4 *)(puVar2 + 4) = 0;
  puVar1[0x2f] = 0;
  puVar1[0x34] = 0;
  iVar3 = DAT_08014818;
  *(undefined4 *)(DAT_08014818 + 0x44) = DAT_08014814;
  puVar1[0x51] = 0;
  puVar1[0x10] = 0;
  puVar1[0x4b] = 0;
  *(undefined1 *)(iVar3 + 0x4c) = 0;
  puVar1[0x11] = 0;
  puVar1 = DAT_08014810;
  *(undefined2 *)(DAT_08014810 + -0x62) = 0x9249;
  *(undefined2 *)(puVar1 + -0x60) = 0x2492;
  *(undefined2 *)(puVar1 + -0x5e) = 0x4924;
  *(undefined2 *)(puVar1 + -0x5c) = 0x9249;
  *(undefined2 *)(puVar1 + -0x5a) = 0x2492;
  *(undefined2 *)(puVar1 + -0x58) = 0x4924;
  uVar5 = FUN_08015ef4();
  *(undefined4 *)(puVar1 + -0x24) = uVar5;
  uVar5 = FUN_08014058();
  *(undefined4 *)(puVar1 + -0x20) = uVar5;
  uVar5 = FUN_0801583c();
  puVar4 = DAT_08014820;
  *(undefined4 *)(puVar1 + -0x1c) = uVar5;
  *puVar4 = DAT_0801481c;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08014824 at 0x08014824
// ---------------------------------------------------------------------------

void FUN_08014824(void)

{
  byte *pbVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  byte bVar8;
  byte *pbVar9;
  uint in_fpscr;
  undefined4 uVar10;
  float fVar11;
  uint local_18;
  
  for (bVar8 = 0; bVar8 < 10; bVar8 = bVar8 + 1) {
    FUN_08012330(0xb4,DAT_08014af4,0xb);
    iVar7 = FUN_08018354(0x15c);
    iVar6 = FUN_0800ba48(DAT_08014af4,0xb);
    if (iVar7 == iVar6) break;
  }
  pbVar1 = DAT_08014af4;
  if (bVar8 == 10) {
    local_18 = 0;
    iVar7 = *DAT_08014af8;
    while ((byte)local_18 < 0xb) {
      pbVar1[local_18] = *(byte *)(iVar7 + local_18);
      local_18 = (uint)(byte)((byte)local_18 + 1);
    }
  }
  iVar7 = DAT_08014afc;
  *(ushort *)(DAT_08014afc + 0x10) = (ushort)*pbVar1;
  *(short *)(iVar7 + 0x10) = (short)CONCAT21(*(undefined2 *)(iVar7 + 0x10),pbVar1[1]);
  iVar2 = DAT_08014b04;
  iVar6 = DAT_08014b00;
  uVar10 = VectorUnsignedToFloat((uint)*(ushort *)(iVar7 + 0x10),(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(DAT_08014b00 + 0x28) = uVar10;
  pfVar3 = DAT_08014b0c;
  fVar11 = DAT_08014b08;
  pbVar9 = (byte *)(iVar7 + 0xe);
  if (*(int *)(iVar6 + 0x28) == iVar2) {
    *(float *)(iVar6 + 0x28) = *DAT_08014b0c;
    uVar10 = VectorFloatToUnsigned(*pfVar3 * fVar11,3);
    *(short *)(iVar7 + 0x10) = (short)uVar10;
    *pbVar9 = (byte)((ushort)*(undefined2 *)(iVar7 + 0x10) >> 8);
    *(char *)(iVar7 + 0xf) = (char)*(undefined2 *)(iVar7 + 0x10);
    *pbVar1 = *pbVar9;
    pbVar1[1] = *(byte *)(iVar7 + 0xf);
  }
  else {
    *(float *)(iVar6 + 0x28) = *(float *)(iVar6 + 0x28) / DAT_08014b08;
  }
  *(ushort *)(iVar7 + 0x10) = (ushort)pbVar1[2];
  *(short *)(iVar7 + 0x10) = (short)CONCAT21(*(undefined2 *)(iVar7 + 0x10),pbVar1[3]);
  uVar10 = VectorUnsignedToFloat((uint)*(ushort *)(iVar7 + 0x10),(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(iVar6 + 0x2c) = uVar10;
  pfVar3 = DAT_08014b10;
  if (*(int *)(iVar6 + 0x2c) == iVar2) {
    *(float *)(iVar6 + 0x2c) = *DAT_08014b10;
    uVar10 = VectorFloatToUnsigned(*pfVar3 * fVar11,3);
    *(short *)(iVar7 + 0x10) = (short)uVar10;
    *pbVar9 = (byte)((ushort)*(undefined2 *)(iVar7 + 0x10) >> 8);
    *(char *)(iVar7 + 0xf) = (char)*(undefined2 *)(iVar7 + 0x10);
    pbVar1[2] = *pbVar9;
    pbVar1[3] = *(byte *)(iVar7 + 0xf);
  }
  else {
    *(float *)(iVar6 + 0x2c) = *(float *)(iVar6 + 0x2c) / fVar11;
  }
  *(ushort *)(iVar7 + 0x10) = (ushort)pbVar1[4];
  *(short *)(iVar7 + 0x10) = (short)CONCAT21(*(undefined2 *)(iVar7 + 0x10),pbVar1[5]);
  uVar10 = VectorUnsignedToFloat((uint)*(ushort *)(iVar7 + 0x10),(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(iVar6 + 0x38) = uVar10;
  if (*(int *)(iVar6 + 0x38) == iVar2) {
    *(undefined4 *)(iVar6 + 0x38) = DAT_08014b14;
    *(undefined2 *)(iVar7 + 0x10) = 0x19;
    *pbVar9 = (byte)((ushort)*(undefined2 *)(iVar7 + 0x10) >> 8);
    *(char *)(iVar7 + 0xf) = (char)*(undefined2 *)(iVar7 + 0x10);
    pbVar1[4] = *pbVar9;
    pbVar1[5] = *(byte *)(iVar7 + 0xf);
  }
  else {
    *(float *)(iVar6 + 0x38) = *(float *)(iVar6 + 0x38) / DAT_08014b18;
  }
  *(ushort *)(iVar6 + 0x3c) = (ushort)pbVar1[10];
  if (*(short *)(iVar6 + 0x3c) == 0xff) {
    *(undefined2 *)(iVar6 + 0x3c) = 10;
    *pbVar9 = 10;
    pbVar1[10] = 10;
  }
  iVar4 = DAT_08014b20;
  iVar2 = DAT_08014b1c;
  uVar10 = VectorUnsignedToFloat((uint)*(byte *)(DAT_08014b1c + 0x1a),(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(iVar6 + 0x40) = uVar10;
  if (*(int *)(iVar6 + 0x40) < iVar4) {
    *(float *)(iVar6 + 0x40) = *(float *)(iVar6 + 0x40) / DAT_08014b28;
  }
  else {
    *(undefined4 *)(iVar6 + 0x40) = DAT_08014b24;
    *pbVar9 = 1;
    *(undefined1 *)(iVar2 + 0x1a) = 1;
  }
  iVar4 = DAT_08014b2c;
  uVar10 = VectorUnsignedToFloat((uint)*(byte *)(iVar2 + 0x1b),(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(iVar6 + 0x44) = uVar10;
  if ((*(int *)(iVar6 + 0x44) < iVar4) && (DAT_08014b30 <= *(int *)(iVar6 + 0x44))) {
    *(float *)(iVar6 + 0x44) = *(float *)(iVar6 + 0x44) / fVar11;
  }
  else {
    *(undefined4 *)(iVar6 + 0x44) = DAT_08014b34;
    *pbVar9 = 0x5a;
    *(undefined1 *)(iVar2 + 0x1b) = 0x5a;
  }
  *(ushort *)(iVar7 + 0x10) = (ushort)*(byte *)(iVar2 + 0x1c);
  *(short *)(iVar7 + 0x10) =
       (short)CONCAT21(*(undefined2 *)(iVar7 + 0x10),*(undefined1 *)(iVar2 + 0x1d));
  pbVar1 = DAT_08014b40;
  pcVar5 = DAT_08014b3c;
  iVar4 = DAT_08014b38;
  uVar10 = VectorUnsignedToFloat((uint)*(ushort *)(iVar7 + 0x10),(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(iVar6 + 0x48) = uVar10;
  if (*(int *)(iVar6 + 0x48) < iVar4) {
    *(float *)(iVar6 + 0x48) = *(float *)(iVar6 + 0x48) / DAT_08014b48;
    if (*pcVar5 != '\0') {
      fVar11 = (float)VectorUnsignedToFloat((uint)*pbVar1,(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(iVar6 + 0x48) = *(float *)(iVar6 + 0x48) * fVar11;
    }
  }
  else {
    fVar11 = DAT_08014b44;
    if (*pcVar5 != '\0') {
      fVar11 = (float)VectorUnsignedToFloat((uint)*pbVar1,(byte)(in_fpscr >> 0x16) & 3);
      fVar11 = fVar11 * DAT_08014b44;
    }
    *(float *)(iVar6 + 0x48) = fVar11;
    *pbVar9 = 0xb;
    *(undefined1 *)(iVar7 + 0xf) = 0x54;
    *(byte *)(iVar2 + 0x1c) = *pbVar9;
    *(undefined1 *)(iVar2 + 0x1d) = *(undefined1 *)(iVar7 + 0xf);
  }
  FUN_08014560();
  *(undefined4 *)(DAT_08014b4c + 0x4c) = *(undefined4 *)(DAT_08014b4c + 0x20);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08014b50 at 0x08014b50
// ---------------------------------------------------------------------------

void FUN_08014b50(void)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  short *psVar6;
  float *pfVar7;
  float fVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  ushort uVar12;
  uint in_fpscr;
  undefined4 uVar13;
  float fVar14;
  ushort local_68;
  char local_64 [32];
  char local_44;
  undefined1 local_43;
  undefined1 local_42;
  undefined1 local_41;
  undefined1 local_40;
  undefined1 local_3f;
  char local_3e;
  char local_3d;
  char local_3c;
  char local_3b;
  char local_3a;
  char local_39;
  undefined1 local_38;
  undefined1 local_37;
  undefined1 local_36;
  undefined1 local_35;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c;
  char local_24;
  
  if (*DAT_08014f4c == '\x01') {
    uVar12 = 0;
    local_24 = '\0';
    if ((*DAT_08014f50 == 0x200) || (*DAT_08014f50 == 0x100)) {
      iVar9 = *DAT_08014f54;
    }
    else {
      iVar9 = DAT_08014f58;
    }
    for (local_68 = 0; local_68 < 0x19; local_68 = local_68 + 1) {
      local_64[local_68] = *(char *)(iVar9 + (uint)local_68 + 0x180);
    }
    uVar10 = FUN_0800c0d0(local_64,0x18);
    for (local_68 = 0; local_68 < 0x17; local_68 = local_68 + 1) {
      local_64[local_68] = *(char *)(iVar9 + (uint)local_68 + 0x1a0);
    }
    uVar11 = FUN_0800c0d0(local_64,0x16);
    fVar8 = DAT_08014f7c;
    pfVar7 = DAT_08014f78;
    psVar6 = DAT_08014f74;
    puVar5 = DAT_08014f70;
    puVar4 = DAT_08014f6c;
    puVar3 = DAT_08014f68;
    puVar2 = DAT_08014f64;
    puVar1 = DAT_08014f60;
    if (uVar11 == (byte)local_64[0x16]) {
      local_24 = '\x01';
    }
    if (((uVar10 == (byte)local_64[0x18]) && (local_24 != '\0')) && (local_64[0] != -1)) {
      for (; uVar12 < 0x18; uVar12 = uVar12 + 1) {
        local_64[uVar12] = *(char *)(iVar9 + (uint)uVar12 + 0x180);
      }
      *DAT_08014f5c = local_64[0];
      *puVar1 = local_64[1];
      *puVar2 = local_64[2];
      *puVar3 = local_64[3];
      *puVar4 = local_64[4];
      *puVar5 = local_64[5];
      *psVar6 = (byte)local_64[6] - 0x28;
      psVar6[1] = (byte)local_64[7] - 0x28;
      psVar6[2] = (byte)local_64[8] - 0x28;
      psVar6[3] = (byte)local_64[9] - 0x28;
      psVar6[4] = (byte)local_64[10] - 0x28;
      psVar6[5] = (byte)local_64[0xb] - 0x28;
      fVar14 = (float)VectorUnsignedToFloat
                                ((uint)CONCAT11(local_64[0xc],local_64[0xd]),
                                 (byte)(in_fpscr >> 0x16) & 3);
      *pfVar7 = fVar14 / fVar8;
      fVar14 = (float)VectorUnsignedToFloat
                                ((uint)CONCAT11(local_64[0xe],local_64[0xf]),
                                 (byte)(in_fpscr >> 0x16) & 3);
      pfVar7[1] = fVar14 / fVar8;
      fVar14 = (float)VectorUnsignedToFloat
                                ((uint)CONCAT11(local_64[0x10],local_64[0x11]),
                                 (byte)(in_fpscr >> 0x16) & 3);
      pfVar7[2] = fVar14 / fVar8;
      fVar14 = (float)VectorUnsignedToFloat
                                ((uint)CONCAT11(local_64[0x12],local_64[0x13]),
                                 (byte)(in_fpscr >> 0x16) & 3);
      pfVar7[3] = fVar14 / fVar8;
      fVar14 = (float)VectorUnsignedToFloat
                                ((uint)CONCAT11(local_64[0x14],local_64[0x15]),
                                 (byte)(in_fpscr >> 0x16) & 3);
      pfVar7[4] = fVar14 / fVar8;
      fVar14 = (float)VectorUnsignedToFloat
                                ((uint)CONCAT11(local_64[0x16],local_64[0x17]),
                                 (byte)(in_fpscr >> 0x16) & 3);
      pfVar7[5] = fVar14 / fVar8;
      FUN_08014560();
    }
    else {
      local_44 = *DAT_08014f5c;
      local_43 = *DAT_08014f60;
      local_42 = *DAT_08014f64;
      local_41 = *DAT_08014f68;
      local_40 = *DAT_08014f6c;
      local_3f = *DAT_08014f70;
      local_3e = (char)*DAT_08014f74 + '(';
      local_3d = (char)DAT_08014f74[1] + '(';
      local_3c = (char)DAT_08014f74[2] + '(';
      local_3b = (char)DAT_08014f74[3] + '(';
      local_3a = (char)DAT_08014f74[4] + '(';
      local_39 = (char)DAT_08014f74[5] + '(';
      uVar13 = VectorFloatToUnsigned(*DAT_08014f78 * DAT_08014f7c,3);
      local_38 = (undefined1)((uint)uVar13 >> 8);
      uVar13 = VectorFloatToUnsigned(*DAT_08014f78 * DAT_08014f7c,3);
      local_37 = (undefined1)uVar13;
      uVar13 = VectorFloatToUnsigned(DAT_08014f78[1] * DAT_08014f7c,3);
      local_36 = (undefined1)((uint)uVar13 >> 8);
      uVar13 = VectorFloatToUnsigned(DAT_08014f78[1] * DAT_08014f7c,3);
      local_35 = (undefined1)uVar13;
      uVar13 = VectorFloatToUnsigned(DAT_08014f78[2] * DAT_08014f7c,3);
      local_34 = (undefined1)((uint)uVar13 >> 8);
      uVar13 = VectorFloatToUnsigned(DAT_08014f78[2] * DAT_08014f7c,3);
      local_33 = (undefined1)uVar13;
      uVar13 = VectorFloatToUnsigned(DAT_08014f78[3] * DAT_08014f7c,3);
      local_32 = (undefined1)((uint)uVar13 >> 8);
      uVar13 = VectorFloatToUnsigned(DAT_08014f78[3] * DAT_08014f7c,3);
      local_31 = (undefined1)uVar13;
      uVar13 = VectorFloatToUnsigned(DAT_08014f78[4] * DAT_08014f7c,3);
      local_30 = (undefined1)((uint)uVar13 >> 8);
      uVar13 = VectorFloatToUnsigned(DAT_08014f78[4] * DAT_08014f7c,3);
      local_2f = (undefined1)uVar13;
      uVar13 = VectorFloatToUnsigned(DAT_08014f78[5] * DAT_08014f7c,3);
      local_2e = (undefined1)((uint)uVar13 >> 8);
      uVar13 = VectorFloatToUnsigned(DAT_08014f78[5] * DAT_08014f7c,3);
      local_2d = (undefined1)uVar13;
      local_2c = FUN_0800c0d0(&local_44,0x18);
      FUN_0800f850(0x180,&local_44,0x19);
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08014f80 at 0x08014f80
// ---------------------------------------------------------------------------

void FUN_08014f80(void)

{
  undefined1 *puVar1;
  
  puVar1 = DAT_08014fa0;
  *DAT_08014fa0 = 0;
  puVar1[1] = 0;
  puVar1[2] = 0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[5] = 0;
  puVar1[6] = 0;
  puVar1[7] = 0;
  puVar1[8] = 0;
  puVar1[9] = 0;
  puVar1[10] = 0;
  puVar1[0xb] = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08014fa4 at 0x08014fa4
// ---------------------------------------------------------------------------

void FUN_08014fa4(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  
  *DAT_080151b0 = 1;
  *DAT_080151b4 = 0x464;
  *DAT_080151b8 = 0x1e;
  puVar1 = DAT_080151dc;
  *DAT_080151c0 = DAT_080151bc;
  uVar2 = DAT_080151e0;
  *puVar1 = s_6495_004615_A22_260316_080151c4;
  puVar1 = DAT_080151f0;
  *DAT_080151e4 = uVar2;
  *DAT_080151e8 = 0x41200000;
  *puVar1 = DAT_080151ec;
  puVar3 = DAT_080151f8;
  *(undefined4 *)(DAT_080151f8 + 4) = DAT_080151f4;
  puVar4 = DAT_08015210;
  *DAT_08015200 = DAT_080151fc;
  *DAT_08015204 = 0x3f000000;
  *DAT_08015208 = 0x40900000;
  *DAT_0801520c = 0x40000000;
  *puVar4 = 0;
  *DAT_08015214 = 0;
  *DAT_08015218 = 0;
  *DAT_0801521c = 0;
  *DAT_08015220 = 10;
  *DAT_08015224 = 0x1e;
  *DAT_08015228 = 0x20;
  *DAT_0801522c = 1;
  *DAT_08015230 = 1;
  *DAT_08015234 = 1;
  *DAT_08015238 = 1;
  *DAT_0801523c = 1;
  *DAT_08015240 = 7;
  *DAT_08015244 = 3;
  *DAT_08015248 = 3;
  *DAT_0801524c = 3;
  *DAT_08015250 = 0xb;
  *DAT_08015254 = 0;
  *DAT_08015258 = 0xb;
  *DAT_0801525c = 4;
  *DAT_08015260 = 0;
  *DAT_08015264 = 0;
  *DAT_08015268 = 0;
  *DAT_0801526c = 1;
  *DAT_08015270 = 1;
  *DAT_08015274 = 2;
  *DAT_08015278 = 0;
  *DAT_0801527c = 1;
  *DAT_08015280 = 1;
  *DAT_08015284 = 0;
  *DAT_08015288 = 0;
  *puVar3 = 6;
  *DAT_0801528c = 0x15;
  *DAT_08015290 = 0x15;
  *DAT_08015294 = 0;
  *DAT_08015298 = 4;
  *DAT_0801529c = 4;
  *DAT_080152a0 = 0;
  uVar2 = DAT_080152a4;
  *DAT_080152a8 = DAT_080152a4;
  *DAT_080152ac = uVar2;
  *DAT_080152b0 = 0x3e800000;
  *DAT_080152b4 = 0x3e800000;
  uVar2 = DAT_080152b8;
  *DAT_080152bc = DAT_080152b8;
  *DAT_080152c0 = uVar2;
  *DAT_080152c4 = 3;
  *DAT_080152c8 = 3;
  *DAT_080152cc = 1;
  *DAT_080152d0 = 0;
  *DAT_080152d4 = 10;
  *DAT_080152d8 = 0;
  *DAT_080152dc = 1;
  *DAT_080152e0 = 0;
  *DAT_080152e4 = 0;
  *DAT_080152e8 = 0;
  *DAT_080152ec = 0x14;
  *DAT_080152f0 = 100;
  *DAT_080152f4 = 2;
  *DAT_080152f8 = 1;
  *DAT_080152fc = 0;
  *DAT_08015300 = 0x50;
  *DAT_08015304 = 0;
  uVar2 = DAT_08015308;
  *DAT_0801530c = DAT_08015308;
  *DAT_08015314 = DAT_08015310;
  *DAT_08015318 = 2;
  *DAT_0801531c = 2;
  *DAT_08015320 = 0x13;
  *DAT_08015324 = 0x22;
  *DAT_08015328 = 0x21;
  *DAT_0801532c = 0;
  *DAT_08015330 = 0;
  *DAT_08015334 = 0;
  *DAT_08015338 = 8;
  *DAT_0801533c = 1;
  *DAT_08015340 = 0x100;
  *DAT_08015344 = 1;
  *DAT_08015348 = 0;
  *DAT_0801534c = 1;
  *DAT_08015350 = 1;
  *DAT_08015354 = 0x101;
  *DAT_08015358 = uVar2;
  *DAT_0801535c = uVar2;
  *DAT_08015360 = 1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08015364 at 0x08015364
// ---------------------------------------------------------------------------

void FUN_08015364(void)

{
  FUN_08012330(0x1a8,DAT_08015370,0x18);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08015374 at 0x08015374
// ---------------------------------------------------------------------------

void FUN_08015374(uint param_1)

{
  uint in_fpscr;
  float fVar1;
  uint uVar2;
  
  FUN_080128c4(0x5555);
  FUN_080128b8(5);
  fVar1 = (float)VectorUnsignedToFloat(param_1 & 0xffff,(byte)(in_fpscr >> 0x16) & 3);
  uVar2 = VectorFloatToUnsigned(fVar1 / DAT_080153b4,3);
  FUN_0801288c(uVar2 & 0xffff);
  FUN_080128a8();
  *DAT_080128a4 = 0xcccc;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080153b8 at 0x080153b8
// ---------------------------------------------------------------------------

void FUN_080153b8(void)

{
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080153bc at 0x080153bc
// ---------------------------------------------------------------------------

undefined8 FUN_080153bc(undefined4 param_1)

{
  bool bVar1;
  int *piVar2;
  undefined1 *puVar3;
  undefined1 uVar4;
  char *pcVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  undefined8 uVar10;
  ushort local_28;
  undefined2 uStack_26;
  ushort local_24;
  undefined2 uStack_22;
  
  iVar7 = DAT_08015584;
  local_28 = (ushort)param_1;
  uStack_26 = (undefined2)((uint)param_1 >> 0x10);
  uStack_22 = 0;
  local_24 = 0;
  bVar1 = false;
  if (*DAT_08015570 != '\0') {
    if ((*DAT_08015574 == 0x200) || (*DAT_08015574 == 0x100)) {
      iVar8 = *DAT_08015578;
    }
    else {
      iVar8 = DAT_0801557c;
    }
    local_24 = (ushort)iVar8;
    uStack_22 = (undefined2)((uint)iVar8 >> 0x10);
    if (*DAT_08015580 == '\0') {
      uVar9 = DAT_080155a0;
    }
    else if (*DAT_08015588 == '\0') {
      uVar9 = DAT_080155a4;
    }
    else if (*DAT_0801558c == '\0') {
      uVar9 = DAT_080155a8;
    }
    else if (*DAT_08015590 == '\0') {
      uVar9 = DAT_080155ac;
    }
    else if (*DAT_08015594 == '\0') {
      uVar9 = DAT_080155b0;
    }
    else if (*DAT_08015598 == '\0') {
      uVar9 = DAT_080155b4;
    }
    else {
      uVar9 = DAT_0801559c;
    }
    *(undefined4 *)(DAT_08015584 + 0x34) = uVar9;
    pcVar5 = *(char **)(iVar7 + 0x34);
    *pcVar5 = *(char *)(iVar8 + 0x1c0);
    if (*pcVar5 != -1) {
      for (local_28 = 0; local_28 < 0xca; local_28 = local_28 + 1) {
        pcVar5[local_28] = *(char *)(iVar8 + (uint)local_28 + 0x1c0);
      }
      uVar6 = FUN_0800c0d0(*(undefined4 *)(iVar7 + 0x34),0xc9);
      if (uVar6 == *(byte *)(*(int *)(iVar7 + 0x34) + 0xc9)) {
        bVar1 = true;
      }
    }
    puVar3 = DAT_080155bc;
    piVar2 = DAT_080155b8;
    if ((!bVar1) || (pcVar5 = *(char **)(iVar7 + 0x34), *pcVar5 == -1)) {
      local_28 = 0;
      iVar8 = *(int *)(iVar7 + 0x34);
      for (; local_28 < 100; local_28 = local_28 + 1) {
        uVar9 = *(undefined4 *)(*piVar2 + (uint)local_28 * 4);
        *(char *)(iVar8 + (uint)local_28 * 2) = (char)((uint)uVar9 >> 8);
        *(char *)(iVar8 + (uint)local_28 * 2 + 1) = (char)uVar9;
      }
      *(undefined1 *)(iVar8 + 200) = *puVar3;
      uVar4 = FUN_0800c0d0(iVar8,0xc9);
      iVar7 = *(int *)(iVar7 + 0x34);
      *(undefined1 *)(iVar7 + 0xc9) = uVar4;
      uVar10 = FUN_0800f850(0x1c0,iVar7,0xca);
      return uVar10;
    }
    local_28 = 0;
    iVar8 = *DAT_080155b8;
    for (; local_28 < 100; local_28 = local_28 + 1) {
      local_24 = (ushort)(byte)pcVar5[(uint)local_28 * 2];
      *(uint *)(iVar8 + (uint)local_28 * 4) =
           (uint)CONCAT11(pcVar5[(uint)local_28 * 2],pcVar5[(uint)local_28 * 2 + 1]);
    }
    *puVar3 = *(undefined1 *)(*(int *)(iVar7 + 0x34) + 200);
    if (*DAT_080155c0 == '\x01') {
      if (DAT_080155c8 < *DAT_080155c4) {
        *puVar3 = 1;
      }
      else {
        *puVar3 = 0;
      }
    }
  }
  return CONCAT26(uStack_22,CONCAT24(local_24,CONCAT22(uStack_26,local_28)));
}



// ---------------------------------------------------------------------------
// Function: FUN_080155cc at 0x080155cc
// ---------------------------------------------------------------------------

void FUN_080155cc(void)

{
  int iVar1;
  short sVar2;
  undefined2 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  short *psVar6;
  uint in_fpscr;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined8 uVar9;
  
  iVar1 = DAT_080156ec;
  psVar6 = (short *)(DAT_080156ec + -0x200);
  *(char *)(DAT_080156ec + -0x1d4) =
       *(char *)(DAT_080156ec + 8) + *(char *)(DAT_080156ec + 9) * '\x10';
  *psVar6 = *(byte *)(iVar1 + 0x16) + 1;
  uVar9 = FUN_08008548(*psVar6);
  uVar4 = (undefined4)((ulonglong)DAT_080156f0 >> 0x20);
  uVar8 = (undefined4)DAT_080156f0;
  uVar9 = FUN_08008364((int)uVar9,(int)((ulonglong)uVar9 >> 0x20),uVar8,uVar4);
  uVar5 = (undefined4)((ulonglong)DAT_080156f8 >> 0x20);
  uVar7 = (undefined4)DAT_080156f8;
  FUN_08008358((int)uVar9,(int)((ulonglong)uVar9 >> 0x20),uVar7,uVar5);
  sVar2 = FUN_080085a0();
  *psVar6 = sVar2;
  *(ushort *)(iVar1 + -0x1fe) = *(byte *)(iVar1 + 0x15) + 1;
  uVar9 = FUN_08008548(*(undefined2 *)(iVar1 + -0x1fe));
  uVar9 = FUN_08008364((int)uVar9,(int)((ulonglong)uVar9 >> 0x20),uVar8,uVar4);
  FUN_08008358((int)uVar9,(int)((ulonglong)uVar9 >> 0x20),(int)DAT_08015700,
               (int)((ulonglong)DAT_08015700 >> 0x20));
  uVar3 = FUN_080085a0();
  *(undefined2 *)(iVar1 + -0x1fe) = uVar3;
  if (*(char *)(DAT_08015708 + 6) == '\x01') {
    uVar9 = FUN_08008548(*(undefined1 *)(iVar1 + 0x14));
    uVar9 = FUN_08008364((int)uVar9,(int)((ulonglong)uVar9 >> 0x20),uVar7,uVar5);
    FUN_08008216((int)uVar9,(int)((ulonglong)uVar9 >> 0x20),uVar7,uVar5);
    uVar4 = FUN_08008658();
    *(undefined4 *)(iVar1 + -0x1fc) = uVar4;
    uVar9 = FUN_08008548(*(undefined1 *)(iVar1 + 1));
    uVar9 = FUN_08008364((int)uVar9,(int)((ulonglong)uVar9 >> 0x20),uVar7,uVar5);
    FUN_08008216((int)uVar9,(int)((ulonglong)uVar9 >> 0x20),uVar7,uVar5);
  }
  else {
    if (*(char *)(DAT_08015708 + 6) != '\x02') {
      uVar4 = VectorUnsignedToFloat(*(byte *)(iVar1 + 0x14) + 1,(byte)(in_fpscr >> 0x16) & 3);
      *(undefined4 *)(iVar1 + -0x1fc) = uVar4;
      uVar4 = VectorUnsignedToFloat(*(byte *)(iVar1 + 1) + 1,(byte)(in_fpscr >> 0x16) & 3);
      goto LAB_08015660;
    }
    uVar9 = FUN_08008548();
    FUN_08008364((int)uVar9,(int)((ulonglong)uVar9 >> 0x20),(int)DAT_0801570c,
                 (int)((ulonglong)DAT_0801570c >> 0x20));
    uVar4 = FUN_08008658();
    *(undefined4 *)(iVar1 + -0x1fc) = uVar4;
    uVar9 = FUN_08008548(*(byte *)(iVar1 + 1) + 1);
    FUN_08008364((int)uVar9,(int)((ulonglong)uVar9 >> 0x20),(int)DAT_08015714,
                 (int)((ulonglong)DAT_08015714 >> 0x20));
  }
  uVar4 = FUN_08008658();
LAB_08015660:
  *(undefined4 *)(iVar1 + -0x1f8) = uVar4;
  *(char *)(iVar1 + -0x1d3) = *(char *)(iVar1 + 0x17) + *(char *)(iVar1 + 0x18) * '\b';
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801571c at 0x0801571c
// ---------------------------------------------------------------------------

void FUN_0801571c(void)

{
  int iVar1;
  short *psVar2;
  
  iVar1 = DAT_08015764;
  psVar2 = (short *)(DAT_08015764 + -0x2fc);
  *(ushort *)(DAT_08015764 + -0x2f4) = *(byte *)(DAT_08015764 + 10) + 0x1e;
  *(ushort *)(iVar1 + -0x2f2) = *(byte *)(iVar1 + 0xb) + 0x1e;
  *(ushort *)(iVar1 + -0x2f0) = *(byte *)(iVar1 + 0xc) - 0x28;
  *(ushort *)(iVar1 + -0x2ee) = *(byte *)(iVar1 + 0xd) - 0x28;
  *psVar2 = *(byte *)(iVar1 + 0xe) + 0x1e;
  *(ushort *)(iVar1 + -0x2fa) = *(byte *)(iVar1 + 0xf) + 0x1e;
  *(ushort *)(iVar1 + -0x2f8) = *(byte *)(iVar1 + 0x10) - 0x28;
  *(ushort *)(iVar1 + -0x2f6) = *(byte *)(iVar1 + 0x11) - 0x28;
  *(undefined2 *)(iVar1 + -0x2ec) = 5000;
  *(undefined2 *)(iVar1 + -0x2ea) = 5000;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08015768 at 0x08015768
// ---------------------------------------------------------------------------

void FUN_08015768(void)

{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  
  iVar1 = DAT_08015820;
  uVar4 = FUN_08008548(*(undefined1 *)(DAT_08015820 + 2));
  uVar4 = FUN_08008448((int)uVar4,(int)((ulonglong)uVar4 >> 0x20),(int)DAT_08015824,
                       (int)((ulonglong)DAT_08015824 >> 0x20));
  FUN_08008216((int)uVar4,(int)((ulonglong)uVar4 >> 0x20),(int)DAT_0801582c,
               (int)((ulonglong)DAT_0801582c >> 0x20));
  uVar3 = FUN_08008658();
  *(undefined4 *)(iVar1 + -0x2a0) = uVar3;
  uVar4 = FUN_08008548(*(undefined1 *)(iVar1 + 6));
  uVar4 = FUN_08008364((int)uVar4,(int)((ulonglong)uVar4 >> 0x20),(int)DAT_08015834,
                       (int)((ulonglong)DAT_08015834 >> 0x20));
  uVar5 = FUN_080085d2(*(undefined4 *)(iVar1 + -0x2a0));
  FUN_08008358((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),(int)uVar4,(int)((ulonglong)uVar4 >> 0x20)
              );
  uVar3 = FUN_08008658();
  *(undefined4 *)(iVar1 + -0x29c) = uVar3;
  *(ushort *)(iVar1 + -0x298) = (*(byte *)(iVar1 + 3) & 0x7f) * 100;
  if (*(ushort *)(iVar1 + -0x298) < 0x1f5) {
    if (*(ushort *)(iVar1 + -0x298) < 0xc9) goto LAB_080157fc;
    sVar2 = *(short *)(iVar1 + -0x298) + -100;
  }
  else {
    sVar2 = *(ushort *)(iVar1 + -0x298) - 300;
  }
  *(short *)(iVar1 + -0x298) = sVar2;
LAB_080157fc:
  *(ushort *)(iVar1 + -0x296) = (*(byte *)(iVar1 + 0x19) + 1) * 1000;
  *(short *)(iVar1 + -0x296) = *(short *)(iVar1 + -0x296) + -300;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801583c at 0x0801583c
// ---------------------------------------------------------------------------

undefined4 FUN_0801583c(void)

{
  return DAT_08015840;
}



// ---------------------------------------------------------------------------
// Function: FUN_08015844 at 0x08015844
// ---------------------------------------------------------------------------

void FUN_08015844(void)

{
  float *pfVar1;
  uint uVar2;
  byte extraout_r1;
  byte bVar3;
  uint in_fpscr;
  float fVar4;
  
  if (*DAT_080158c0 != '\x01') {
    return;
  }
  uVar2 = FUN_080112a4();
  pfVar1 = DAT_080158c8;
  bVar3 = extraout_r1;
  while ((bVar3 < 100 && (*(uint *)(*DAT_080158c4 + (99 - (uint)bVar3) * 4) <= uVar2))) {
    bVar3 = bVar3 + 1;
  }
  *(byte *)((int)DAT_080158c8 + 0x12) = bVar3 << 1;
  fVar4 = (float)VectorUnsignedToFloat
                           ((uint)*(byte *)((int)pfVar1 + 0x12),(byte)(in_fpscr >> 0x16) & 3);
  fVar4 = (float)(int)((*pfVar1 / DAT_080158cc) * fVar4);
  pfVar1[2] = fVar4;
  FUN_0800b460(pfVar1,fVar4,bVar3,uVar2);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080158d0 at 0x080158d0
// ---------------------------------------------------------------------------

void FUN_080158d0(void)

{
  undefined4 uVar1;
  undefined4 in_r3;
  undefined4 local_18;
  
  local_18 = in_r3;
  FUN_08017cb0(4,1);
  FUN_08017cb0(8,1);
  FUN_08017cb0(0x10,1);
  FUN_08017cb0(0x20,1);
  FUN_08017cb0(1);
  FUN_080101b0(DAT_080159a4,1);
  uVar1 = DAT_080159a8;
  local_18 = 0x100233a5;
  FUN_0801031c(DAT_080159a8,&local_18);
  local_18 = CONCAT22(local_18._2_2_,0x5a);
  local_18 = CONCAT13(4,(undefined3)local_18);
  FUN_0801031c(uVar1,&local_18);
  local_18 = CONCAT22(local_18._2_2_,4);
  local_18 = CONCAT13(4,(undefined3)local_18);
  FUN_0801031c(DAT_080159ac,&local_18);
  uVar1 = DAT_080159b0;
  local_18 = 0x100287c1;
  FUN_0801031c(DAT_080159b0,&local_18);
  local_18 = CONCAT22(local_18._2_2_,2);
  local_18 = CONCAT13(4,(undefined3)local_18);
  FUN_0801031c(uVar1,&local_18);
  uVar1 = DAT_080159b4;
  local_18 = 0x1002431a;
  FUN_0801031c(DAT_080159b4,&local_18);
  local_18 = CONCAT22(local_18._2_2_,0xbc25);
  local_18 = CONCAT13(4,(undefined3)local_18);
  FUN_0801031c(uVar1,&local_18);
  FUN_0800f610(0);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080159b8 at 0x080159b8
// ---------------------------------------------------------------------------

void FUN_080159b8(void)

{
  FUN_08017e10();
  FUN_08017e28();
  FUN_08017e40();
  FUN_08017e58();
  FUN_08021864();
  FUN_0800ac90();
  FUN_08016620();
  FUN_08016608();
  FUN_08011464();
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080159e4 at 0x080159e4
// ---------------------------------------------------------------------------

void FUN_080159e4(void)

{
  if (*(char *)(DAT_080159f8 + 0x3d) == '\0') {
    FUN_0800db18(0x14);
    return;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080159fc at 0x080159fc
// ---------------------------------------------------------------------------

void FUN_080159fc(void)

{
  int iVar1;
  char cVar2;
  byte *pbVar3;
  undefined4 in_r3;
  
  FUN_08012330(0xe0,DAT_08015a94,1,in_r3,in_r3);
  if (*DAT_08015a94 < 0x21) {
    FUN_08012330(0xe0,DAT_08015a94,*DAT_08015a94 + 1);
  }
  FUN_08012330(0x162,DAT_08015a94 + 0x20,1);
  pbVar3 = DAT_08015a94 + 0x20;
  if (*pbVar3 < 0x21) {
    FUN_08012330(0x162,pbVar3,*pbVar3 + 4);
  }
  cVar2 = FUN_08018354(0x104);
  iVar1 = DAT_08015a98;
  if (cVar2 == -1) {
    FUN_08021b54(0x104,*(undefined1 *)(DAT_08015a98 + 1));
  }
  else {
    *(char *)(DAT_08015a98 + 1) = cVar2;
  }
  cVar2 = FUN_08018354(0x105);
  if (cVar2 == -1) {
    FUN_08021b54(0x105,*(undefined1 *)(iVar1 + 2));
    return;
  }
  *(char *)(iVar1 + 2) = cVar2;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08015a9c at 0x08015a9c
// ---------------------------------------------------------------------------

void FUN_08015a9c(void)

{
  undefined4 uVar1;
  int iVar2;
  float fVar3;
  
  iVar2 = DAT_08015b20;
  uVar1 = DAT_08015b10;
  if (*DAT_08015b14 == '\0') {
    fVar3 = *(float *)(DAT_08015b18 + 0xc);
  }
  else {
    fVar3 = *(float *)(DAT_08015b1c + 0x114);
  }
  if (((fVar3 < *(float *)(DAT_08015b20 + 0x48)) &&
      ((int)(*(float *)(DAT_08015b24 + 0xc) - *(float *)(DAT_08015b18 + 0xc)) < 0x3f000000)) &&
     (0x3fc00000 < *(int *)(DAT_08015b18 + 0xc))) {
    *(undefined1 *)(DAT_08015b20 + 0x59) = 0;
    *(undefined1 *)(iVar2 + 0x5f) = 2;
    *(undefined4 *)(iVar2 + 100) = uVar1;
    *(undefined4 *)(iVar2 + 0x60) = uVar1;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08015b28 at 0x08015b28
// ---------------------------------------------------------------------------

void FUN_08015b28(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 unaff_r7;
  short local_48;
  undefined1 local_46;
  undefined1 local_45;
  int local_44;
  int local_40;
  undefined2 local_3c;
  undefined2 local_3a;
  undefined2 local_38;
  undefined2 local_36;
  undefined2 local_34;
  undefined4 uStack_2c;
  int local_28;
  
  local_44 = 0;
  uStack_2c = param_1;
  local_28 = param_2;
  FUN_08017cb0(1);
  uVar2 = DAT_08015e98;
  iVar1 = DAT_08015e94;
  uVar3 = DAT_08015e90;
  switch(param_1) {
  default:
    goto LAB_08015e36;
  case 1:
    if ((*DAT_08015e9c == '\x01') && (local_44 = FUN_080103be(), local_44 != 0)) {
      local_28 = local_44;
    }
    if (*DAT_08015ea0 == '\a') {
      local_48 = 0x40;
      local_45 = 0x18;
      local_46 = 2;
      FUN_0801031c(uVar3,&local_48);
      local_48 = 0x80;
      local_45 = 4;
      FUN_0801031c(uVar3,&local_48);
      *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 4;
      FUN_080101b0(DAT_08015ea4,1);
    }
    else if (*DAT_08015ea0 == '\n') {
      local_48 = 0x200;
      local_45 = 0x18;
      local_46 = 2;
      FUN_0801031c(uVar2,&local_48);
      local_48 = 0x400;
      local_45 = 4;
      FUN_0801031c(uVar2,&local_48);
    }
    uVar3 = 0x4000;
    unaff_r7 = DAT_08015ea8;
    goto LAB_08015e32;
  case 2:
    if ((*DAT_08015eac == '\x01') && (local_44 = FUN_080103be(), local_44 != 0)) {
      local_28 = local_44;
    }
    if (*DAT_08015eb0 == '\x03') {
      local_48 = 4;
      local_45 = 0x18;
      local_46 = 2;
      FUN_0801031c(uVar2,&local_48);
      local_48 = 8;
      local_45 = 4;
      FUN_0801031c(uVar2,&local_48);
    }
    else if (*DAT_08015eb0 == '\x05') {
      local_48 = 0x10;
      local_45 = 0x18;
      local_46 = 2;
      FUN_0801031c(uVar3,&local_48);
      local_48 = 0x20;
      local_45 = 4;
      FUN_0801031c(uVar3,&local_48);
      *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 8;
      *(uint *)(iVar1 + 0x20) = *(uint *)(iVar1 + 0x20) | 0x80000;
      FUN_080101b0(DAT_08015ea4,1);
    }
    uVar3 = 0x20000;
    unaff_r7 = DAT_08015eb4;
    break;
  case 3:
    if ((*DAT_08015eb8 == '\x01') && (local_44 = FUN_080103be(), local_44 != 0)) {
      local_28 = local_44;
    }
    if (*DAT_08015ebc == '\v') {
      local_48 = 0x400;
      local_45 = 0x18;
      local_46 = 2;
      FUN_0801031c(uVar3,&local_48);
      local_48 = 0x800;
      local_45 = 4;
      FUN_0801031c(uVar3,&local_48);
    }
    uVar3 = 0x40000;
    unaff_r7 = DAT_08015ec0;
    break;
  case 4:
    if ((*DAT_08015ec4 == '\x01') && (local_44 = FUN_080103be(), local_44 != 0)) {
      local_28 = local_44;
    }
    uVar3 = DAT_08015ecc;
    if (*DAT_08015ec8 == '\x0e') {
      local_48 = 0x2000;
      local_45 = 0x18;
      local_46 = 2;
      FUN_0801031c(uVar2,&local_48);
      local_48 = 0x4000;
      local_45 = 4;
      FUN_0801031c(uVar2,&local_48);
      *(uint *)(iVar1 + 0x20) = *(uint *)(iVar1 + 0x20) | 0x200000;
    }
    else if (*DAT_08015ec8 == '\v') {
      local_48 = 0x400;
      local_45 = 0x18;
      local_46 = 2;
      FUN_0801031c(DAT_08015ecc,&local_48);
      local_48 = (short)((int)uVar3 >> 0x13);
      local_45 = 4;
      FUN_0801031c(uVar3,&local_48);
    }
    uVar3 = 0x80000;
    unaff_r7 = DAT_08015ed0;
    break;
  case 5:
    if ((*DAT_08015ed4 == '\x01') && (local_44 = FUN_080103be(), local_44 != 0)) {
      local_28 = local_44;
    }
    if (*DAT_08015ed8 == '\x0e') {
      local_48 = 0x2000;
      local_45 = 0x18;
      local_46 = 2;
      FUN_0801031c(uVar3,&local_48);
      local_48 = 0x4000;
      local_45 = 4;
      FUN_0801031c(uVar3,&local_48);
      *(uint *)(iVar1 + 0x20) = *(uint *)(iVar1 + 0x20) | 0x400000;
    }
    uVar3 = 0x100000;
    unaff_r7 = DAT_08015edc;
    break;
  case 6:
    if ((*DAT_08015ee0 == '\x01') && (local_44 = FUN_080103be(), local_44 != 0)) {
      local_28 = local_44;
    }
    uVar3 = DAT_08015ecc;
    if (*DAT_08015ee4 == '\x01') {
      local_48 = 1;
      local_45 = 0x18;
      local_46 = 2;
      FUN_0801031c(DAT_08015ecc,&local_48);
      local_48 = 2;
      local_45 = 4;
      FUN_0801031c(uVar3,&local_48);
      *(uint *)(iVar1 + 0x20) = *(uint *)(iVar1 + 0x20) | 0x2000000;
    }
    uVar3 = 0x20000;
    unaff_r7 = DAT_08015ee8;
    goto LAB_08015e32;
  case 7:
    if ((*DAT_08015eec == '\x01') && (local_44 = FUN_080103be(), local_44 != 0)) {
      local_28 = local_44;
    }
    uVar3 = 0x40000;
    unaff_r7 = DAT_08015ef0;
LAB_08015e32:
    FUN_08017cb0(uVar3);
    goto LAB_08015e36;
  }
  FUN_08017c80(uVar3);
LAB_08015e36:
  local_40 = local_28;
  local_3c = 0;
  local_3a = 0;
  local_38 = 0;
  local_34 = 0;
  local_36 = 0xc;
  FUN_08020740(unaff_r7,&local_40);
  FUN_08020654(unaff_r7,0x525,1);
  FUN_0802072c(unaff_r7,1);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08015ef4 at 0x08015ef4
// ---------------------------------------------------------------------------

undefined4 FUN_08015ef4(void)

{
  return DAT_08015ef8;
}



// ---------------------------------------------------------------------------
// Function: FUN_08015efc at 0x08015efc
// ---------------------------------------------------------------------------

void FUN_08015efc(void)

{
  int iVar1;
  uint local_8;
  
  iVar1 = DAT_08015f24;
  local_8 = 0;
  while ((byte)local_8 < 0x18) {
    *(undefined1 *)(iVar1 + local_8) = 0;
    local_8 = (uint)(byte)((byte)local_8 + 1);
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08015f28 at 0x08015f28
// ---------------------------------------------------------------------------

void FUN_08015f28(void)

{
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08015f2c at 0x08015f2c
// ---------------------------------------------------------------------------

void FUN_08015f2c(void)

{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  
  iVar1 = DAT_08015fe4;
  uVar4 = FUN_08008548(*(undefined1 *)(DAT_08015fe4 + 4));
  uVar4 = FUN_08008448((int)uVar4,(int)((ulonglong)uVar4 >> 0x20),(int)DAT_08015fe8,
                       (int)((ulonglong)DAT_08015fe8 >> 0x20));
  FUN_08008216((int)uVar4,(int)((ulonglong)uVar4 >> 0x20),(int)DAT_08015ff0,
               (int)((ulonglong)DAT_08015ff0 >> 0x20));
  uVar3 = FUN_08008658();
  *(undefined4 *)(iVar1 + -0x254) = uVar3;
  uVar4 = FUN_08008548(*(undefined1 *)(iVar1 + 7));
  uVar4 = FUN_08008364((int)uVar4,(int)((ulonglong)uVar4 >> 0x20),(int)DAT_08015ff8,
                       (int)((ulonglong)DAT_08015ff8 >> 0x20));
  uVar5 = FUN_080085d2(*(undefined4 *)(iVar1 + -0x254));
  FUN_08008216((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),(int)uVar4,(int)((ulonglong)uVar4 >> 0x20)
              );
  uVar3 = FUN_08008658();
  *(undefined4 *)(iVar1 + -0x250) = uVar3;
  *(ushort *)(iVar1 + -0x24c) = (*(byte *)(iVar1 + 5) & 0x7f) * 100;
  if (*(ushort *)(iVar1 + -0x24c) < 0x1f5) {
    if (*(ushort *)(iVar1 + -0x24c) < 0xc9) goto LAB_08015fc0;
    sVar2 = *(short *)(iVar1 + -0x24c) + -100;
  }
  else {
    sVar2 = *(ushort *)(iVar1 + -0x24c) - 300;
  }
  *(short *)(iVar1 + -0x24c) = sVar2;
LAB_08015fc0:
  *(ushort *)(iVar1 + -0x24a) = (*(byte *)(iVar1 + 0x1a) + 1) * 1000;
  *(short *)(iVar1 + -0x24a) = *(short *)(iVar1 + -0x24a) + -300;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08016000 at 0x08016000
// ---------------------------------------------------------------------------

void FUN_08016000(void)

{
  char *pcVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  int iVar6;
  byte bVar7;
  byte bVar8;
  int iVar9;
  uint in_fpscr;
  float fVar10;
  uint local_18;
  uint local_14;
  
  uVar2 = DAT_08016134;
  pcVar1 = DAT_08016130;
  do {
  } while (*(short *)(*DAT_0801612c + 0x25a) != 0);
  for (bVar7 = 0; bVar7 < 10; bVar7 = bVar7 + 1) {
    FUN_08012330(0x60,uVar2,(uint)(byte)pcVar1[9] << 1);
    FUN_0800c084(uVar2,((byte)pcVar1[9] & 0x7f) << 1);
    if (*pcVar1 == '\x01') break;
  }
  iVar3 = DAT_08016138;
  bVar8 = 1;
  if (9 < bVar7) {
    pcVar1[7] = '\x01';
    for (; local_18 = (uint)bVar8, local_18 <= (byte)pcVar1[9]; bVar8 = bVar8 + 1) {
      *(undefined4 *)(iVar3 + local_18 * 4) = 0x3f800000;
    }
    return;
  }
  pcVar1[7] = '\0';
  iVar6 = DAT_08016144;
  fVar5 = DAT_08016140;
  iVar4 = DAT_0801613c;
  iVar9 = DAT_08016144 * 0x40000000;
  local_18 = 1;
  while (local_18 <= (byte)pcVar1[9]) {
    local_14 = (uint)CONCAT11(*(undefined1 *)(iVar4 + local_18 * 2 + 300),
                              *(undefined1 *)(iVar4 + local_18 * 2 + 0x12d));
    fVar10 = (float)VectorUnsignedToFloat(local_14,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(iVar3 + local_18 * 4) = fVar10 / fVar5;
    if ((*(int *)(iVar3 + local_18 * 4) <= iVar6) || (iVar9 <= *(int *)(iVar3 + local_18 * 4))) {
      *(undefined4 *)(iVar3 + local_18 * 4) = 0x3f800000;
    }
    local_18 = (uint)(byte)((char)local_18 + 1);
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08016148 at 0x08016148
// ---------------------------------------------------------------------------

void FUN_08016148(void)

{
  uint *puVar1;
  ushort uVar2;
  
  *(uint *)(DAT_080161b4 + 0x1c) = *(uint *)(DAT_080161b4 + 0x1c) | 0x10000000;
  puVar1 = DAT_080161b8;
  *DAT_080161b8 = *DAT_080161b8 | 8;
  FUN_08015374(4000);
  FUN_080173ae();
  FUN_080161bc(0);
  enableIRQinterrupts();
  do {
    uVar2 = 0;
    while( true ) {
      *puVar1 = *puVar1 | 0xe0;
      *puVar1 = *puVar1 | 0x10;
      FUN_0800db18(1);
      if ((int)(puVar1[1] << 0x1d) < 0) break;
      uVar2 = uVar2 + 1;
      if (0x14 < uVar2) {
        return;
      }
    }
  } while( true );
}



// ---------------------------------------------------------------------------
// Function: FUN_080161bc at 0x080161bc
// ---------------------------------------------------------------------------

void FUN_080161bc(undefined4 param_1)

{
  char *pcVar1;
  int iVar2;
  undefined4 uVar3;
  char local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined1 local_2a;
  undefined1 local_28;
  undefined1 local_27;
  undefined1 local_26;
  undefined1 local_25;
  undefined1 local_24;
  undefined1 local_23;
  undefined1 local_22;
  undefined1 local_21;
  undefined2 local_20;
  undefined4 local_18;
  
  pcVar1 = DAT_08016354;
  local_40 = 'd';
  if (*DAT_08016354 == '\0') {
    local_20 = 0x8200;
  }
  else {
    local_20 = 0x8103;
  }
  local_18 = param_1;
  FUN_08017a9c(1);
  iVar2 = FUN_0800989c(4);
  if ((iVar2 != 0xa5a5) || ((char)local_18 != '\0')) {
    FUN_08017c80(0x18000000,1);
    FUN_08017cb0(1);
    FUN_08017a9c(1);
    FUN_08009888();
    *(undefined4 *)(DAT_08016358 + 0x20) = 0;
    FUN_08017cf8(0);
    if (*pcVar1 == '\0') {
      FUN_08017cec(1);
      do {
        iVar2 = FUN_08017dc0(0x61);
        if (iVar2 != 0) break;
        local_40 = local_40 + -1;
        FUN_0800db18(10);
      } while (local_40 != '\0');
      uVar3 = 0x200;
    }
    else {
      FUN_08017be4();
      do {
        iVar2 = FUN_08017dc0(0x41);
        if (iVar2 != 0) break;
        local_40 = local_40 + -1;
        FUN_0800db18(10);
      } while (local_40 != '\0');
      uVar3 = 0x100;
    }
    FUN_08017c04(uVar3);
    FUN_08017cf8(1);
    FUN_08018250();
    if (*pcVar1 == '\0') {
      uStack_34 = 0x99f;
    }
    else {
      uStack_34 = 0x7ff;
    }
    local_38 = 0xf;
    local_3c = 0;
    FUN_080180ac(&local_3c);
    FUN_0800db18(1);
    local_25 = *DAT_0801635c;
    local_27 = DAT_0801635c[1];
    local_26 = DAT_0801635c[2];
    local_28 = 3;
    FUN_080180fc(1,&local_28);
    local_21 = 0;
    local_24 = 4;
    local_23 = 0x22;
    local_22 = 0x30;
    FUN_08017f00(1,&local_24);
    FUN_080098ac(4,0xa5a5);
    if (*pcVar1 == '\0') {
      FUN_08017fa0(0);
      uVar3 = 0x99f;
    }
    else {
      FUN_08017fa0(0);
      uVar3 = 0x800;
    }
    FUN_08018200(uVar3);
  }
  FUN_08017a9c(0);
  FUN_0800f3d0(0x100000);
  local_2c = 0;
  local_2b = 8;
  local_2a = 1;
  local_30 = 0x100000;
  FUN_0800f3fc(&local_30);
  FUN_08017fc8(1);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08016360 at 0x08016360
// ---------------------------------------------------------------------------

void FUN_08016360(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar1 = DAT_08016460;
  if (*(char *)(DAT_08016460 + 2) == '\x01') {
    *(undefined1 *)(DAT_08016460 + 7) = 1;
  }
  else if ((*(char *)(DAT_08016460 + 2) == '\0') && (*(char *)(DAT_08016460 + 7) == '\x01')) {
    FUN_0800db18(0x32);
    uVar2 = DAT_08016464;
    FUN_080102cc(DAT_08016464,1);
    uVar3 = DAT_08016468;
    FUN_080102cc(DAT_08016468,2);
    FUN_080102cc(uVar2,4);
    FUN_080102cc(uVar3,8);
    iVar4 = DAT_0801646c;
    FUN_080102cc(DAT_0801646c,0x10);
    FUN_080102cc(uVar2,0x20);
    FUN_080102cc(uVar2,0x80);
    FUN_080102cc(uVar2,0x8000);
    FUN_0800f3d0(1);
    FUN_0800f3d0(2);
    FUN_0800f3d0(4);
    FUN_0800f3d0(8);
    FUN_0800f3d0(0x10);
    FUN_0800f3d0(0x20);
    FUN_0800f3d0(0x80);
    FUN_0800f3d0(0x8000);
    FUN_08017cb0(4,1);
    FUN_08017cb0(8,1);
    FUN_08017cb0(0x10,1);
    FUN_08017cb0(0x20,1);
    *(undefined4 *)(iVar4 + 0x14) = 1;
    FUN_0800a634();
    FUN_08015b28(1,0x2580);
    FUN_08015b28(2,0x2580);
    FUN_08015b28(4,0x2580);
    *(undefined4 *)(iVar4 + 0x10) = 0x20;
    *(undefined4 *)(iVar4 + 0x14) = 0x80;
    *(undefined4 *)(DAT_08016470 + 4) = 0;
    *DAT_08016474 = 0;
    *(undefined2 *)(DAT_08016478 + 0x260) = 0;
    *(undefined1 *)(iVar1 + 7) = 0;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801647c at 0x0801647c
// ---------------------------------------------------------------------------

void FUN_0801647c(void)

{
  int iVar1;
  
  iVar1 = DAT_080164ec;
  if (*(char *)(DAT_080164ec + 2) == '\x01') {
    if ((*DAT_080164f8 == '\0') && (*(int *)(DAT_080164fc + 0x10) < 0x40000000)) {
      *(char *)(DAT_080164ec + 3) = *(char *)(DAT_080164ec + 3) + '\x01';
      if (9 < *(byte *)(iVar1 + 3)) {
        *(undefined1 *)(iVar1 + 3) = 0;
        *(undefined1 *)(iVar1 + 2) = 0x11;
        FUN_0800c8f4();
        FUN_08019844(0,0xbe);
      }
    }
  }
  else {
    *(undefined1 *)(DAT_080164ec + 3) = 0;
  }
  if ((*(char *)(iVar1 + 2) == '\x11') && (*DAT_080164f0 == '\0')) {
    if ((*(char *)(DAT_080164f4 + 0x4c) != '\0') && (*(char *)(DAT_080164f4 + 0x3a) == '\0')) {
      FUN_0800c8f4();
      return;
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08016500 at 0x08016500
// ---------------------------------------------------------------------------

void FUN_08016500(float param_1)

{
  uint uVar1;
  byte bVar2;
  uint in_fpscr;
  float fVar3;
  
  fVar3 = (float)VectorUnsignedToFloat((uint)*DAT_0801659c,(byte)(in_fpscr >> 0x16) & 3);
  uVar1 = in_fpscr & 0xfffffff;
  if (param_1 <= (fVar3 / DAT_080165a0 + 1.0) * *DAT_080165a4) {
    fVar3 = (float)VectorUnsignedToFloat((uint)*DAT_0801659c,(byte)(uVar1 >> 0x16) & 3);
    fVar3 = (1.0 - fVar3 / DAT_080165a0) * *DAT_080165a4;
    uVar1 = uVar1 | (uint)(fVar3 < param_1) << 0x1f | (uint)(fVar3 == param_1) << 0x1e;
    bVar2 = (byte)(uVar1 >> 0x18);
    if ((bool)(bVar2 >> 6 & 1) || (bool)(bVar2 >> 7) != (NAN(fVar3) || NAN(param_1)))
    goto LAB_08016594;
    fVar3 = (float)VectorUnsignedToFloat((uint)*DAT_0801659c,(byte)(uVar1 >> 0x16) & 3);
    param_1 = 1.0 - fVar3 / DAT_080165a0;
  }
  else {
    fVar3 = (float)VectorUnsignedToFloat((uint)*DAT_0801659c,(byte)(uVar1 >> 0x16) & 3);
    param_1 = fVar3 / DAT_080165a0 + 1.0;
  }
  param_1 = param_1 * *DAT_080165a4;
LAB_08016594:
  *DAT_080165a4 = param_1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080165a8 at 0x080165a8
// ---------------------------------------------------------------------------

bool FUN_080165a8(void)

{
  return *DAT_080165b4 != '\0';
}



// ---------------------------------------------------------------------------
// Function: FUN_080165b8 at 0x080165b8
// ---------------------------------------------------------------------------

bool FUN_080165b8(void)

{
  return *DAT_080165c4 != '\0';
}



// ---------------------------------------------------------------------------
// Function: FUN_080165c8 at 0x080165c8
// ---------------------------------------------------------------------------

bool FUN_080165c8(void)

{
  return *DAT_080165d4 != '\0';
}



// ---------------------------------------------------------------------------
// Function: FUN_080165d8 at 0x080165d8
// ---------------------------------------------------------------------------

bool FUN_080165d8(void)

{
  return *DAT_080165e4 != '\0';
}



// ---------------------------------------------------------------------------
// Function: FUN_080165e8 at 0x080165e8
// ---------------------------------------------------------------------------

bool FUN_080165e8(void)

{
  return *DAT_080165f4 != '\0';
}



// ---------------------------------------------------------------------------
// Function: FUN_080165f8 at 0x080165f8
// ---------------------------------------------------------------------------

bool FUN_080165f8(void)

{
  return *DAT_08016604 != '\0';
}



// ---------------------------------------------------------------------------
// Function: FUN_08016608 at 0x08016608
// ---------------------------------------------------------------------------

void FUN_08016608(void)

{
  *DAT_08016610 = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08016614 at 0x08016614
// ---------------------------------------------------------------------------

void FUN_08016614(void)

{
  *DAT_0801661c = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08016620 at 0x08016620
// ---------------------------------------------------------------------------

void FUN_08016620(void)

{
  *DAT_08016628 = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801662c at 0x0801662c
// ---------------------------------------------------------------------------

void FUN_0801662c(void)

{
  *DAT_08016634 = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08016638 at 0x08016638
// ---------------------------------------------------------------------------

undefined1 FUN_08016638(void)

{
  if ((*DAT_08016650 == '\x01') || ((int)((uint)*(byte *)(DAT_08016654 + 8) << 0x1c) < 0)) {
    return 1;
  }
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_08016658 at 0x08016658
// ---------------------------------------------------------------------------

undefined8 FUN_08016658(byte *param_1,char param_2)

{
  ushort uVar1;
  bool bVar2;
  undefined4 local_10;
  
  uVar1 = 0;
  while( true ) {
    local_10 = CONCAT22(local_10._2_2_,uVar1);
    bVar2 = param_2 == '\0';
    param_2 = param_2 + -1;
    if (bVar2) break;
    uVar1 = *param_1 + uVar1;
    param_1 = param_1 + 1;
  }
  return CONCAT44(local_10,(uint)uVar1);
}



// ---------------------------------------------------------------------------
// Function: FUN_08016684 at 0x08016684
// ---------------------------------------------------------------------------

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_08016684(void)

{
  char *pcVar1;
  bool bVar2;
  code *pcVar3;
  int iVar4;
  ushort *puVar5;
  byte bVar6;
  undefined1 uVar7;
  uint uVar8;
  int iVar9;
  uint extraout_r1;
  uint uVar10;
  uint extraout_r3;
  uint uVar11;
  int unaff_r7;
  undefined4 unaff_r8;
  undefined4 in_cr14;
  undefined4 uVar12;
  
  iVar4 = iRam0801674c;
  uVar8 = *(uint *)(iRam0801674c + 0x1c);
  if (*(char *)(uVar8 + 2) == '\x01') {
    *(undefined1 *)(uVar8 + 0x132) = *(undefined1 *)(uVar8 + 4);
    if (*(char *)(uVar8 + 4) == -0x70) {
      *(undefined1 *)(uVar8 + 0x131) = 4;
      uVar12 = VectorFloatToUnsigned((*pfRam0801675c + fRam08016760) * 10.0,3);
      uVar7 = (undefined1)uVar12;
LAB_0801672a:
      *(undefined1 *)(uVar8 + 0x133) = uVar7;
      iVar4 = DAT_08020044;
      if ((*DAT_08020040 == '\x01') && (*(char *)(*(int *)(DAT_08020044 + 0x1c) + 0x262) == '\x01'))
      {
        FUN_08017e04();
      }
      if ((*DAT_08020048 == '\x01') && (*(char *)(*(int *)(iVar4 + 0x1c) + 0x262) == '\x02')) {
        FUN_08017e1c();
      }
      if ((*DAT_0802004c == '\x01') && (*(char *)(*(int *)(iVar4 + 0x1c) + 0x262) == '\x03')) {
        FUN_08017e34();
      }
      if ((*DAT_08020050 == '\x01') && (*(char *)(*(int *)(iVar4 + 0x1c) + 0x262) == '\x04')) {
        FUN_08017e4c();
      }
      if ((*DAT_08020054 == '\x01') && (*(char *)(*(int *)(iVar4 + 0x1c) + 0x262) == '\x05')) {
        FUN_08017e64();
      }
      if ((*DAT_08020058 == '\x01') && (*(char *)(*(int *)(iVar4 + 0x1c) + 0x262) == '\x06')) {
        FUN_08017e70();
      }
      iVar9 = *(int *)(iVar4 + 0x1c);
      *(undefined1 *)(iVar9 + 0x12e) = 0xeb;
      *(undefined1 *)(iVar9 + 0x12f) = 1;
      *(undefined1 *)(iVar9 + 0x130) = 1;
      uVar7 = FUN_08016658(iVar9 + 0x131,*(char *)(iVar9 + 0x131) + -1);
      *(undefined1 *)
       ((uint)*(byte *)(*(int *)(iVar4 + 0x1c) + 0x131) + *(int *)(iVar4 + 0x1c) + 0x130) = uVar7;
      *(undefined1 *)
       ((uint)*(byte *)(*(int *)(iVar4 + 0x1c) + 0x131) + *(int *)(iVar4 + 0x1c) + 0x131) = 0xf5;
      *(ushort *)(*(int *)(iVar4 + 0x1c) + 0x25a) = *(byte *)(*(int *)(iVar4 + 0x1c) + 0x131) + 4;
      thunk_FUN_0800a8b8();
      puVar5 = DAT_08020060;
      if ((*DAT_0802005c != '\0') && (*(char *)(*(int *)(iVar4 + 0x1c) + 0x262) == '\x01')) {
        *DAT_08020060 = *DAT_08020060 & 0xffdf;
        *puVar5 = *puVar5 | 0x80;
      }
      puVar5 = DAT_08020068;
      if ((*DAT_08020064 != '\0') && (*(char *)(*(int *)(iVar4 + 0x1c) + 0x262) == '\x02')) {
        *DAT_08020068 = *DAT_08020068 & 0xffdf;
        *puVar5 = *puVar5 | 0x80;
      }
      uVar12 = DAT_08020070;
      if ((*DAT_0802006c != '\0') && (*(char *)(*(int *)(iVar4 + 0x1c) + 0x262) == '\x03')) {
        FUN_08020654(DAT_08020070,0x525,0);
        FUN_08020654(uVar12,0x727,1);
      }
      uVar12 = DAT_08020078;
      if ((*DAT_08020074 != '\0') && (*(char *)(*(int *)(iVar4 + 0x1c) + 0x262) == '\x04')) {
        FUN_08020654(DAT_08020078,0x525,0);
        FUN_08020654(uVar12,0x727,1);
      }
      uVar12 = DAT_08020080;
      if ((*DAT_0802007c != '\0') && (*(char *)(*(int *)(iVar4 + 0x1c) + 0x262) == '\x05')) {
        FUN_08020654(DAT_08020080,0x525,0);
        FUN_08020654(uVar12,0x727,1);
      }
      uVar12 = DAT_08020088;
      uVar8 = 0;
      if ((*DAT_08020084 == '\0') ||
         (uVar8 = (uint)*(byte *)(*(int *)(iVar4 + 0x1c) + 0x262), uVar8 != 6)) {
        return uVar8;
      }
      FUN_08020654(DAT_08020088,0x525,0);
      uVar8 = FUN_08020654(uVar12,0x727,1);
      return uVar8;
    }
  }
  else if ((*(char *)(uVar8 + 2) == '\0') &&
          (*(undefined1 *)(uVar8 + 0x132) = 0x80, *(char *)(uVar8 + 4) == -0x80)) {
    if (*(char *)(uVar8 + 5) == '\"') {
      *(undefined1 *)(uVar8 + 0x131) = 4;
      uVar7 = 0x33;
      goto LAB_0801672a;
    }
    if (*(char *)(uVar8 + 5) == 'U') {
      FUN_0801975c();
      FUN_08019844(0,100);
      if (*(char *)(iVar4 + 1) == '\0') {
        FUN_0800c8f4();
        FUN_0800ac9c();
        FUN_08012720(0x5a,0xfe,1);
        FUN_08022f60();
        uVar8 = DAT_0801678c;
        coprocessor_store(0,in_cr14,unaff_r8);
        uVar10 = extraout_r1;
        uVar11 = extraout_r3 >> 9;
        if (SBORROW4(unaff_r7,0xfe)) {
          pcVar1 = (char *)(*(int *)(DAT_0801678c + 0x1c) + 3);
          bVar6 = FUN_08016658(pcVar1,*pcVar1 + -1);
          uVar10 = (uint)bVar6;
          uVar11 = uVar8;
        }
        if (uVar10 == *(byte *)((uint)*(byte *)(*(int *)(uVar11 + 0x1c) + 3) +
                               *(int *)(uVar11 + 0x1c) + 2)) {
          return 1;
        }
        return 0;
      }
      FUN_08012720(0x5a,0xfe,1);
      FUN_08017c1c();
      disableIRQinterrupts();
      uVar8 = 0x8000000;
      if ((_DAT_08000000 & uRam08016750) == uRam08016754) {
        *puRam08016758 = 0x8000000;
        pcVar3 = _DAT_08000004;
        uVar8 = _DAT_08000000;
        bVar2 = (bool)isCurrentModePrivileged();
        if (bVar2) {
          setMainStackPointer(_DAT_08000000);
        }
        *(code **)(iVar4 + 0x20) = _DAT_08000004;
        uVar8 = (*pcVar3)(pcVar3,uVar8);
      }
      enableIRQinterrupts();
    }
  }
  return uVar8;
}



// ---------------------------------------------------------------------------
// Function: FUN_08016764 at 0x08016764
// ---------------------------------------------------------------------------

undefined4 FUN_08016764(void)

{
  char *pcVar1;
  int iVar2;
  char cVar3;
  
  iVar2 = DAT_0801678c;
  pcVar1 = (char *)(*(int *)(DAT_0801678c + 0x1c) + 3);
  cVar3 = FUN_08016658(pcVar1,*pcVar1 + -1);
  if (cVar3 == *(char *)((uint)*(byte *)(*(int *)(iVar2 + 0x1c) + 3) + *(int *)(iVar2 + 0x1c) + 2))
  {
    return 1;
  }
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_08016790 at 0x08016790
// ---------------------------------------------------------------------------

void FUN_08016790(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  byte bVar5;
  
  iVar2 = DAT_08016848;
  iVar1 = DAT_08016844;
  if ((*(char *)(DAT_08016844 + 0x16) != '\0') && (*(char *)(DAT_08016848 + 0x41) != '\0')) {
    *(short *)(DAT_08016844 + 0x12) = *(short *)(DAT_08016844 + 0x12) + 1;
    puVar4 = DAT_08016850;
    iVar3 = DAT_0801684c;
    if ((*(ushort *)(iVar1 + 0x14) <= *(ushort *)(iVar1 + 0x12)) ||
       (((*(char *)(iVar2 + 0x3b) != '\0' || (*(char *)(iVar2 + 0x39) != '\0')) ||
        (*(char *)(iVar2 + 0x1b) != '\0')))) {
      *DAT_08016850 = 0;
      *(undefined1 *)(iVar2 + 0x41) = 0;
      *(undefined2 *)(iVar1 + 0x12) = 0;
      *(undefined1 *)(iVar2 + 0x3f) = 0;
      *(undefined4 *)(iVar1 + 8) = 0;
      *(undefined4 *)(iVar1 + 0xc) = 0;
      *(undefined2 *)(iVar1 + 0x10) = 0;
      *(undefined1 *)(iVar3 + 0x10) = 0;
      FUN_08008c40();
      for (bVar5 = 0; bVar5 < 0x32; bVar5 = bVar5 + 1) {
        FUN_0801ca54();
        FUN_0801f89c();
        FUN_0800db18(10);
      }
      *puVar4 = 1;
      return;
    }
    if (*(char *)(iVar2 + 0x3d) == '\0') {
      if (*(float *)(DAT_08016854 + 0xc) < *(float *)(DAT_08016854 + 4)) {
        *(undefined1 *)(iVar2 + 0x41) = 0;
        *(undefined2 *)(iVar1 + 0x12) = 0;
        FUN_08008c40();
        *(undefined1 *)(iVar2 + 0x3f) = 0;
        *(undefined4 *)(iVar1 + 8) = 0;
        *(undefined4 *)(iVar1 + 0xc) = 0;
        *(undefined2 *)(iVar1 + 0x10) = 0;
        *(undefined1 *)(iVar3 + 0x10) = 0;
      }
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08016898 at 0x08016898
// ---------------------------------------------------------------------------

void FUN_08016898(void)

{
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801689c at 0x0801689c
// ---------------------------------------------------------------------------

void FUN_0801689c(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  FUN_0800f610(0);
  *(undefined1 *)(DAT_08016960 + 2) = 1;
  *DAT_08016964 = 0x80;
  iVar1 = DAT_08016968;
  *(undefined4 *)(DAT_08016968 + 0x14) = 1;
  FUN_08019544();
  FUN_0800a508();
  FUN_0800d960();
  *(undefined4 *)(iVar1 + 0x14) = 0x80;
  *(undefined4 *)(iVar1 + 0x10) = 0x20;
  FUN_0800c8f4();
  FUN_0800ac9c();
  uVar2 = DAT_0801696c;
  FUN_080102cc(DAT_0801696c,1);
  puVar3 = DAT_08016964 + -5;
  FUN_080102cc(puVar3,2);
  FUN_080102cc(uVar2,4);
  FUN_080102cc(puVar3,8);
  FUN_080102cc(iVar1,0x10);
  FUN_080102cc(uVar2,0x20);
  FUN_080102cc(uVar2,0x80);
  FUN_080102cc(uVar2,0x8000);
  FUN_0800f3d0(1);
  FUN_0800f3d0(2);
  FUN_0800f3d0(4);
  FUN_0800f3d0(8);
  FUN_0800f3d0(0x10);
  FUN_0800f3d0(0x20);
  FUN_0800f3d0(0x80);
  FUN_0800f3d0(0x8000);
  FUN_0800db18(0x14);
  FUN_0800ffa8(puVar3,2,0x48,0x10);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08016970 at 0x08016970
// ---------------------------------------------------------------------------

undefined1 FUN_08016970(void)

{
  undefined1 uVar1;
  
  if ((*DAT_08016984 != '\0') || (uVar1 = 0, *DAT_08016988 != '\0')) {
    uVar1 = 1;
  }
  return uVar1;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801698c at 0x0801698c
// ---------------------------------------------------------------------------

void FUN_0801698c(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  FUN_0800f610(0);
  if (*(char *)(DAT_08016a4c + 2) == '\0') {
    *(undefined1 *)(DAT_08016a4c + 2) = 1;
    FUN_08016360();
    FUN_08019544();
    FUN_0800a508();
    FUN_0800d960();
    iVar1 = DAT_08016a50;
    *(undefined4 *)(DAT_08016a50 + 0x10) = 0x20;
    *(undefined4 *)(iVar1 + 0x14) = 0x80;
    *(undefined4 *)(iVar1 + 0x14) = 0x1000;
    puVar2 = DAT_08016a54;
    *DAT_08016a54 = 0x10;
    *DAT_08016a58 = 0x8000;
    *puVar2 = 8;
    *DAT_08016a5c = 0;
    FUN_0800db18(0x14);
    puVar2 = DAT_08016a54 + -5;
    FUN_0800ffa8(puVar2,1,4,0x10);
    puVar3 = DAT_08016a58 + -5;
    FUN_0800ffa8(puVar3,2,4,0x10);
    FUN_0800ffa8(puVar2,4,4,0x10);
    FUN_0800ffa8(puVar3,8,4,0xc);
    FUN_0800ffa8(iVar1,0x10,4);
    FUN_0800ffa8(puVar2,0x20,4,0x10);
    FUN_0800ffa8(puVar2,0x80,4,0x10);
    FUN_0800ffa8(puVar2,0x8000,4,0x10);
    return;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08016a60 at 0x08016a60
// ---------------------------------------------------------------------------

void FUN_08016a60(void)

{
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  short sVar7;
  int iVar8;
  undefined4 uVar9;
  byte *pbVar10;
  byte *pbVar11;
  int iVar12;
  bool bVar13;
  
  FUN_08017a20();
  if (*DAT_08016cb0 != '\0') {
    FUN_08009d34();
  }
  pbVar10 = DAT_08016cb4;
  DAT_08016cb4[0x3d] = 0;
  iVar12 = DAT_08016cb8;
  if ((((pbVar10[0x3a] == 0) && (pbVar10[0x3b] == 0)) && (pbVar10[0x3f] == 0)) &&
     ((iVar8 = FUN_08016970(), iVar8 == 0 && (*DAT_08016cbc == '\0')))) {
    if (((pbVar10[0x12] & 1) != 0) || (pbVar10[0x13] == 0)) {
      pbVar11 = pbVar10;
      if ((int)((uint)pbVar10[0x12] << 0x1e) < 0) goto LAB_08016abe;
      bVar13 = pbVar10[0x17] == 0;
      do {
        pbVar11 = pbVar10;
        if (!bVar13) {
          return;
        }
LAB_08016abe:
        pcVar6 = DAT_08016ce4;
        pcVar5 = DAT_08016ce0;
        pcVar4 = DAT_08016cdc;
        pcVar3 = DAT_08016cd8;
        pcVar1 = DAT_08016cd4;
        pbVar10 = DAT_08016cd0;
        if (((pbVar11[0x1b] & 1) == 0) && (pbVar11[0x1c] != 0)) {
          return;
        }
        if ((-1 < (int)((uint)pbVar11[0x1b] << 0x1e)) && (pbVar11[0x21] != 0)) {
          return;
        }
        if ((pbVar11[0x12] != 0) && (pbVar11[0x14] != 0)) {
          return;
        }
        if ((pbVar11[0x1b] != 0) && (pbVar11[0x1d] != 0)) {
          return;
        }
        if (((int)((uint)pbVar11[0x12] << 0x1e) < 0) && (pbVar11[0x18] != 0)) {
          return;
        }
        if (((int)((uint)pbVar11[0x1b] << 0x1e) < 0) && (pbVar11[0x22] != 0)) {
          return;
        }
        if (*pbVar11 == 0) {
          if (pbVar11[1] != 0) {
            return;
          }
          if (pbVar11[3] != 0) {
            return;
          }
        }
        if (((*pbVar11 & 1) != 0) && (pbVar11[2] != 0)) {
          return;
        }
        if (((int)((uint)*pbVar11 << 0x1e) < 0) && (pbVar11[4] != 0)) {
          return;
        }
        if (*(short *)(DAT_08016cc4 + 0x38) != 0) {
          return;
        }
        if (*(short *)(DAT_08016cc4 + 0x48) != 0) {
          return;
        }
        if (*(short *)(DAT_08016cc8 + 0x38) != 0) {
          return;
        }
        if (*(short *)(DAT_08016cc8 + 0x48) != 0) {
          return;
        }
        if (*(short *)(DAT_08016ccc + 0x36) != 0) {
          return;
        }
        if (*(short *)(DAT_08016ccc + 0x32) != 0) {
          return;
        }
        if (*(short *)(DAT_08016ccc + 0x38) != 0) {
          return;
        }
        if (*(short *)(DAT_08016ccc + 0x34) != 0) {
          return;
        }
        if ((pbVar11[0x1b] & 3) != 0) {
          if (*DAT_08016ce8 == '\x01') {
            if ((((*DAT_08016cd0 == 0) || (*DAT_08016cd4 == '\0')) || (*DAT_08016cd8 == '\0')) ||
               (((*DAT_08016cdc == '\0' || (*DAT_08016ce0 == '\0')) ||
                ((*DAT_08016ce4 == '\0' || ((*DAT_08016cf0 == '\0' || (*DAT_08016cf4 == '\0'))))))))
            {
              sVar7 = *(short *)(iVar12 + 8) + 1;
            }
            else {
              sVar7 = *(short *)(iVar12 + 8) + 10;
            }
            *(short *)(iVar12 + 8) = sVar7;
            if ((uint)(*DAT_08016cf8 * 10) <= (uint)*(ushort *)(iVar12 + 8)) {
              if (*(char *)(iVar12 + 2) == '\0') {
                *(undefined1 *)(iVar12 + 2) = 1;
                FUN_08019844(0,3);
                FUN_080196d0(0x1e4);
              }
              *(undefined2 *)(iVar12 + 8) = 0;
              if (*DAT_08016cb0 == '\x01') {
                FUN_08009e18();
              }
              else {
                FUN_08016e44();
              }
            }
          }
          if (*pbVar10 == 0) {
            return;
          }
          if (*pcVar1 == '\0') {
            return;
          }
          if (*pcVar3 == '\0') {
            return;
          }
          if (*pcVar4 == '\0') {
            return;
          }
          if (*pcVar5 == '\0') {
            return;
          }
          if (*pcVar6 == '\0') {
            return;
          }
          if (*DAT_08016cf0 == '\0') {
            return;
          }
          if (*DAT_08016cf4 == '\0') {
            return;
          }
          uVar9 = 1;
LAB_08016ca2:
          FUN_08016ee8(uVar9);
          return;
        }
        *(undefined2 *)(iVar12 + 8) = 0;
        pcVar2 = DAT_08016cc0;
        iVar12 = *DAT_08016cec * 9;
        if ((uint)(*DAT_08016cec * 100) <= *(uint *)(DAT_08016cc0 + 4)) {
          *DAT_08016cc0 = '\0';
          if (*pbVar10 == 0) {
            return;
          }
          if (*pcVar1 == '\0') {
            return;
          }
          if (*pcVar3 == '\0') {
            return;
          }
          if (*pcVar4 == '\0') {
            return;
          }
          if (*pcVar5 == '\0') {
            return;
          }
          if (*pcVar6 == '\0') {
            return;
          }
          if (*DAT_08016cf0 == '\0') {
            return;
          }
          if (*DAT_08016cf4 == '\0') {
            return;
          }
          uVar9 = 0;
          goto LAB_08016ca2;
        }
        bVar13 = false;
      } while (*DAT_08016cc0 != '\0');
      *DAT_08016cc0 = '\x01';
      pcVar2[4] = '\0';
      pcVar2[5] = '\0';
      pcVar2[6] = '\0';
      pcVar2[7] = '\0';
    }
  }
  else {
    pcVar1 = DAT_08016cc0;
    *DAT_08016cc0 = '\0';
    pcVar1[4] = '\0';
    pcVar1[5] = '\0';
    pcVar1[6] = '\0';
    pcVar1[7] = '\0';
    *(undefined2 *)(iVar12 + 8) = 0;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08016cfc at 0x08016cfc
// ---------------------------------------------------------------------------

int FUN_08016cfc(undefined1 param_1)

{
  uint uVar1;
  byte bVar2;
  short sVar3;
  float fVar4;
  uint in_fpscr;
  float fVar5;
  undefined8 uVar6;
  short local_18;
  float local_14;
  short local_10;
  
  for (bVar2 = 0; bVar2 < 5; bVar2 = bVar2 + 1) {
    FUN_080089c0(param_1);
  }
  local_10 = 0;
  for (local_14._0_1_ = 0; local_14._0_1_ < 10; local_14._0_1_ = local_14._0_1_ + 1) {
    sVar3 = FUN_080089c0(param_1);
    local_10 = sVar3 + local_10;
  }
  uVar6 = FUN_08008548(local_10);
  FUN_08008448((int)uVar6,(int)((ulonglong)uVar6 >> 0x20),(int)DAT_08016e24,
               (int)((ulonglong)DAT_08016e24 >> 0x20));
  fVar4 = (float)FUN_08008658();
  fVar5 = (float)VectorUnsignedToFloat((uint)*DAT_08016e2c,(byte)(in_fpscr >> 0x16) & 3);
  local_14 = (fVar4 * fVar5) / (DAT_08016e30 - fVar4);
  local_18 = 0xa0;
  do {
    if (local_18 < 0) {
LAB_08016de8:
      if ((local_18 == 0) || (local_18 < 0)) {
        local_14 = DAT_08016e38;
      }
      if (DAT_08016e3c < (int)local_14) {
        local_14 = DAT_08016e40;
      }
      return (int)(short)(int)local_14;
    }
    fVar4 = *(float *)(*DAT_08016e34 + local_18 * 4);
    uVar1 = in_fpscr & 0xfffffff | (uint)(fVar4 < local_14) << 0x1f;
    in_fpscr = uVar1 | (uint)(NAN(fVar4) || NAN(local_14)) << 0x1c;
    if ((byte)(uVar1 >> 0x1f) == ((byte)(in_fpscr >> 0x1c) & 1)) {
      local_14 = (float)VectorSignedToFloat(local_18 + -0x28,(byte)(in_fpscr >> 0x16) & 3);
      goto LAB_08016de8;
    }
    local_18 = local_18 + -1;
  } while( true );
}



// ---------------------------------------------------------------------------
// Function: FUN_08016e44 at 0x08016e44
// ---------------------------------------------------------------------------

void FUN_08016e44(void)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  uint in_r3;
  undefined4 unaff_r4;
  undefined4 unaff_r5;
  undefined4 unaff_r6;
  undefined4 unaff_lr;
  undefined8 uVar5;
  uint local_1c;
  
  iVar2 = DAT_08016ed8;
  cVar1 = '\0';
  local_1c = in_r3 & 0xffffff00;
  *(undefined1 *)(DAT_08016ed8 + 0x3e) = 0;
  FUN_0800ac9c();
  FUN_0800c8f4();
  FUN_0800c500();
  FUN_0800c5ec();
  FUN_0802008c();
  FUN_0801689c();
  FUN_08011458();
  FUN_08021858();
  FUN_08009902();
  puVar3 = DAT_08016edc;
  do {
    *puVar3 = 0xaaaa;
    iVar4 = FUN_0801efb8();
    if (iVar4 == 0) {
      cVar1 = '\x01';
      break;
    }
    FUN_080112fc();
    FUN_0800db18(1);
    iVar4 = FUN_08017af0();
  } while (iVar4 != 1);
  FUN_080219cc();
  *(undefined2 *)(DAT_08016ee0 + 4) = 0;
  if (cVar1 != '\x01') {
    *(undefined1 *)(iVar2 + 0x3d) = 1;
  }
  FUN_08021864();
  FUN_08011464();
  uVar5 = FUN_080098f4();
  if ((int)uVar5 == 0) {
    *DAT_08016ee4 = 1;
  }
  iVar2 = DAT_08016894;
  *(undefined4 *)(DAT_08016894 + 0x14) = 1;
  FUN_0800a634(1,(int)((ulonglong)uVar5 >> 0x20),cVar1,local_1c,unaff_r4,unaff_r5,unaff_r6,unaff_lr)
  ;
  FUN_08015b28(1,0x2580);
  FUN_08015b28(2,0x2580);
  FUN_08015b28(4,0x2580);
  *(undefined4 *)(iVar2 + 0x10) = 0x20;
  *(undefined4 *)(iVar2 + 0x14) = 0x80;
  FUN_0800c8f4();
  FUN_0800ac9c();
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08016ee8 at 0x08016ee8
// ---------------------------------------------------------------------------

void FUN_08016ee8(void)

{
  bool bVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = DAT_08016fcc;
  bVar1 = false;
  *(undefined1 *)(DAT_08016fcc + 0x3e) = 0;
  FUN_0800c500();
  FUN_0800c5ec();
  FUN_080202f4();
  FUN_0801698c();
  FUN_08011458();
  FUN_08021858();
  iVar2 = DAT_08016fdc;
  puVar3 = DAT_08016fd8;
  if ((*DAT_08016fd0 == '\0') && (*DAT_08016fd4 == '\0')) {
    FUN_08009902();
    iVar2 = DAT_08016fdc;
    puVar3 = DAT_08016fd8;
  }
  do {
    *puVar3 = 0xaaaa;
    iVar5 = FUN_0801efb8();
    if ((iVar5 == 0) || (*DAT_08016fe0 != '\0')) {
      bVar1 = true;
LAB_08016f40:
      FUN_080219cc();
      *(undefined2 *)(iVar2 + 4) = 0;
      if (!bVar1) {
        *(undefined1 *)(iVar4 + 0x3d) = 1;
      }
      FUN_08021864();
      FUN_08011464();
      FUN_08016898();
      return;
    }
    FUN_080112fc();
    FUN_0800db18(1);
    *(short *)(iVar2 + 4) = *(short *)(iVar2 + 4) + 1;
    iVar5 = FUN_0801f35c();
    if (iVar5 == 1) goto LAB_08016f40;
    if (*DAT_08016fe4 <= *(ushort *)(iVar2 + 4)) {
      *(undefined2 *)(iVar2 + 4) = 0;
      goto LAB_08016f40;
    }
    if (((((*DAT_08016fe8 == '\0') || (*DAT_08016fec == '\0')) || (*DAT_08016ff0 == '\0')) ||
        ((*DAT_08016ff4 == '\0' || (*DAT_08016ff8 == '\0')))) ||
       ((*DAT_08016ffc == '\0' || ((*DAT_08017000 == '\0' || (*DAT_08017004 == '\0'))))))
    goto LAB_08016f40;
  } while( true );
}



// ---------------------------------------------------------------------------
// Function: FUN_08017168 at 0x08017168
// ---------------------------------------------------------------------------

void FUN_08017168(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  iVar1 = DAT_08017214;
  if ((0x78 < *(short *)(DAT_08017214 + 0x42)) || (*(short *)(DAT_08017214 + 0x42) < 0x32)) {
    *(undefined2 *)(DAT_08017214 + 0x42) = 100;
  }
  iVar3 = DAT_0801721c;
  iVar2 = DAT_08017218;
  if ((int)((uint)*(byte *)(DAT_08017218 + 0x51) << 0x1d) < 0) {
    if (*(char *)(DAT_08017218 + 0x51) != '\0') {
      if (*(short *)(iVar1 + 0x44) < *(short *)(iVar1 + 0x40)) {
        *(undefined1 *)(DAT_0801721c + 0x12) = 0;
        return;
      }
      *(char *)(DAT_0801721c + 0x12) = *(char *)(DAT_0801721c + 0x12) + '\x01';
      if (*(ushort *)(iVar1 + 0x46) <= (ushort)*(byte *)(iVar3 + 0x12)) {
        *(undefined1 *)(iVar3 + 0x12) = 0;
        *(undefined1 *)(iVar2 + 0x51) = 0;
        FUN_0800c940();
        FUN_0800acd8();
        uVar5 = 10;
        uVar4 = 0x14;
        goto LAB_08017206;
      }
    }
  }
  else if (*(short *)(iVar1 + 0x40) < *(short *)(iVar1 + 0x42)) {
    *(undefined1 *)(DAT_0801721c + 0x11) = 0;
  }
  else {
    *(char *)(DAT_0801721c + 0x11) = *(char *)(DAT_0801721c + 0x11) + '\x01';
    if (*(ushort *)(iVar1 + 0x46) <= (ushort)*(byte *)(iVar3 + 0x11)) {
      *(undefined1 *)(iVar3 + 0x11) = 0;
      *(undefined1 *)(iVar2 + 0x51) = 4;
      FUN_0800c8f4();
      FUN_0800ac9c();
      FUN_08019844(0x13,8);
      uVar5 = 9;
      uVar4 = 0x13;
LAB_08017206:
      FUN_08019844(uVar4,uVar5);
      return;
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: MemManage_Handler at 0x08017220
// ---------------------------------------------------------------------------

void MemManage_Handler(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ---------------------------------------------------------------------------
// Function: FUN_08017304 at 0x08017304
// ---------------------------------------------------------------------------

void FUN_08017304(void)

{
  int iVar1;
  int iVar2;
  uint local_10;
  
  iVar1 = DAT_080173a4;
  iVar2 = *(int *)(DAT_080173a4 + 4);
  if (iVar2 != 0x101) {
    if (iVar2 == 0x102) goto LAB_0801736e;
    if ((((iVar2 != 0x103) && (iVar2 != 0x201)) && (iVar2 != 0x202)) && (iVar2 != 0x203)) {
      return;
    }
  }
  if (iVar2 == 0x103) {
    *(undefined4 *)(DAT_080173a8 + 0x24) = 0x103;
    iVar2 = DAT_080173a8 + 0x38;
    local_10 = 0;
    while ((byte)local_10 < 8) {
      *(undefined1 *)(iVar2 + local_10) = *(undefined1 *)(local_10 + iVar1 + 0xb);
      local_10 = (uint)(byte)((byte)local_10 + 1);
    }
    return;
  }
LAB_0801736e:
  if (*(int *)(DAT_080173a8 + 0x20) != 0) {
    return;
  }
  *(int *)(DAT_080173a8 + 0x20) = iVar2;
  iVar2 = DAT_080173a8 + 0x30;
  local_10 = 0;
  while ((byte)local_10 < 8) {
    *(undefined1 *)(iVar2 + local_10) = *(undefined1 *)(local_10 + iVar1 + 0xb);
    local_10 = (uint)(byte)((byte)local_10 + 1);
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: NMI_Handler at 0x080173ac
// ---------------------------------------------------------------------------

void NMI_Handler(void)

{
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080173ae at 0x080173ae
// ---------------------------------------------------------------------------

void FUN_080173ae(void)

{
  undefined4 in_r3;
  undefined4 local_10;
  
  local_10 = in_r3;
  FUN_08017568(0x500);
  local_10 = 0x1010125;
  FUN_08017504(&local_10);
  local_10._0_1_ = 0x26;
  FUN_08017504(&local_10);
  local_10._0_1_ = 0x27;
  FUN_08017504(&local_10);
  local_10._0_1_ = 0x34;
  FUN_08017504(&local_10);
  local_10._0_1_ = 0x35;
  FUN_08017504(&local_10);
  local_10._0_1_ = 0x4a;
  FUN_08017504(&local_10);
  local_10 = CONCAT31(local_10._1_3_,0x4b);
  FUN_08017504(&local_10);
  local_10 = 0x1000115;
  FUN_08017504(&local_10);
  local_10._0_1_ = 0x13;
  FUN_08017504(&local_10);
  local_10._0_1_ = 0x14;
  FUN_08017504(&local_10);
  local_10._0_1_ = 0x40;
  FUN_08017504(&local_10);
  local_10._0_1_ = 0x41;
  FUN_08017504(&local_10);
  local_10 = CONCAT31(local_10._1_3_,0x3f);
  FUN_08017504(&local_10);
  local_10 = 0x1030306;
  FUN_08017504(&local_10);
  local_10._0_1_ = 7;
  FUN_08017504(&local_10);
  local_10._0_1_ = 8;
  FUN_08017504(&local_10);
  local_10._0_1_ = 9;
  FUN_08017504(&local_10);
  local_10._0_1_ = 10;
  FUN_08017504(&local_10);
  local_10._0_1_ = 0x17;
  FUN_08017504(&local_10);
  local_10 = CONCAT31(local_10._1_3_,0x28);
  FUN_08017504(&local_10);
  local_10 = 0x1010203;
  FUN_08017504(&local_10);
  local_10 = 0x1020229;
  FUN_08017504(&local_10);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017504 at 0x08017504
// ---------------------------------------------------------------------------

void FUN_08017504(byte *param_1)

{
  byte bVar1;
  uint uVar2;
  
  bVar1 = *param_1;
  if (param_1[3] == 0) {
    *(int *)(&DAT_e000e180 + (uint)(bVar1 >> 5) * 4) = 1 << (bVar1 & 0x1f);
    return;
  }
  uVar2 = 0x700 - (*DAT_08017564 & 0x700) >> 8;
  (&DAT_e000e400)[bVar1] =
       (char)(((uint)param_1[2] & 0xfU >> (uVar2 & 0xff) | (uint)param_1[1] << (4 - uVar2 & 0xff))
             << 4);
  *(int *)(&DAT_e000e100 + (uint)(*param_1 >> 5) * 4) = 1 << (*param_1 & 0x1f);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017568 at 0x08017568
// ---------------------------------------------------------------------------

void FUN_08017568(uint param_1)

{
  *DAT_08017578 = param_1 | DAT_08017574;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801757c at 0x0801757c
// ---------------------------------------------------------------------------

void FUN_0801757c(void)

{
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017580 at 0x08017580
// ---------------------------------------------------------------------------

void FUN_08017580(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  
  iVar4 = DAT_08017718;
  iVar3 = DAT_08017714;
  iVar2 = DAT_08017710;
  iVar1 = DAT_0801770c;
  if (*(char *)(DAT_0801770c + 0x18) != '\0') {
    if (*(char *)(DAT_08017710 + 0x48) == '\0') {
      if (*(float *)(DAT_08017718 + 0x14) < *(float *)(DAT_0801770c + 0x1c)) {
        *(undefined1 *)(DAT_08017714 + 0x15) = 0;
      }
      else {
        *(char *)(DAT_08017714 + 0x15) = *(char *)(DAT_08017714 + 0x15) + '\x01';
        if (*DAT_08017724 <= (ushort)*(byte *)(iVar3 + 0x15)) {
          *(undefined1 *)(iVar3 + 0x15) = 0;
          if (*(char *)(iVar2 + 0x48) == '\0') {
            FUN_08019844(0,0x1a);
          }
          *(undefined1 *)(iVar2 + 0x48) = 1;
        }
      }
    }
    else if (*(char *)(DAT_08017710 + 0x48) != '\0') {
      if (*DAT_0801771c < *(float *)(DAT_08017718 + 0x14)) {
        *(undefined1 *)(DAT_08017714 + 0x16) = 0;
      }
      else {
        *(char *)(DAT_08017714 + 0x16) = *(char *)(DAT_08017714 + 0x16) + '\x01';
        if (*DAT_08017720 <= (ushort)*(byte *)(iVar3 + 0x16)) {
          *(undefined1 *)(iVar3 + 0x16) = 0;
          *(undefined1 *)(iVar2 + 0x48) = 0;
          FUN_08019844(0,0x71);
        }
      }
    }
    if (*(char *)(iVar2 + 0x49) == '\0') {
      if (*(float *)(iVar4 + 0x10) < *(float *)(iVar1 + 0x20)) {
        *(undefined1 *)(iVar3 + 0x17) = 0;
      }
      else {
        *(char *)(iVar3 + 0x17) = *(char *)(iVar3 + 0x17) + '\x01';
        if (*DAT_08017730 <= (ushort)*(byte *)(iVar3 + 0x17)) {
          *(undefined1 *)(iVar3 + 0x17) = 0;
          if (*(char *)(iVar2 + 0x49) == '\0') {
            FUN_08019844(0,0x1b);
          }
          *(undefined1 *)(iVar2 + 0x49) = 1;
        }
      }
    }
    else if (*(char *)(iVar2 + 0x49) != '\0') {
      if (*DAT_08017728 < *(float *)(iVar4 + 0x10)) {
        *(undefined1 *)(iVar3 + 0x18) = 0;
      }
      else {
        *(char *)(iVar3 + 0x18) = *(char *)(iVar3 + 0x18) + '\x01';
        if (*DAT_0801772c <= (ushort)*(byte *)(iVar3 + 0x18)) {
          *(undefined1 *)(iVar3 + 0x18) = 0;
          *(undefined1 *)(iVar2 + 0x49) = 0;
          FUN_08019844(0,0x72);
        }
      }
    }
  }
  if (*(char *)(DAT_08017734 + 0x5a) != '\0') {
    if (*(char *)(iVar2 + 0x11) == '\0') {
      if (*(short *)(DAT_08017734 + 0x40) < *(short *)(DAT_08017734 + 0x56)) {
        *(undefined1 *)(iVar3 + 0x19) = 0;
      }
      else {
        *(char *)(iVar3 + 0x19) = *(char *)(iVar3 + 0x19) + '\x01';
        if (*DAT_0801773c <= (ushort)*(byte *)(iVar3 + 0x19)) {
          *(undefined1 *)(iVar3 + 0x19) = 0;
          *(undefined1 *)(iVar2 + 0x11) = 1;
          uVar5 = 0x73;
LAB_080176ce:
          FUN_08019844(0,uVar5);
          return;
        }
      }
    }
    else if (*(char *)(iVar2 + 0x11) != '\0') {
      if (*(short *)(DAT_08017734 + 0x58) < *(short *)(DAT_08017734 + 0x40)) {
        *(undefined1 *)(iVar3 + 0x1a) = 0;
      }
      else {
        *(char *)(iVar3 + 0x1a) = *(char *)(iVar3 + 0x1a) + '\x01';
        if (*DAT_08017738 <= (ushort)*(byte *)(iVar3 + 0x1a)) {
          *(undefined1 *)(iVar3 + 0x1a) = 0;
          *(undefined1 *)(iVar2 + 0x11) = 0;
          uVar5 = 0x74;
          goto LAB_080176ce;
        }
      }
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017740 at 0x08017740
// ---------------------------------------------------------------------------

void FUN_08017740(void)

{
  int iVar1;
  
  iVar1 = DAT_08017774;
  if ((int)((uint)*(byte *)(DAT_08017774 + 0x39) << 0x1e) < 0) {
    FUN_08019844(0xd,10);
  }
  *(byte *)(iVar1 + 0x39) = *(byte *)(iVar1 + 0x39) & 0xfd;
  *DAT_08017778 = 0;
  *(undefined2 *)(DAT_0801777c + 0x16) = 0;
  FUN_0800c940();
  *(undefined1 *)(DAT_08017894 + 5) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017780 at 0x08017780
// ---------------------------------------------------------------------------

void FUN_08017780(void)

{
  float fVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  int iVar5;
  float local_28;
  byte local_24 [8];
  
  iVar2 = DAT_08017830;
  fVar1 = DAT_08017828;
  local_28 = DAT_08017828;
  if (((int)((uint)*(byte *)(DAT_0801782c + 0x39) << 0x1e) < 0) &&
     (iVar5 = FUN_08016638(), puVar4 = DAT_0801783c, iVar3 = DAT_08017838, iVar5 == 1)) {
    if (*DAT_08017834 == '\0') {
LAB_08017804:
      *(undefined2 *)(iVar3 + 0x260) = 0;
      *puVar4 = 0;
      *(short *)(iVar2 + 0x38) = *(short *)(iVar2 + 0x38) + 1;
      if (*(ushort *)(iVar2 + 0x38) < 0x1e) {
        return;
      }
      *(undefined2 *)(iVar2 + 0x38) = 0;
      FUN_08017740();
      return;
    }
    iVar5 = FUN_080122f0(0x51,local_24,1);
    if (iVar5 == 0) {
      return;
    }
    if ((int)((uint)local_24[0] << 0x18) < 0) {
      local_28 = fVar1;
      iVar5 = FUN_0800d3c4(&local_28);
      if (iVar5 == 0) {
        return;
      }
      if (*(float *)(DAT_08017840 + 0x114) * 0.5 < local_28) goto LAB_08017804;
    }
    else {
      FUN_08012720(0x51,local_24[0] | 0x80,1);
    }
  }
  *(undefined2 *)(iVar2 + 0x38) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017844 at 0x08017844
// ---------------------------------------------------------------------------

void FUN_08017844(void)

{
  int iVar1;
  
  iVar1 = DAT_0801787c;
  if (((*(char *)(DAT_0801787c + 6) == '\0') || (*DAT_08017880 != '\0')) ||
     ((*(byte *)(DAT_08017884 + 0x39) & 3) != 0)) {
    *(undefined1 *)(DAT_0801787c + 6) = 0;
    *(undefined2 *)(iVar1 + 0x3c) = 0;
  }
  else {
    *(short *)(DAT_0801787c + 0x3c) = *(short *)(DAT_0801787c + 0x3c) + 1;
    if (*(ushort *)(DAT_08017888 + 2) + 10 <= (uint)*(ushort *)(iVar1 + 0x3c)) {
      *(undefined2 *)(iVar1 + 0x3c) = 0;
      *(undefined1 *)(iVar1 + 6) = 0;
      return;
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801789a at 0x0801789a
// ---------------------------------------------------------------------------

void FUN_0801789a(void)

{
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801789c at 0x0801789c
// ---------------------------------------------------------------------------

void FUN_0801789c(undefined4 param_1,uint param_2,uint param_3,uint param_4)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  ushort uVar5;
  undefined4 local_28;
  uint local_24;
  uint local_20;
  
  iVar3 = DAT_0801795c;
  iVar2 = DAT_08017958;
  local_20 = param_4 & 0xffffff00;
  if ((*(char *)(DAT_08017958 + 0x1b) != '\0') && (*(char *)(DAT_08017958 + 0x4c) == '\0')) {
    *(undefined4 *)(DAT_0801795c + 0x10) = 0x1000;
    *DAT_08017960 = 0x10;
    local_28 = param_2 & 0xffff0000;
    local_24 = param_3 & 0xffffff00;
    while ((byte)local_24 < 10) {
      FUN_0800db18(10);
      if ((int)((uint)*(byte *)(iVar3 + 8) << 0x1e) < 0) {
        uVar5 = (short)local_28 + 1;
        local_28 = CONCAT22(local_28._2_2_,uVar5);
        if (2 < uVar5) {
          local_28 = (uint)local_28._2_2_ << 0x10;
          break;
        }
      }
      else {
        local_28 = (uint)local_28._2_2_ << 0x10;
      }
      local_24 = CONCAT31(local_24._1_3_,(byte)local_24 + 1);
    }
    puVar4 = DAT_08017960;
    *(undefined4 *)(iVar3 + 0x14) = 0x1000;
    puVar4[1] = 0x10;
    if ((local_24 & 0xff) < 10) {
      pbVar1 = (byte *)(iVar2 + 0x39);
      *pbVar1 = *pbVar1 | 1;
      FUN_08019844(0xb,8);
      FUN_080196d0(0x1e2,local_28,local_24,local_20);
      return;
    }
    if (*DAT_08017964 != '\0') {
      FUN_0800ceec();
      *(undefined1 *)(iVar2 + 0x4c) = 1;
      *(undefined1 *)(DAT_08017968 + 4) = 1;
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801796c at 0x0801796c
// ---------------------------------------------------------------------------

void FUN_0801796c(void)

{
  int iVar1;
  byte *pbVar2;
  
  pbVar2 = DAT_08017a14;
  iVar1 = DAT_08017a10;
  if (((*(byte *)(DAT_08017a10 + 4) & 1) == 0) || (DAT_08017a14[0x3a] != 0)) {
    *(undefined2 *)(DAT_08017a10 + 0xe) = 0;
LAB_080179da:
    *(undefined2 *)(iVar1 + 0x10) = 0;
    return;
  }
  *(short *)(DAT_08017a10 + 0xe) = *(short *)(DAT_08017a10 + 0xe) + 1;
  if (*(ushort *)(iVar1 + 0xe) < 0x1e) {
    if ((((pbVar2[0x39] & 3) == 0) && ((pbVar2[0x1b] & 3) == 0)) &&
       ((-1 < (int)((uint)*pbVar2 << 0x1e) &&
        ((-1 < (int)((uint)pbVar2[0x51] << 0x1d) && ((pbVar2[0x10] & 3) == 0)))))) {
      return;
    }
    if (*(int *)(DAT_08017a18 + 0x10) <= DAT_08017a1c) goto LAB_080179da;
    *(short *)(iVar1 + 0x10) = *(short *)(iVar1 + 0x10) + 1;
    if (*(ushort *)(iVar1 + 0x10) < 4) {
      return;
    }
    *(undefined2 *)(iVar1 + 0xe) = 0;
    *(undefined1 *)(iVar1 + 4) = 0;
    *(undefined2 *)(iVar1 + 0x10) = 0;
  }
  else {
    *(undefined2 *)(iVar1 + 0xe) = 0;
    *(undefined2 *)(iVar1 + 0x10) = 0;
    *(undefined1 *)(iVar1 + 4) = 0;
    if (((((pbVar2[0x39] & 3) == 0) && ((pbVar2[0x1b] & 3) == 0)) &&
        (-1 < (int)((uint)*pbVar2 << 0x1e))) &&
       ((-1 < (int)((uint)pbVar2[0x51] << 0x1d) && ((pbVar2[0x10] & 3) == 0)))) {
      return;
    }
  }
  FUN_0800c8f4();
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017a20 at 0x08017a20
// ---------------------------------------------------------------------------

void FUN_08017a20(void)

{
  uint uVar1;
  
  uVar1 = DAT_e000e010;
  DAT_e000e010 = uVar1 | 1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017a30 at 0x08017a30
// ---------------------------------------------------------------------------

void FUN_08017a30(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = DAT_08017a8c;
  iVar1 = DAT_08017a88;
  if ((int)((uint)*(byte *)(DAT_08017a88 + 0x12) << 0x1b) < 0) {
    FUN_08019844(0x16,0xb);
    *(undefined1 *)(iVar1 + 0x14) = 0;
    *(undefined2 *)(iVar2 + 0x14) = 0;
    *(undefined1 *)(iVar1 + 0x16) = 0;
  }
  if ((*(byte *)(iVar1 + 0x12) & 1) != 0) {
    FUN_08019844(5,0xb);
    *(undefined1 *)(iVar1 + 0x14) = 0;
    *(undefined2 *)(iVar2 + 0x14) = 0;
    *(undefined1 *)(iVar1 + 0x16) = 0;
  }
  *(byte *)(iVar1 + 0x12) = *(byte *)(iVar1 + 0x12) & 0xee;
  if ((int)((uint)*(byte *)(iVar1 + 0x12) << 0x1e) < 0) {
    *(byte *)(iVar1 + 0x12) = *(byte *)(iVar1 + 0x12) & 0xfd;
    FUN_08019844(6,0xb);
    *(undefined1 *)(iVar1 + 0x18) = 0;
    *(undefined2 *)(iVar2 + 0x26) = 0;
    *(undefined1 *)(iVar1 + 0x1a) = 0;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017a90 at 0x08017a90
// ---------------------------------------------------------------------------

void FUN_08017a90(void)

{
  *DAT_08017a98 = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017a9c at 0x08017a9c
// ---------------------------------------------------------------------------

void FUN_08017a9c(undefined4 param_1)

{
  *(undefined4 *)(DAT_08017aa4 + 0x20) = param_1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017af0 at 0x08017af0
// ---------------------------------------------------------------------------

undefined4 FUN_08017af0(void)

{
  if (*(char *)(DAT_08017b00 + 2) == '\0') {
    return 1;
  }
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017b04 at 0x08017b04
// ---------------------------------------------------------------------------

short FUN_08017b04(undefined4 param_1,undefined1 param_2)

{
  short sVar1;
  short sVar2;
  
  sVar1 = FUN_0800c0d0(param_1,param_2);
  sVar2 = FUN_08016658(param_1,param_2);
  return sVar1 + sVar2;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017b3c at 0x08017b3c
// ---------------------------------------------------------------------------

void FUN_08017b3c(void)

{
  byte *pbVar1;
  undefined4 uVar2;
  short sVar3;
  short sVar4;
  uint uVar5;
  undefined4 in_r3;
  undefined2 uVar7;
  uint uVar6;
  
  uVar2 = DAT_08017ba8;
  pbVar1 = DAT_08017ba4;
  FUN_08012330(0x60,DAT_08017ba8,(uint)*DAT_08017ba4 << 1,in_r3,in_r3);
  uVar7 = (undefined2)((uint)in_r3 >> 0x10);
  FUN_08018708(DAT_08017bac);
  sVar3 = FUN_08017b04(uVar2,(*pbVar1 & 0x7f) << 1);
  sVar4 = FUN_08017b04(DAT_08017bac,0xc);
  uVar6 = CONCAT22(uVar7,sVar4 + sVar3);
  FUN_08022e7c(0x100,sVar4 + sVar3);
  uVar5 = FUN_08018768(0x100);
  if (uVar5 == (uVar6 & 0xffff)) {
    *DAT_08017bb0 = 1;
    FUN_0801aa48(0xff,0xff,uVar6 & 0xffff,uVar6);
    return;
  }
  *DAT_08017bb0 = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017bc8 at 0x08017bc8
// ---------------------------------------------------------------------------

void FUN_08017bc8(uint param_1,int param_2)

{
  if (param_2 == 0) {
    param_1 = param_1 & 0xfffffeff;
  }
  *(uint *)(DAT_08017be0 + 0x2c) = *(uint *)(DAT_08017be0 + 0x2c) & 0xfffffe0f | param_1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017be4 at 0x08017be4
// ---------------------------------------------------------------------------

void FUN_08017be4(int param_1)

{
  int iVar1;
  undefined1 uVar2;
  
  iVar1 = DAT_08017c00;
  *(undefined1 *)(DAT_08017c00 + 0x20) = 0;
  *(undefined1 *)(iVar1 + 0x20) = 0;
  uVar2 = 1;
  if (param_1 != 1) {
    if (param_1 != 4) {
      return;
    }
    uVar2 = 5;
  }
  *(undefined1 *)(iVar1 + 0x20) = uVar2;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017c04 at 0x08017c04
// ---------------------------------------------------------------------------

void FUN_08017c04(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_08017c18;
  *(uint *)(DAT_08017c18 + 0x20) = *(uint *)(DAT_08017c18 + 0x20) & 0xfffffcff;
  *(uint *)(iVar1 + 0x20) = *(uint *)(iVar1 + 0x20) | param_1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017c1c at 0x08017c1c
// ---------------------------------------------------------------------------

void FUN_08017c1c(void)

{
  uint *puVar1;
  
  puVar1 = DAT_08017c58;
  *DAT_08017c58 = *DAT_08017c58 | 1;
  puVar1[1] = puVar1[1] & DAT_08017c5c;
  *puVar1 = *puVar1 & DAT_08017c60;
  *puVar1 = *puVar1 & 0xfffbffff;
  puVar1[1] = puVar1[1] & DAT_08017c64;
  puVar1[0xb] = 0x3800;
  puVar1[0xc] = 0x3800;
  puVar1[2] = 0x9f0000;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017c68 at 0x08017c68
// ---------------------------------------------------------------------------

void FUN_08017c68(uint param_1,int param_2)

{
  if (param_2 == 0) {
    param_1 = *(uint *)(DAT_08017c7c + 0x14) & ~param_1;
  }
  else {
    param_1 = *(uint *)(DAT_08017c7c + 0x14) | param_1;
  }
  *(uint *)(DAT_08017c7c + 0x14) = param_1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017c80 at 0x08017c80
// ---------------------------------------------------------------------------

void FUN_08017c80(uint param_1,int param_2)

{
  if (param_2 == 0) {
    param_1 = *(uint *)(DAT_08017c94 + 0x1c) & ~param_1;
  }
  else {
    param_1 = *(uint *)(DAT_08017c94 + 0x1c) | param_1;
  }
  *(uint *)(DAT_08017c94 + 0x1c) = param_1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017c98 at 0x08017c98
// ---------------------------------------------------------------------------

void FUN_08017c98(uint param_1,int param_2)

{
  if (param_2 == 0) {
    param_1 = *(uint *)(DAT_08017cac + 0x10) & ~param_1;
  }
  else {
    param_1 = *(uint *)(DAT_08017cac + 0x10) | param_1;
  }
  *(uint *)(DAT_08017cac + 0x10) = param_1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017cb0 at 0x08017cb0
// ---------------------------------------------------------------------------

void FUN_08017cb0(uint param_1,int param_2)

{
  if (param_2 == 0) {
    param_1 = *(uint *)(DAT_08017cc4 + 0x18) & ~param_1;
  }
  else {
    param_1 = *(uint *)(DAT_08017cc4 + 0x18) | param_1;
  }
  *(uint *)(DAT_08017cc4 + 0x18) = param_1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017cc8 at 0x08017cc8
// ---------------------------------------------------------------------------

void FUN_08017cc8(uint param_1,int param_2)

{
  if (param_2 == 0) {
    param_1 = *(uint *)(DAT_08017cdc + 0xc) & ~param_1;
  }
  else {
    param_1 = *(uint *)(DAT_08017cdc + 0xc) | param_1;
  }
  *(uint *)(DAT_08017cdc + 0xc) = param_1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017ce0 at 0x08017ce0
// ---------------------------------------------------------------------------

void FUN_08017ce0(undefined4 param_1)

{
  *DAT_08017ce8 = param_1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017cec at 0x08017cec
// ---------------------------------------------------------------------------

void FUN_08017cec(undefined4 param_1)

{
  *DAT_08017cf4 = param_1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017cf8 at 0x08017cf8
// ---------------------------------------------------------------------------

void FUN_08017cf8(undefined4 param_1)

{
  *DAT_08017d00 = param_1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017d04 at 0x08017d04
// ---------------------------------------------------------------------------

void FUN_08017d04(uint *param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  iVar1 = DAT_08017dac;
  uVar2 = *(uint *)(DAT_08017dac + 4) & DAT_08017db0;
  if ((int)(uVar2 << 4) < 0) {
    iVar4 = -0x1ef;
  }
  else {
    iVar4 = 2;
  }
  if (((*(uint *)(DAT_08017dac + 4) & 0x10000) == 0) || (*(int *)(DAT_08017dac + 4) << 0xe < 0)) {
    uVar3 = DAT_08017db4;
  }
  else {
    uVar3 = DAT_08017db8;
  }
  uVar3 = uVar3 * (iVar4 + (uVar2 >> 0x12));
  uVar2 = *(uint *)(DAT_08017dac + 4) & 0xc;
  if (((uVar2 == 0) || (uVar2 == 4)) || (uVar2 != 8)) {
    *param_1 = DAT_08017db8;
  }
  else {
    *param_1 = uVar3;
  }
  iVar4 = DAT_08017dbc;
  uVar2 = *param_1 >> *(sbyte *)(DAT_08017dbc + (*(uint *)(iVar1 + 4) >> 4 & 0xf));
  param_1[1] = uVar2;
  param_1[2] = uVar2 >> *(sbyte *)(iVar4 + (*(uint *)(iVar1 + 4) >> 8 & 7));
  param_1[3] = uVar2 >> *(sbyte *)(iVar4 + (*(uint *)(iVar1 + 4) >> 0xb & 7));
  iVar4 = DAT_08017dbc;
  param_1[5] = uVar2 / *(byte *)(DAT_08017dbc + 0x10 + (*(uint *)(iVar1 + 0x2c) & 0xf));
  param_1[4] = uVar3 / *(ushort *)(iVar4 + 0x20 + (*(uint *)(iVar1 + 0x2c) >> 4 & 0xf) * 2);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017dc0 at 0x08017dc0
// ---------------------------------------------------------------------------

bool FUN_08017dc0(uint param_1)

{
  uint uVar1;
  
  if (param_1 >> 5 == 1) {
    uVar1 = *DAT_08017dec;
  }
  else if (param_1 >> 5 == 2) {
    uVar1 = DAT_08017dec[8];
  }
  else {
    uVar1 = DAT_08017dec[9];
  }
  return (1 << (param_1 & 0x1f) & uVar1) != 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017df0 at 0x08017df0
// ---------------------------------------------------------------------------

void FUN_08017df0(int param_1)

{
  *DAT_08017e00 = *DAT_08017e00 & 0xffffff07 | param_1 << 3;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017e04 at 0x08017e04
// ---------------------------------------------------------------------------

void FUN_08017e04(void)

{
  *DAT_08017e0c = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017e10 at 0x08017e10
// ---------------------------------------------------------------------------

void FUN_08017e10(void)

{
  *DAT_08017e18 = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017e1c at 0x08017e1c
// ---------------------------------------------------------------------------

void FUN_08017e1c(void)

{
  *DAT_08017e24 = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017e28 at 0x08017e28
// ---------------------------------------------------------------------------

void FUN_08017e28(void)

{
  *DAT_08017e30 = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017e34 at 0x08017e34
// ---------------------------------------------------------------------------

void FUN_08017e34(void)

{
  *DAT_08017e3c = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017e40 at 0x08017e40
// ---------------------------------------------------------------------------

void FUN_08017e40(void)

{
  *DAT_08017e48 = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017e4c at 0x08017e4c
// ---------------------------------------------------------------------------

void FUN_08017e4c(void)

{
  *(undefined4 *)(DAT_08017e54 + 0x14) = 0x20;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017e58 at 0x08017e58
// ---------------------------------------------------------------------------

void FUN_08017e58(void)

{
  *(undefined4 *)(DAT_08017e60 + 0x10) = 0x20;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017e64 at 0x08017e64
// ---------------------------------------------------------------------------

void FUN_08017e64(void)

{
  *DAT_08017e6c = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017e70 at 0x08017e70
// ---------------------------------------------------------------------------

void FUN_08017e70(void)

{
  *DAT_08017e78 = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: EXTI15_10_IRQHandler at 0x08017e7c
// ---------------------------------------------------------------------------

void EXTI15_10_IRQHandler(void)

{
  FUN_08017ebc(0x1000);
  FUN_0800f3d0(0x20000);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017e92 at 0x08017e92
// ---------------------------------------------------------------------------

uint FUN_08017e92(uint param_1)

{
  return (param_1 & 0xf) + (param_1 >> 4) * 10 & 0xff;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017ea4 at 0x08017ea4
// ---------------------------------------------------------------------------

uint FUN_08017ea4(uint param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  for (; 9 < param_1; param_1 = param_1 - 10 & 0xff) {
    uVar1 = uVar1 + 1 & 0xff;
  }
  return param_1 | (uVar1 & 0xf) << 4;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017ebc at 0x08017ebc
// ---------------------------------------------------------------------------

void FUN_08017ebc(uint param_1)

{
  *DAT_08017ed4 = ~((param_1 & 0xfffff) >> 4 | 0x80) | *DAT_08017ed4 & 0x80;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017ed8 at 0x08017ed8
// ---------------------------------------------------------------------------

void FUN_08017ed8(uint param_1,int param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  
  puVar1 = DAT_08017efc;
  *DAT_08017efc = 0xca;
  *puVar1 = 0x53;
  uVar2 = DAT_08017efc[-7];
  if (param_2 == 0) {
    uVar2 = uVar2 & ~param_1;
  }
  else {
    uVar2 = uVar2 | param_1;
  }
  DAT_08017efc[-7] = uVar2;
  *puVar1 = 0xff;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017f00 at 0x08017f00
// ---------------------------------------------------------------------------

undefined4 FUN_08017f00(int param_1,byte *param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  undefined4 uVar6;
  
  piVar1 = DAT_08017f98;
  uVar6 = 0;
  if (param_1 == 0) {
    if (-1 < *DAT_08017f98 * 0x2000000) {
      param_2[3] = 0;
    }
    iVar3 = FUN_08017ea4(*param_2);
    iVar2 = FUN_08017ea4(param_2[1]);
    uVar5 = FUN_08017ea4(param_2[2]);
    uVar5 = iVar3 << 0x10 | iVar2 << 8 | uVar5 | (uint)param_2[3] << 0x10;
  }
  else {
    if (*DAT_08017f98 * 0x2000000 < 0) {
      FUN_08017e92();
    }
    else {
      param_2[3] = 0;
    }
    uVar5 = (uint)param_2[2] | (uint)*param_2 << 0x10 |
            (uint)param_2[1] << 8 | (uint)param_2[3] << 0x10;
  }
  piVar4 = DAT_08017f98 + 7;
  *piVar4 = 0xca;
  *piVar4 = 0x53;
  iVar3 = FUN_08018020();
  if (iVar3 != 0) {
    DAT_08017f98[-2] = uVar5 & DAT_08017f9c;
    FUN_0801805c();
    if ((*piVar1 << 0x1a < 0) || (iVar3 = FUN_08018250(), iVar3 != 0)) {
      uVar6 = 1;
    }
  }
  *piVar4 = 0xff;
  return uVar6;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017fa0 at 0x08017fa0
// ---------------------------------------------------------------------------

void FUN_08017fa0(uint param_1)

{
  undefined4 *puVar1;
  uint *puVar2;
  
  puVar1 = DAT_08017fc4;
  *DAT_08017fc4 = 0xca;
  *puVar1 = 0x53;
  puVar2 = DAT_08017fc4 + -7;
  *puVar2 = *puVar2 & 0xfffffff8;
  *puVar2 = *puVar2 | param_1;
  *puVar1 = 0xff;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08017fc8 at 0x08017fc8
// ---------------------------------------------------------------------------

undefined4 FUN_08017fc8(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  uint *puVar3;
  int local_c;
  
  puVar1 = DAT_0801801c;
  local_c = 0;
  *DAT_0801801c = 0xca;
  *puVar1 = 0x53;
  puVar3 = DAT_0801801c + -7;
  if (param_1 == 0) {
    *puVar3 = *puVar3 & 0xfffffbff;
    puVar3 = DAT_0801801c + -6;
    do {
      local_c = local_c + 1;
      if (local_c == (int)puVar3 >> 0x11) break;
    } while ((*puVar3 & 4) == 0);
    if (-1 < (int)(*puVar3 << 0x1d)) {
      uVar2 = 0;
      goto LAB_08018016;
    }
  }
  else {
    *puVar3 = *puVar3 | 0x400;
  }
  uVar2 = 1;
LAB_08018016:
  *puVar1 = 0xff;
  return uVar2;
}



// ---------------------------------------------------------------------------
// Function: FUN_08018020 at 0x08018020
// ---------------------------------------------------------------------------

undefined4 FUN_08018020(void)

{
  uint *puVar1;
  int local_8;
  
  puVar1 = DAT_08018058;
  local_8 = 0;
  if (-1 < (int)(*DAT_08018058 << 0x19)) {
    *DAT_08018058 = 0x80;
    do {
      local_8 = local_8 + 1;
      if (local_8 == (int)puVar1 >> 0x11) break;
    } while ((*puVar1 & 0x40) == 0);
    if (-1 < (int)(*puVar1 << 0x19)) {
      return 0;
    }
  }
  return 1;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801805c at 0x0801805c
// ---------------------------------------------------------------------------

void FUN_0801805c(void)

{
  *DAT_08018068 = *DAT_08018068 & 0xffffff7f;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801806c at 0x0801806c
// ---------------------------------------------------------------------------

void FUN_0801806c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 *puVar1;
  undefined4 uStack_10;
  undefined4 local_c;
  
  uStack_10 = param_3;
  local_c = param_4;
  FUN_08018298(1,&uStack_10);
  FUN_080182e0(1,&local_c);
  puVar1 = DAT_080180a8;
  DAT_080180a8[5] = local_c._2_1_;
  puVar1[4] = local_c._1_1_;
  puVar1[3] = (undefined1)local_c;
  puVar1[2] = uStack_10._2_1_;
  puVar1[1] = uStack_10._1_1_;
  *puVar1 = uStack_10._3_1_;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080180ac at 0x080180ac
// ---------------------------------------------------------------------------

bool FUN_080180ac(uint *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  uint *puVar3;
  
  puVar1 = DAT_080180f8;
  *DAT_080180f8 = 0xca;
  *puVar1 = 0x53;
  iVar2 = FUN_08018020();
  if (iVar2 != 0) {
    puVar3 = DAT_080180f8 + -7;
    *puVar3 = *puVar3 & 0xffffffbf;
    *puVar3 = *puVar3 | *param_1;
    puVar3 = DAT_080180f8 + -5;
    *puVar3 = param_1[2];
    *puVar3 = *puVar3 | (uint)(ushort)param_1[1] << 0x10;
    FUN_0801805c();
  }
  *puVar1 = 0xff;
  return iVar2 != 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_080180fc at 0x080180fc
// ---------------------------------------------------------------------------

undefined4 FUN_080180fc(int param_1,byte *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  
  uVar5 = 0;
  if (param_1 == 0) {
    if ((int)((uint)param_2[1] << 0x1b) < 0) {
      param_2[1] = (param_2[1] & 0xef) + 10;
    }
    iVar2 = FUN_08017ea4(param_2[3]);
    iVar3 = FUN_08017ea4(param_2[1]);
    uVar4 = FUN_08017ea4(param_2[2]);
    uVar4 = iVar2 << 0x10 | iVar3 << 8 | uVar4 | (uint)*param_2 << 0xd;
  }
  else {
    FUN_08017e92();
    FUN_08017e92(param_2[2]);
    uVar4 = (uint)param_2[2] | (uint)param_2[3] << 0x10 |
            (uint)param_2[1] << 8 | (uint)*param_2 << 0xd;
  }
  puVar1 = DAT_08018190;
  *DAT_08018190 = 0xca;
  *puVar1 = 0x53;
  iVar2 = FUN_08018020();
  if (iVar2 != 0) {
    DAT_08018190[-8] = uVar4 & DAT_08018194;
    FUN_0801805c();
    if (((int)(DAT_08018190[-7] << 0x1a) < 0) || (iVar2 = FUN_08018250(), iVar2 != 0)) {
      uVar5 = 1;
    }
  }
  *puVar1 = 0xff;
  return uVar5;
}



// ---------------------------------------------------------------------------
// Function: FUN_08018198 at 0x08018198
// ---------------------------------------------------------------------------

void FUN_08018198(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined1 param_5,undefined1 param_6)

{
  undefined1 local_20;
  undefined1 local_1f;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_14 = param_1;
  local_10 = param_2;
  local_c = param_3;
  local_8 = param_4;
  FUN_08017c80(0x18000000,1);
  FUN_08017cb0(1);
  FUN_08017a9c(1);
  local_1f = (undefined1)local_10;
  local_1e = (undefined1)local_c;
  local_1d = (undefined1)local_14;
  local_20 = 1;
  local_1c = (undefined1)local_8;
  local_1b = param_5;
  local_1a = param_6;
  FUN_080180fc(1,&local_20);
  FUN_08017f00(1,&local_1c);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08018200 at 0x08018200
// ---------------------------------------------------------------------------

void FUN_08018200(undefined4 param_1)

{
  undefined4 *puVar1;
  
  puVar1 = DAT_08018218;
  *DAT_08018218 = 0xca;
  *puVar1 = 0x53;
  DAT_08018218[-4] = param_1;
  *puVar1 = 0xff;
  return;
}



// ---------------------------------------------------------------------------
// Function: RTC_IRQHandler at 0x0801821c
// ---------------------------------------------------------------------------

void RTC_IRQHandler(void)

{
  if (*DAT_08018244 == '\0') {
    FUN_08017ed8(0x4000,0);
  }
  *DAT_08018248 = *DAT_08018248 & 0xfffffbff;
  *DAT_0801824c = 0x100000;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08018250 at 0x08018250
// ---------------------------------------------------------------------------

bool FUN_08018250(void)

{
  undefined4 *puVar1;
  uint *puVar2;
  uint uVar3;
  int local_c;
  
  puVar1 = DAT_08018294;
  local_c = 0;
  *DAT_08018294 = 0xca;
  *puVar1 = 0x53;
  puVar2 = DAT_08018294 + -6;
  *puVar2 = *puVar2 & 0xffffffdf;
  do {
    local_c = local_c + 1;
    if (local_c == (int)puVar2 >> 0xf) break;
  } while ((*puVar2 & 0x20) == 0);
  uVar3 = *puVar2;
  *puVar1 = 0xff;
  return (int)(uVar3 << 0x1a) < 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_08018298 at 0x08018298
// ---------------------------------------------------------------------------

void FUN_08018298(int param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  uint uVar2;
  
  uVar2 = *DAT_080182d8 & DAT_080182dc;
  param_2[3] = (char)(uVar2 >> 0x10);
  param_2[1] = (byte)(uVar2 >> 8) & 0x1f;
  param_2[2] = (byte)uVar2 & 0x3f;
  *param_2 = (char)((uVar2 & 0xffff) >> 0xd);
  if (param_1 == 0) {
    uVar1 = FUN_08017e92(uVar2 >> 0x10);
    param_2[3] = uVar1;
    uVar1 = FUN_08017e92(param_2[1]);
    param_2[1] = uVar1;
    uVar1 = FUN_08017e92(param_2[2]);
    param_2[2] = uVar1;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080182e0 at 0x080182e0
// ---------------------------------------------------------------------------

void FUN_080182e0(int param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  uint uVar2;
  
  uVar2 = *DAT_08018324 & DAT_08018328;
  *param_2 = (char)((uVar2 & 0x3fffff) >> 0x10);
  param_2[1] = (byte)(uVar2 >> 8) & 0x7f;
  param_2[2] = (byte)uVar2 & 0x7f;
  param_2[3] = (byte)(uVar2 >> 0x10) & 0x40;
  if (param_1 == 0) {
    uVar1 = FUN_08017e92((uVar2 & 0x3fffff) >> 0x10);
    *param_2 = uVar1;
    uVar1 = FUN_08017e92(param_2[1]);
    param_2[1] = uVar1;
    uVar1 = FUN_08017e92(param_2[2]);
    param_2[2] = uVar1;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801832c at 0x0801832c
// ---------------------------------------------------------------------------

undefined4 FUN_0801832c(void)

{
  undefined1 *puVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = DAT_08018350;
  puVar1 = (undefined1 *)(*(int *)(DAT_08018350 + 0x1c) + 3);
  uVar3 = FUN_0800c0d0(puVar1,*puVar1);
  if (uVar3 == *(byte *)((uint)*(byte *)(*(int *)(iVar2 + 0x1c) + 3) + *(int *)(iVar2 + 0x1c) + 2))
  {
    return 1;
  }
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_08018354 at 0x08018354
// ---------------------------------------------------------------------------

ulonglong FUN_08018354(uint param_1)

{
  undefined4 local_10 [2];
  uint local_8;
  
  local_8 = param_1;
  FUN_08012330(param_1 & 0xffff,local_10,1);
  return CONCAT44(local_10[0],local_10[0]) & 0xffffffff000000ff;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801836c at 0x0801836c
// ---------------------------------------------------------------------------

undefined4 FUN_0801836c(uint param_1,byte *param_2,uint param_3)

{
  uint *puVar1;
  byte bVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined1 local_a0;
  undefined1 local_9f;
  undefined1 local_9e;
  byte local_9d [117];
  byte local_28;
  uint local_20;
  byte *pbStack_1c;
  uint local_18;
  
  local_a0 = 0x40;
  local_20._0_1_ = (undefined1)param_1;
  local_9f = (undefined1)local_20;
  local_9e = 0x41;
  local_20 = param_1;
  pbStack_1c = param_2;
  local_18 = param_3;
  FUN_08012578();
  FUN_080126b0(0x40);
  FUN_080124a4();
  FUN_080126b0(local_20 & 0xff);
  FUN_080124a4();
  FUN_08012578();
  FUN_080126b0(0x41);
  FUN_080124a4();
  puVar1 = DAT_080184e0;
  local_28 = 0;
  while( true ) {
    if ((local_18 & 0xff) << 1 <= (uint)local_28) break;
    bVar2 = FUN_0801227c();
    local_9d[local_28] = bVar2;
    if ((local_18 & 0xff) * 2 - 1 != (uint)local_28) {
      *puVar1 = (*puVar1 & 0xffff0fff) + 0x3000;
      FUN_080121bc();
      *puVar1 = (*puVar1 & 0xfffff0ff) + 0x400;
      FUN_080121bc();
      FUN_080121bc();
      *puVar1 = ((*puVar1 & 0xfffff0ff) + 0x300 & 0xffff0fff) + 0x4000;
      FUN_080121bc();
      FUN_080121bc();
    }
    local_28 = local_28 + 1;
  }
  *puVar1 = ((*puVar1 & 0xffff0fff) + 0x4000 & 0xfffff0ff) + 0x400;
  FUN_080121bc();
  FUN_080121bc();
  *puVar1 = ((*puVar1 & 0xfffff0ff) + 0x300 & 0xffff0fff) + 0x3000;
  FUN_080121bc();
  FUN_080121bc();
  FUN_0801260c();
  uVar3 = FUN_08022fa2(&local_a0,4);
  if (uVar3 == local_9d[1]) {
    *param_2 = local_9d[0];
    for (local_28 = 0; (int)(uint)local_28 < (int)((local_18 & 0xff) - 1); local_28 = local_28 + 1)
    {
      uVar3 = FUN_08022fa2(local_9d + (uint)local_28 * 2 + 2,1);
      if (uVar3 != local_9d[(uint)local_28 * 2 + 3]) goto LAB_080184aa;
      param_2[local_28 + 1] = local_9d[(uint)local_28 * 2 + 2];
    }
    uVar4 = 1;
  }
  else {
LAB_080184aa:
    uVar4 = 0;
  }
  return uVar4;
}



// ---------------------------------------------------------------------------
// Function: FUN_08018574 at 0x08018574
// ---------------------------------------------------------------------------

bool FUN_08018574(float *param_1)

{
  float fVar1;
  char *pcVar2;
  float *pfVar3;
  bool bVar4;
  int iVar5;
  float fVar6;
  float local_38;
  uint local_34;
  float local_2c;
  undefined1 local_28;
  
  pfVar3 = DAT_080186f0;
  pcVar2 = DAT_080186e8;
  fVar1 = DAT_080186e4;
  local_38 = DAT_080186e4;
  local_2c = DAT_080186e4;
  local_34 = local_34 & 0xffff0000;
  local_28 = 0;
  if (*DAT_080186e8 == '\0') {
    if (*(char *)(DAT_080186ec + 0x3d) == '\x01') {
      DAT_080186e8[0xb] = '\x01';
LAB_0801862e:
      pcVar2[0x14] = '\0';
      pcVar2[0x15] = '\0';
LAB_08018630:
      iVar5 = FUN_08009c48(&local_38,1);
      if (iVar5 == 0) {
LAB_0801863c:
        *pcVar2 = '\x01';
        goto LAB_0801859c;
      }
      fVar6 = pfVar3[1];
    }
    else {
      if (DAT_080186e8[0xb] == '\x01') {
        *(short *)(DAT_080186e8 + 0x14) = *(short *)(DAT_080186e8 + 0x14) + 1;
        if (10 < *(ushort *)(pcVar2 + 0x14)) {
          pcVar2[0xb] = '\0';
          goto LAB_0801862e;
        }
        goto LAB_08018630;
      }
      iVar5 = FUN_08009c48(&local_38,2);
      if (iVar5 == 0) goto LAB_0801863c;
      fVar6 = *pfVar3;
    }
    local_38 = (local_38 - fVar6) / (*DAT_080186f4 * DAT_080186f8);
    if (0.0 < local_38) {
      fVar6 = pfVar3[3];
    }
    else {
      fVar6 = pfVar3[2];
    }
    local_38 = local_38 / fVar6;
    iVar5 = FUN_0800d9cc(local_38,&local_2c);
    bVar4 = iVar5 != 0;
    if (bVar4) {
      local_38 = local_38 + local_2c;
    }
    if ((((uint)DAT_080186fc < (uint)local_2c) || (*DAT_08018704 < local_38)) ||
       (local_38 < -*DAT_08018700)) {
      *param_1 = local_38;
    }
    else {
      *param_1 = fVar1;
    }
  }
  else {
LAB_0801859c:
    bVar4 = false;
  }
  return bVar4;
}



// ---------------------------------------------------------------------------
// Function: FUN_08018708 at 0x08018708
// ---------------------------------------------------------------------------

void FUN_08018708(undefined1 *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = *DAT_08018764;
  uVar2 = DAT_08018764[1];
  uVar3 = DAT_08018764[2];
  *param_1 = (char)uVar1;
  param_1[1] = (char)((uint)uVar1 >> 8);
  param_1[2] = (char)((uint)uVar1 >> 0x10);
  param_1[3] = (char)((uint)uVar1 >> 0x18);
  param_1[4] = (char)uVar2;
  param_1[5] = (char)((uint)uVar2 >> 8);
  param_1[6] = (char)((uint)uVar2 >> 0x10);
  param_1[7] = (char)((uint)uVar2 >> 0x18);
  param_1[8] = (char)uVar3;
  param_1[9] = (char)((uint)uVar3 >> 8);
  param_1[10] = (char)((uint)uVar3 >> 0x10);
  param_1[0xb] = (char)((uint)uVar3 >> 0x18);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08018768 at 0x08018768
// ---------------------------------------------------------------------------

undefined8 FUN_08018768(uint param_1)

{
  undefined4 local_10;
  undefined1 local_c;
  undefined1 local_b;
  uint local_8;
  
  local_8 = param_1;
  FUN_08012330(param_1 & 0xffff,&local_c,2);
  local_10 = CONCAT22(local_10._2_2_,CONCAT11(local_c,local_b));
  return CONCAT44(local_10,(uint)CONCAT11(local_c,local_b));
}



// ---------------------------------------------------------------------------
// Function: FUN_08018798 at 0x08018798
// ---------------------------------------------------------------------------

void FUN_08018798(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  int iVar5;
  uint local_10;
  
  iVar2 = DAT_08018894;
  iVar1 = DAT_08018890;
  iVar3 = DAT_0801888c;
  iVar5 = *(int *)(DAT_0801888c + 4);
  if (iVar5 == 0x104) {
    local_10 = 0;
    while ((byte)local_10 < 8) {
      *(undefined1 *)(iVar2 + local_10) = *(undefined1 *)(local_10 + iVar3 + 0xb);
      local_10 = (uint)(byte)((byte)local_10 + 1);
    }
    bVar4 = *(byte *)(iVar1 + 2) | 1;
  }
  else if (iVar5 == 0x105) {
    local_10 = 0;
    while ((byte)local_10 < 8) {
      *(undefined1 *)(local_10 + iVar2 + 8) = *(undefined1 *)(local_10 + iVar3 + 0xb);
      local_10 = (uint)(byte)((byte)local_10 + 1);
    }
    bVar4 = *(byte *)(iVar1 + 2) | 2;
  }
  else {
    if (iVar5 != 0x106) goto LAB_0801884e;
    local_10 = 0;
    while ((byte)local_10 < 8) {
      *(undefined1 *)(local_10 + iVar2 + 0x10) = *(undefined1 *)(local_10 + iVar3 + 0xb);
      local_10 = (uint)(byte)((byte)local_10 + 1);
    }
    bVar4 = *(byte *)(iVar1 + 2) | 4;
  }
  *(byte *)(iVar1 + 2) = bVar4;
LAB_0801884e:
  if ((6 < *(byte *)(iVar1 + 2)) && (*(undefined1 *)(iVar1 + 2) = 0, *(char *)(iVar1 + 1) == '\0'))
  {
    *(undefined1 *)(iVar1 + 1) = 1;
    iVar3 = DAT_08018894 + 0x30;
    local_10 = 0;
    while ((byte)local_10 < 0x18) {
      *(undefined1 *)(iVar3 + local_10) = *(undefined1 *)(iVar2 + local_10);
      local_10 = (uint)(byte)((byte)local_10 + 1);
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08018898 at 0x08018898
// ---------------------------------------------------------------------------

void FUN_08018898(void)

{
  int iVar1;
  
  iVar1 = DAT_080188c8;
  if ((*(byte *)(DAT_080188c8 + 0x39) & 1) != 0) {
    FUN_08019844(0xe,10);
  }
  *(byte *)(iVar1 + 0x39) = *(byte *)(iVar1 + 0x39) & 0xfe;
  *(undefined2 *)(DAT_080188cc + 0x16) = 0;
  FUN_0800c940();
  *(undefined1 *)(DAT_08017894 + 5) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080188d0 at 0x080188d0
// ---------------------------------------------------------------------------

void FUN_080188d0(void)

{
  float fVar1;
  int iVar2;
  undefined1 *puVar3;
  int iVar4;
  int iVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  float local_28;
  byte local_24 [8];
  
  iVar2 = DAT_080189b8;
  fVar1 = DAT_080189b0;
  local_28 = DAT_080189b0;
  if (((*(byte *)(DAT_080189b4 + 0x39) & 1) != 0) &&
     (iVar4 = FUN_08016638(), puVar3 = DAT_080189c4, iVar5 = DAT_080189c0, iVar4 == 1)) {
    if (*DAT_080189bc == '\0') {
      *(undefined2 *)(DAT_080189c0 + 0x260) = 0;
      *puVar3 = 0;
      uVar7 = 0xfffffffe < *(ushort *)(iVar2 + 0x3a);
      iVar5 = *(ushort *)(iVar2 + 0x3a) + 1;
      uVar6 = iVar5 == 0;
      *(short *)(iVar2 + 0x3a) = (short)iVar5;
      uVar8 = FUN_08008548(*DAT_080189c8);
      uVar8 = FUN_08008364((int)uVar8,(int)((ulonglong)uVar8 >> 0x20),(int)DAT_080189cc,
                           (int)((ulonglong)DAT_080189cc >> 0x20));
      uVar9 = FUN_08008548(*(undefined2 *)(iVar2 + 0x3a));
      FUN_08008628((int)uVar9,(int)((ulonglong)uVar9 >> 0x20),(int)uVar8,
                   (int)((ulonglong)uVar8 >> 0x20));
      if ((bool)uVar7 && !(bool)uVar6) {
        return;
      }
LAB_0801899c:
      *(undefined2 *)(iVar2 + 0x3a) = 0;
      FUN_08018898();
      return;
    }
    iVar4 = FUN_080122f0(0x51,local_24,1);
    if (iVar4 == 0) {
      return;
    }
    if ((int)((uint)local_24[0] << 0x18) < 0) {
      local_28 = fVar1;
      iVar4 = FUN_0800d3c4(&local_28);
      if (iVar4 == 0) {
        return;
      }
      if (*(float *)(DAT_080189d4 + 0x114) * 0.5 < local_28) {
        *(undefined2 *)(iVar5 + 0x260) = 0;
        *puVar3 = 0;
        *(short *)(iVar2 + 0x3a) = *(short *)(iVar2 + 0x3a) + 1;
        if (*(ushort *)(iVar2 + 0x3a) < 0x1e) {
          return;
        }
        goto LAB_0801899c;
      }
    }
    else {
      FUN_08012720(0x51,local_24[0] | 0x80,1);
    }
  }
  *(undefined2 *)(iVar2 + 0x3a) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080189d8 at 0x080189d8
// ---------------------------------------------------------------------------

void FUN_080189d8(void)

{
  byte bVar1;
  int iVar2;
  int *piVar3;
  float *pfVar4;
  uint uVar5;
  byte extraout_r1;
  int extraout_r2;
  ushort uVar6;
  uint in_fpscr;
  float fVar7;
  float fVar8;
  float fVar9;
  byte local_28;
  
  piVar3 = DAT_08018bcc;
  iVar2 = DAT_08018bc4;
  if (*(char *)(DAT_08018bc0 + 0x3d) == '\0') {
    uVar6 = *(ushort *)(DAT_08018bc4 + 10);
  }
  else {
    uVar6 = *(ushort *)(DAT_08018bc4 + 0xc);
  }
  if ((*DAT_08018bc8 == '\x01') &&
     ((int)((float)DAT_08018bcc[3] - *(float *)(DAT_08018bd0 + 0xc)) < 0x3f000001)) {
    if ((*(char *)(DAT_08018bc0 + 0x3b) == '\0') && (*(char *)(DAT_08018bc0 + 0x3a) == '\0')) {
      *(short *)(DAT_08018bc4 + 0x28) = *(short *)(DAT_08018bc4 + 0x28) + 1;
      if (uVar6 <= *(ushort *)(iVar2 + 0x28)) {
        *(undefined2 *)(iVar2 + 0x28) = 0;
        uVar5 = FUN_080112a4();
        fVar8 = DAT_08018bdc;
        pfVar4 = DAT_08018bd8;
        local_28 = extraout_r1;
        while ((local_28 < 100 && (*(uint *)(*DAT_08018bd4 + (99 - (uint)local_28) * 4) <= uVar5)))
        {
          local_28 = local_28 + 1;
        }
        if (local_28 + 1 < (uint)(*(byte *)((int)DAT_08018bd8 + 0x12) >> 1)) {
          *(char *)((int)DAT_08018bd8 + 0x12) = *(char *)((int)DAT_08018bd8 + 0x12) + -2;
          fVar7 = (float)VectorSignedToFloat((100 - (uint)*DAT_08018be0) - (uint)*DAT_08018be4,
                                             (byte)(in_fpscr >> 0x16) & 3);
          uVar5 = VectorFloatToUnsigned((*pfVar4 / fVar8) * fVar7 * DAT_08018be8,3);
          pfVar4[2] = (float)((int)pfVar4[2] - (uVar5 & 0xffff));
          FUN_0800b460();
          pfVar4[3] = (float)((int)pfVar4[3] + (uVar5 & 0xffff));
          if (0x40800000 < *piVar3) {
            fVar7 = (float)VectorSignedToFloat(pfVar4[2],(byte)(in_fpscr >> 0x16) & 3);
            fVar9 = (float)VectorUnsignedToFloat(local_28 + 1,(byte)(in_fpscr >> 0x16) & 3);
            fVar7 = fVar7 - (*pfVar4 / fVar8) * fVar9;
            uVar5 = in_fpscr & 0xfffffff | (uint)(fVar7 < 0.0) << 0x1f |
                    (uint)(fVar7 == 0.0) << 0x1e;
            bVar1 = (byte)(uVar5 >> 0x18);
            if (!(bool)(bVar1 >> 6 & 1) && (bool)(bVar1 >> 7) == NAN(fVar7)) {
              fVar7 = (float)VectorSignedToFloat(pfVar4[2],(byte)(uVar5 >> 0x16) & 3);
              fVar9 = (float)VectorUnsignedToFloat(local_28 + 1,(byte)(uVar5 >> 0x16) & 3);
              pfVar4[0x2a] = (*pfVar4 / fVar8) * fVar9 - fVar7;
            }
          }
        }
        else if (0x40800000 < *piVar3) {
          fVar7 = (float)VectorSignedToFloat(DAT_08018bd8[2],(byte)(in_fpscr >> 0x16) & 3);
          fVar8 = (float)VectorUnsignedToFloat((uint)local_28,(byte)(in_fpscr >> 0x16) & 3);
          if (fVar7 - (*DAT_08018bd8 / DAT_08018bdc) * fVar8 < 0.0) {
            fVar8 = (float)VectorSignedToFloat(DAT_08018bd8[2],
                                               (byte)((in_fpscr & 0xfffffff) >> 0x16) & 3);
            fVar7 = (float)VectorUnsignedToFloat
                                     ((uint)local_28,(byte)((in_fpscr & 0xfffffff) >> 0x16) & 3);
            DAT_08018bd8[0x2a] = (*DAT_08018bd8 / DAT_08018bdc) * fVar7 - fVar8;
          }
          *(undefined4 *)(extraout_r2 + 0x30) = DAT_08018bec;
          *(byte *)(extraout_r2 + 4) = extraout_r1;
        }
      }
    }
    else {
      *(undefined2 *)(DAT_08018bc4 + 0x28) = 0;
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08018bf0 at 0x08018bf0
// ---------------------------------------------------------------------------

void FUN_08018bf0(float *param_1,float *param_2)

{
  byte bVar1;
  float fVar2;
  float *pfVar3;
  float fVar4;
  int iVar5;
  char *pcVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  uint in_fpscr;
  uint uVar9;
  uint uVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uVar14;
  
  iVar5 = DAT_08019014;
  fVar4 = DAT_08019010;
  pfVar3 = DAT_0801900c;
  fVar2 = DAT_08019008;
  fVar11 = DAT_08018ff8;
  uVar7 = (undefined4)DAT_08019000;
  uVar8 = (undefined4)((ulonglong)DAT_08019000 >> 0x20);
  if ((int)*param_2 <= DAT_08018ffc) {
    if ((int)*param_1 <= DAT_08018ffc) {
      return;
    }
    fVar12 = (float)VectorSignedToFloat(DAT_0801900c[2],(byte)(in_fpscr >> 0x16) & 3);
    uVar9 = in_fpscr & 0xfffffff | (uint)(fVar12 < *DAT_0801900c) << 0x1f;
    uVar10 = uVar9 | (uint)(NAN(fVar12) || NAN(*DAT_0801900c)) << 0x1c;
    if ((byte)(uVar9 >> 0x1f) == ((byte)(uVar10 >> 0x1c) & 1)) {
      DAT_0801900c[0x2a] = DAT_08018ff8;
    }
    else {
      *(float *)(DAT_08019014 + 0x54) = DAT_0801900c[0x2a];
      fVar12 = (float)VectorSignedToFloat(pfVar3[2],(byte)(uVar10 >> 0x16) & 3);
      *(float *)(iVar5 + 0x50) = (*pfVar3 - fVar12) - *(float *)(iVar5 + 0x54);
      pcVar6 = DAT_08019020;
      if (0x3f800000 < *(int *)(iVar5 + 0x50)) {
        *(float *)(iVar5 + 0x5c) = (*param_1 * *(float *)(iVar5 + 0x54)) / *(float *)(iVar5 + 0x50);
        if (*pcVar6 == '\x01') {
          fVar12 = *param_1 * 4.0;
        }
        else {
          fVar12 = *param_1 * DAT_08019024;
        }
        fVar13 = *(float *)(iVar5 + 0x5c);
        uVar9 = in_fpscr & 0xfffffff | (uint)(fVar13 < fVar12) << 0x1f |
                (uint)(fVar13 == fVar12) << 0x1e;
        uVar10 = uVar9 | (uint)(NAN(fVar13) || NAN(fVar12)) << 0x1c;
        bVar1 = (byte)(uVar9 >> 0x18);
        if ((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(uVar10 >> 0x1c) & 1)) {
          if (*pcVar6 == '\x01') {
            uVar14 = FUN_080085d2(*param_1);
          }
          else {
            uVar14 = FUN_080085d2(*param_1);
            uVar8 = (undefined4)((ulonglong)DAT_08019028 >> 0x20);
            uVar7 = (undefined4)DAT_08019028;
          }
          FUN_08008364((int)uVar14,(int)((ulonglong)uVar14 >> 0x20),uVar7,uVar8);
          fVar12 = (float)FUN_08008658();
          uVar10 = uVar10 & 0xfffffff;
          if (fVar12 <= *(float *)(iVar5 + 0x5c)) goto LAB_08018f60;
        }
        *(float *)(iVar5 + 0x5c) = fVar12;
        goto LAB_08018f60;
      }
    }
    *(float *)(iVar5 + 0x5c) = fVar11;
LAB_08018f60:
    pfVar3[0xc] = *param_1 + *(float *)(iVar5 + 0x5c);
    pfVar3[0x2a] = pfVar3[0x2a] - *(float *)(iVar5 + 0x5c) * fVar2;
    if ((*(char *)((int)pfVar3 + 0x7f) == '\x01') || (*(char *)((int)pfVar3 + 0x7f) == '\x02')) {
      pfVar3[0x20] = pfVar3[0x20] + *param_1 * fVar4;
    }
    *(float *)(iVar5 + 0x40) = pfVar3[0xc] * fVar4;
    *(float *)(iVar5 + 0x48) = *(float *)(iVar5 + 0x48) + *(float *)(iVar5 + 0x40);
    *(float *)(iVar5 + 0x40) = fVar11;
    uVar9 = VectorFloatToUnsigned(*(undefined4 *)(iVar5 + 0x48),3);
    if ((short)uVar9 == 0) {
      return;
    }
    pfVar3[9] = (float)((int)pfVar3[9] + (uVar9 & 0xffff));
    fVar11 = (float)VectorUnsignedToFloat(uVar9 & 0xffff,(byte)(uVar10 >> 0x16) & 3);
    *(float *)(iVar5 + 0x48) = *(float *)(iVar5 + 0x48) - fVar11;
    return;
  }
  if (*DAT_08019018 < *(byte *)((int)DAT_0801900c + 0x12) >> 1) {
LAB_08018d5a:
    *(float *)(iVar5 + 0x58) = fVar11;
  }
  else {
    *(float *)(DAT_08019014 + 0x54) = *DAT_0801900c * DAT_0801900c[0x11];
    fVar12 = (float)VectorSignedToFloat(pfVar3[2],(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(iVar5 + 0x50) = (fVar12 + pfVar3[0x2a]) - *(float *)(iVar5 + 0x54);
    if ((int)pfVar3[2] < 2) goto LAB_08018d5a;
    fVar12 = *(float *)(iVar5 + 0x54);
    in_fpscr = in_fpscr & 0xfffffff;
    uVar10 = in_fpscr | (uint)(fVar12 < 0.0) << 0x1f | (uint)(fVar12 == 0.0) << 0x1e;
    uVar9 = uVar10 | (uint)NAN(fVar12) << 0x1c;
    bVar1 = (byte)(uVar10 >> 0x18);
    if (((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(uVar9 >> 0x1c) & 1)) ||
       (uVar9 = in_fpscr, *(float *)(iVar5 + 0x54) <= pfVar3[0x2a])) {
      in_fpscr = uVar9 & 0xfffffff;
      if (*(float *)(iVar5 + 0x54) < 0.0) {
        fVar12 = pfVar3[0x2a];
        fVar13 = *(float *)(iVar5 + 0x54);
        uVar10 = in_fpscr | (uint)(fVar12 < fVar13) << 0x1f | (uint)(fVar12 == fVar13) << 0x1e;
        in_fpscr = uVar10 | (uint)(NAN(fVar12) || NAN(fVar13)) << 0x1c;
        bVar1 = (byte)(uVar10 >> 0x18);
        if (!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1))
        goto LAB_08018cb4;
      }
      goto LAB_08018d5a;
    }
LAB_08018cb4:
    if (DAT_0801901c < *(int *)(iVar5 + 0x50)) {
      *(float *)(iVar5 + 0x58) =
           ((*(float *)(iVar5 + 0x54) - pfVar3[0x2a]) * *param_2) / *(float *)(iVar5 + 0x50);
      fVar12 = *param_2 * 4.0;
      fVar13 = *(float *)(iVar5 + 0x58);
      uVar10 = in_fpscr & 0xfffffff | (uint)(fVar13 < fVar12) << 0x1f |
               (uint)(fVar13 == fVar12) << 0x1e;
      in_fpscr = uVar10 | (uint)(NAN(fVar13) || NAN(fVar12)) << 0x1c;
      bVar1 = (byte)(uVar10 >> 0x18);
      if (!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1))
      goto LAB_08018d3c;
      uVar14 = FUN_080085d2(*param_2);
      FUN_08008364((int)uVar14,(int)((ulonglong)uVar14 >> 0x20),uVar7,uVar8);
      fVar12 = (float)FUN_08008658();
      in_fpscr = in_fpscr & 0xfffffff;
      if (*(float *)(iVar5 + 0x58) < fVar12) goto LAB_08018d3c;
    }
    else {
      in_fpscr = in_fpscr & 0xfffffff;
      if (0.0 <= *(float *)(iVar5 + 0x50)) goto LAB_08018d5a;
      fVar12 = *param_2 * 4.0;
LAB_08018d3c:
      *(float *)(iVar5 + 0x58) = fVar12;
    }
  }
  pfVar3[0xd] = *param_2 + *(float *)(iVar5 + 0x58);
  if ((int)pfVar3[2] < 1) {
    uVar10 = in_fpscr & 0xfffffff;
    uVar9 = uVar10 | (uint)(pfVar3[0x11] < 0.0) << 0x1f;
    in_fpscr = uVar9 | (uint)NAN(pfVar3[0x11]) << 0x1c;
    if ((byte)(uVar9 >> 0x1f) == ((byte)(in_fpscr >> 0x1c) & 1)) {
      fVar12 = pfVar3[0x2a];
      uVar10 = uVar10 | (uint)(fVar12 < 0.0) << 0x1f | (uint)(fVar12 == 0.0) << 0x1e;
      in_fpscr = uVar10 | (uint)NAN(fVar12) << 0x1c;
      bVar1 = (byte)(uVar10 >> 0x18);
      if ((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) goto LAB_08018da0;
    }
    else {
LAB_08018da0:
      in_fpscr = in_fpscr & 0xfffffff;
      if (0.0 <= pfVar3[0x11]) goto LAB_08018dd0;
      fVar12 = pfVar3[0x2a];
      fVar13 = *(float *)(iVar5 + 0x54);
      uVar10 = in_fpscr | (uint)(fVar12 < fVar13) << 0x1f | (uint)(fVar12 == fVar13) << 0x1e;
      in_fpscr = uVar10 | (uint)(NAN(fVar12) || NAN(fVar13)) << 0x1c;
      bVar1 = (byte)(uVar10 >> 0x18);
      if ((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) goto LAB_08018dd0;
    }
    fVar12 = pfVar3[0x2a] - pfVar3[0xd] * fVar2;
  }
  else {
    fVar12 = pfVar3[0x2a] + *(float *)(iVar5 + 0x58) * fVar2;
  }
  pfVar3[0x2a] = fVar12;
LAB_08018dd0:
  if ((*(char *)((int)pfVar3 + 0x7f) == '\x01') || (*(char *)((int)pfVar3 + 0x7f) == '\x02')) {
    pfVar3[0x21] = pfVar3[0x21] + *param_2 * fVar4;
  }
  *(float *)(iVar5 + 0x44) = pfVar3[0xd] * fVar2;
  *(float *)(iVar5 + 0x4c) = *(float *)(iVar5 + 0x4c) + *(float *)(iVar5 + 0x44);
  *(float *)(iVar5 + 0x44) = fVar11;
  uVar10 = VectorFloatToUnsigned(*(undefined4 *)(iVar5 + 0x4c),3);
  if ((short)uVar10 != 0) {
    pfVar3[9] = (float)((int)pfVar3[9] - (uVar10 & 0xffff));
    fVar11 = (float)VectorUnsignedToFloat(uVar10 & 0xffff,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(iVar5 + 0x4c) = *(float *)(iVar5 + 0x4c) - fVar11;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08019120 at 0x08019120
// ---------------------------------------------------------------------------

void FUN_08019120(void)

{
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08019124 at 0x08019124
// ---------------------------------------------------------------------------

void FUN_08019124(void)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  float *pfVar6;
  float *extraout_r3;
  uint in_fpscr;
  float fVar7;
  float fVar8;
  float fVar9;
  undefined4 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  uint local_38;
  
  iVar3 = DAT_080192d4;
  local_38 = 0;
  if ((*(char *)(DAT_080192d4 + 7) != '\x01') && (*(char *)(DAT_080192d4 + 7) != '\x02')) {
LAB_080192ca:
    *(undefined1 *)(iVar3 + 7) = 0;
    return;
  }
  if (0x3b < (int)(100 - (uint)*(byte *)(DAT_080192d4 + 1))) {
    fVar7 = *(float *)(DAT_080192d4 + 8);
    fVar8 = *(float *)(DAT_080192d4 + 0xc);
    uVar1 = in_fpscr & 0xfffffff | (uint)(fVar7 < fVar8) << 0x1f | (uint)(fVar7 == fVar8) << 0x1e;
    in_fpscr = uVar1 | (uint)(NAN(fVar7) || NAN(fVar8)) << 0x1c;
    bVar2 = (byte)(uVar1 >> 0x18);
    if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
      uVar11 = FUN_08008526(100 - (uint)*(byte *)(DAT_080192d4 + 1));
      uVar12 = FUN_08008548(*(undefined1 *)(iVar3 + 1));
      uVar5 = (undefined4)((ulonglong)DAT_080192d8 >> 0x20);
      uVar10 = (undefined4)DAT_080192d8;
      uVar12 = FUN_08008448((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),uVar10,uVar5);
      uVar12 = FUN_0800835e((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),(int)DAT_080192e0,
                            (int)((ulonglong)DAT_080192e0 >> 0x20));
      uVar13 = FUN_080085d2(*DAT_080192e8);
      uVar12 = FUN_08008364((int)uVar13,(int)((ulonglong)uVar13 >> 0x20),(int)uVar12,
                            (int)((ulonglong)uVar12 >> 0x20));
      uVar12 = FUN_0800835e((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),uVar10,uVar5);
      uVar13 = FUN_080085d2(*(float *)(iVar3 + 8) - *(float *)(iVar3 + 0xc));
      uVar12 = FUN_08008364((int)uVar13,(int)((ulonglong)uVar13 >> 0x20),(int)uVar12,
                            (int)((ulonglong)uVar12 >> 0x20));
      FUN_08008448((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),(int)uVar11,
                   (int)((ulonglong)uVar11 >> 0x20));
      local_38 = FUN_080085a0();
    }
  }
  uVar5 = DAT_080192ec;
  iVar4 = DAT_080192d4;
  *(undefined4 *)(iVar3 + 0xc) = DAT_080192ec;
  *(undefined4 *)(iVar3 + 8) = uVar5;
  *(undefined1 *)(iVar4 + 0x120) = 0;
  *(undefined4 *)(iVar4 + 0x124) = uVar5;
  if (local_38 == 0) goto LAB_080192ca;
  pfVar6 = (float *)(DAT_080192d4 + -0x78);
  if (*(char *)(DAT_080192f0 + 5) != '\0') {
    if ((*DAT_080192f4 + 100) * *(int *)(DAT_080192d4 + -0x74) < local_38) {
      local_38 = (*DAT_080192f4 + 100) * *(int *)(DAT_080192d4 + -0x74);
    }
    else {
      fVar7 = (float)VectorUnsignedToFloat
                               ((uint)*(ushort *)(DAT_080192d4 + -0x68),(byte)(in_fpscr >> 0x16) & 3
                               );
      fVar9 = (float)VectorUnsignedToFloat
                               (*(undefined4 *)(DAT_080192d4 + -0x74),(byte)(in_fpscr >> 0x16) & 3);
      fVar8 = (float)VectorUnsignedToFloat
                               (*(int *)(DAT_080192d4 + -0x74) * 0x3c,(byte)(in_fpscr >> 0x16) & 3);
      fVar8 = fVar8 - fVar7 * *(float *)(DAT_080192d4 + -0x20) * DAT_080192f8 * fVar9;
      fVar7 = (float)VectorUnsignedToFloat(local_38,(byte)(in_fpscr >> 0x16) & 3);
      uVar1 = in_fpscr & 0xfffffff | (uint)(fVar8 < fVar7) << 0x1f | (uint)(fVar8 == fVar7) << 0x1e;
      in_fpscr = uVar1 | (uint)(NAN(fVar8) || NAN(fVar7)) << 0x1c;
      bVar2 = (byte)(uVar1 >> 0x18);
      if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1))
      goto LAB_080192ca;
      if (*(char *)(iVar3 + 7) == '\x01') {
        uVar5 = VectorUnsignedToFloat(local_38,(byte)(in_fpscr >> 0x16) & 3);
        FUN_08016500(uVar5);
        pfVar6 = extraout_r3;
        goto LAB_08019292;
      }
    }
  }
  fVar7 = (float)VectorUnsignedToFloat(local_38,(byte)(in_fpscr >> 0x16) & 3);
  *pfVar6 = fVar7;
LAB_08019292:
  pfVar6[2] = (float)(int)*pfVar6;
  FUN_0801975c();
  if ((*(char *)(iVar3 + 7) == '\x01') || (*(char *)(iVar3 + 7) == '\x02')) {
    *(undefined1 *)(iVar3 + 7) = 0;
    FUN_08019844(0,0x2c);
    return;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080192fc at 0x080192fc
// ---------------------------------------------------------------------------

void FUN_080192fc(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = DAT_08019398;
  iVar1 = DAT_08019390;
  if (*(char *)(DAT_0801938c + 0x4c) != '\0') {
    if (*(char *)(DAT_08019390 + 0x52) == '\0') {
      if ((uint)*(byte *)(DAT_0801938c + 0x4d) * 2 < (uint)*(byte *)(DAT_08019394 + 0x14)) {
        *(undefined1 *)(DAT_08019398 + 0x1f) = 0;
      }
      else {
        *(char *)(DAT_08019398 + 0x1f) = *(char *)(DAT_08019398 + 0x1f) + '\x01';
        if (*DAT_080193a0 <= (ushort)*(byte *)(iVar2 + 0x1f)) {
          *(undefined1 *)(iVar2 + 0x1f) = 0;
          *(undefined1 *)(iVar1 + 0x52) = 1;
          uVar3 = 0x79;
LAB_0801934c:
          FUN_08019844(0,uVar3);
          return;
        }
      }
    }
    else if (*(char *)(DAT_08019390 + 0x52) != '\0') {
      if ((uint)*(byte *)(DAT_08019394 + 0x14) < (*(byte *)(DAT_0801938c + 0x4d) + 1) * 2) {
        *(undefined1 *)(DAT_08019398 + 0x20) = 0;
      }
      else {
        *(char *)(DAT_08019398 + 0x20) = *(char *)(DAT_08019398 + 0x20) + '\x01';
        if (*DAT_0801939c <= (ushort)*(byte *)(iVar2 + 0x20)) {
          *(undefined1 *)(iVar2 + 0x20) = 0;
          *(undefined1 *)(iVar1 + 0x52) = 0;
          uVar3 = 0x7a;
          goto LAB_0801934c;
        }
      }
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080193a4 at 0x080193a4
// ---------------------------------------------------------------------------

void FUN_080193a4(void)

{
  int iVar1;
  int iVar2;
  short sVar3;
  uint in_fpscr;
  float fVar4;
  float fVar5;
  float fVar6;
  
  iVar1 = DAT_0801951c;
  iVar2 = 0;
  if (*DAT_08019514 == '\x01') {
    if (*(char *)(DAT_08019518 + 0x3b) == '\0') {
      *(undefined4 *)(DAT_0801951c + 0x38) = 0;
      if ((uint)*DAT_08019520 * 900 <= *(uint *)(iVar1 + 0x3c)) goto LAB_080193ec;
      iVar2 = *(int *)(iVar1 + 0x3c) + 1;
    }
    else {
      *(int *)(DAT_0801951c + 0x38) = *(int *)(DAT_0801951c + 0x38) + 1;
      if (*(uint *)(iVar1 + 0x38) < 3) {
        return;
      }
      *(undefined4 *)(iVar1 + 0x38) = 0;
    }
    *(int *)(iVar1 + 0x3c) = iVar2;
    return;
  }
LAB_080193ec:
  fVar4 = DAT_08019528;
  if ((*DAT_08019524 != '\0') && (*(char *)(DAT_0801952c + 5) != '\x02')) {
    if (*DAT_08019524 == '\x01') {
      sVar3 = *(short *)(DAT_08019538 + 0x22);
    }
    else {
      sVar3 = *(short *)(DAT_08019530 + 0x118);
    }
    if ((sVar3 < 100) && (-0x28 < sVar3)) {
      if (sVar3 < *(short *)(DAT_08019524 + 10)) {
        if (sVar3 < *(short *)(DAT_08019524 + 8)) {
          if (sVar3 < *(short *)(DAT_08019524 + 6)) {
            if (sVar3 < *(short *)(DAT_08019524 + 4)) {
              fVar5 = *(float *)(DAT_08019524 + 0x10) / DAT_08019534;
              fVar6 = *(float *)(DAT_08019524 + 0x28);
              fVar4 = (float)VectorSignedToFloat((int)sVar3 - (int)*(short *)(DAT_08019524 + 2),
                                                 (byte)(in_fpscr >> 0x16) & 3);
            }
            else {
              fVar5 = *(float *)(DAT_08019524 + 0x14) / DAT_08019534;
              fVar6 = *(float *)(DAT_08019524 + 0x2c);
              fVar4 = (float)VectorSignedToFloat((int)sVar3 - (int)*(short *)(DAT_08019524 + 4),
                                                 (byte)(in_fpscr >> 0x16) & 3);
            }
          }
          else {
            fVar5 = *(float *)(DAT_08019524 + 0x18) / DAT_08019534;
            fVar6 = *(float *)(DAT_08019524 + 0x30);
            fVar4 = (float)VectorSignedToFloat((int)sVar3 - (int)*(short *)(DAT_08019524 + 6),
                                               (byte)(in_fpscr >> 0x16) & 3);
          }
        }
        else {
          fVar5 = *(float *)(DAT_08019524 + 0x1c) / DAT_08019534;
          fVar6 = *(float *)(DAT_08019524 + 0x34);
          fVar4 = (float)VectorSignedToFloat((int)sVar3 - (int)*(short *)(DAT_08019524 + 8),
                                             (byte)(in_fpscr >> 0x16) & 3);
        }
      }
      else {
        fVar5 = *(float *)(DAT_08019524 + 0x20) / DAT_08019534;
        fVar6 = *(float *)(DAT_08019524 + 0x38);
        fVar4 = (float)VectorSignedToFloat((int)sVar3 - (int)*(short *)(DAT_08019524 + 10),
                                           (byte)(in_fpscr >> 0x16) & 3);
      }
      fVar4 = (1.0 - fVar4 * fVar6) - fVar5;
    }
  }
  *(float *)(DAT_08019524 + -0x15c) = fVar4;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801953c at 0x0801953c
// ---------------------------------------------------------------------------

void FUN_0801953c(void)

{
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801953e at 0x0801953e
// ---------------------------------------------------------------------------

void FUN_0801953e(void)

{
  return;
}



// ---------------------------------------------------------------------------
// Function: SVC_Handler at 0x08019540
// ---------------------------------------------------------------------------

void SVC_Handler(void)

{
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08019544 at 0x08019544
// ---------------------------------------------------------------------------

void FUN_08019544(void)

{
  int iVar1;
  undefined4 local_10;
  
  iVar1 = DAT_08019620;
  if (*(float *)(DAT_08019620 + 0x1c) != *(float *)(DAT_08019620 + 8)) {
    *(undefined4 *)(DAT_08019620 + 0x1c) = *(undefined4 *)(DAT_08019620 + 8);
    local_10 = VectorFloatToUnsigned(*(undefined4 *)(iVar1 + 8),3);
    FUN_080127e0(0x180,&local_10,4);
  }
  if (*(float *)(iVar1 + 0x20) != *(float *)(iVar1 + 0xc)) {
    *(undefined4 *)(iVar1 + 0x20) = *(undefined4 *)(iVar1 + 0xc);
    local_10 = VectorFloatToUnsigned(*(undefined4 *)(iVar1 + 0xc),3);
    FUN_080127e0(0x184,&local_10,4);
  }
  if (*(float *)(iVar1 + 0x24) != *(float *)(iVar1 + 0x10)) {
    *(undefined4 *)(iVar1 + 0x24) = *(undefined4 *)(iVar1 + 0x10);
    local_10 = VectorFloatToUnsigned(*(undefined4 *)(iVar1 + 0x10),3);
    FUN_080127e0(0x188,&local_10,4);
  }
  if (*(float *)(iVar1 + 0x28) != *(float *)(iVar1 + 0x14)) {
    *(undefined4 *)(iVar1 + 0x28) = *(undefined4 *)(iVar1 + 0x14);
    local_10 = VectorFloatToUnsigned(*(undefined4 *)(iVar1 + 0x14),3);
    FUN_080127e0(0x18c,&local_10,4);
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08019624 at 0x08019624
// ---------------------------------------------------------------------------

undefined8 FUN_08019624(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  undefined1 local_14;
  undefined1 local_13;
  undefined1 local_12;
  undefined1 local_11;
  uint local_c;
  
  local_c = param_1;
  FUN_08012330(param_1 & 0xffff,&local_14,4,param_4,0);
  uVar1 = CONCAT31(CONCAT21(CONCAT11(local_14,local_13),local_12),local_11);
  if (0x3fffff < uVar1) {
    uVar1 = 0;
  }
  local_14 = 0;
  iVar2 = uVar1 + 1;
  local_13 = (undefined1)((uint)iVar2 >> 0x10);
  local_12 = (undefined1)((uint)iVar2 >> 8);
  local_11 = (undefined1)iVar2;
  if ((0x1bf < (ushort)local_c) && ((ushort)local_c < 0x1ff)) {
    FUN_080127e0(local_c & 0xffff,&local_14,4);
    if ((ushort)local_c == 0x1ec) {
      *(int *)(DAT_080196cc + 0x50) = iVar2;
      return CONCAT17(local_11,CONCAT16(local_12,CONCAT15(local_13,CONCAT14(local_14,iVar2))));
    }
    if ((ushort)local_c == 0x1f0) {
      *(int *)(DAT_080196cc + 0x54) = iVar2;
    }
  }
  return CONCAT17(local_11,CONCAT16(local_12,CONCAT15(local_13,CONCAT14(local_14,iVar2))));
}



// ---------------------------------------------------------------------------
// Function: FUN_080196d0 at 0x080196d0
// ---------------------------------------------------------------------------

void FUN_080196d0(uint param_1)

{
  short sVar1;
  byte local_20;
  short local_1c [6];
  uint local_10;
  
  local_10 = param_1;
  do {
    for (local_20 = 0; local_20 < 3; local_20 = local_20 + 1) {
      sVar1 = FUN_08018768(local_10 & 0xffff);
      local_1c[local_20] = sVar1;
    }
  } while ((local_1c[0] != local_1c[1]) || (local_1c[1] != local_1c[2]));
  if (local_1c[0] == -1) {
    local_1c[0] = 0;
  }
  local_1c[0] = local_1c[0] + 1;
  if ((0x1bf < (ushort)local_10) && ((ushort)local_10 < 0x1ff)) {
    FUN_08022e7c(local_10 & 0xffff,local_1c[0]);
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801975c at 0x0801975c
// ---------------------------------------------------------------------------

void FUN_0801975c(void)

{
  undefined4 uVar1;
  undefined4 local_20;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 local_14;
  undefined1 local_13;
  undefined1 local_12;
  undefined1 local_11;
  undefined1 local_10;
  undefined1 local_f;
  undefined1 local_e;
  undefined1 local_d;
  undefined1 local_c;
  undefined1 local_b;
  undefined1 local_a;
  undefined1 local_9;
  
  local_20 = 0;
  uVar1 = VectorFloatToUnsigned(*DAT_08019840,3);
  local_19 = (undefined1)uVar1;
  uVar1 = VectorFloatToUnsigned(*DAT_08019840,3);
  local_1a = (undefined1)((uint)uVar1 >> 8);
  uVar1 = VectorFloatToUnsigned(*DAT_08019840,3);
  local_1b = (undefined1)((uint)uVar1 >> 0x10);
  uVar1 = VectorFloatToUnsigned(*DAT_08019840,3);
  local_1c = (undefined1)((uint)uVar1 >> 0x18);
  if (-1 < (int)DAT_08019840[2]) {
    local_20 = DAT_08019840[2];
  }
  local_15 = (undefined1)local_20;
  local_16 = (undefined1)((uint)local_20 >> 8);
  local_17 = (undefined1)((uint)local_20 >> 0x10);
  local_18 = (undefined1)((uint)local_20 >> 0x18);
  local_11 = (undefined1)DAT_08019840[3];
  local_12 = (undefined1)((uint)DAT_08019840[3] >> 8);
  local_13 = (undefined1)((uint)DAT_08019840[3] >> 0x10);
  local_14 = (undefined1)((uint)DAT_08019840[3] >> 0x18);
  local_f = (undefined1)*(undefined2 *)(DAT_08019840 + 4);
  local_10 = (undefined1)((ushort)*(undefined2 *)(DAT_08019840 + 4) >> 8);
  local_d = (undefined1)DAT_08019840[1];
  local_e = (undefined1)((uint)DAT_08019840[1] >> 8);
  local_b = (undefined1)*(undefined2 *)(DAT_08019840 + 0x10);
  local_c = (undefined1)((ushort)*(undefined2 *)(DAT_08019840 + 0x10) >> 8);
  local_9 = (undefined1)*(undefined2 *)((int)DAT_08019840 + 0x42);
  local_a = (undefined1)((ushort)*(undefined2 *)((int)DAT_08019840 + 0x42) >> 8);
  FUN_080127e0(0xa0,&local_1c,0x14);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08019844 at 0x08019844
// ---------------------------------------------------------------------------

void FUN_08019844(undefined4 param_1,undefined4 param_2)

{
  short sVar1;
  char *pcVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  int iVar5;
  float fVar6;
  int iVar7;
  byte *pbVar8;
  int iVar9;
  float *pfVar10;
  byte bVar11;
  short sVar12;
  ushort uVar13;
  uint uVar14;
  uint in_fpscr;
  float fVar15;
  undefined4 uVar16;
  ushort local_48;
  ushort local_40;
  ushort local_3c [4];
  float local_34;
  byte local_30;
  undefined4 local_2c;
  undefined4 local_28;
  
  if (*DAT_08019c54 == '\0') {
    return;
  }
  local_2c = param_1;
  local_28 = param_2;
  if (*DAT_08019c58 == '\0') {
    if (*DAT_08019c6c == 0x20) {
      local_40 = 0x7f - *DAT_08019c5c;
      local_34 = (float)CONCAT22(local_34._2_2_,0x70 - *DAT_08019c5c);
    }
    if (*DAT_08019c6c == 0x80) {
      local_40 = -(*DAT_08019c5c + -0x1ff);
      local_34 = (float)CONCAT22(local_34._2_2_,0x1f0 - *DAT_08019c5c);
    }
    if (*DAT_08019c6c == 0x100) {
      local_40 = -(*DAT_08019c5c + -0x3ff);
      local_34 = (float)CONCAT22(local_34._2_2_,0x3f0 - *DAT_08019c5c);
    }
    if (*DAT_08019c6c == 0x200) {
      local_40 = -(*DAT_08019c5c + -0x7ff);
      local_34 = (float)CONCAT22(local_34._2_2_,0x7f0 - *DAT_08019c5c);
    }
    if (*DAT_08019c6c == 0x400) {
      local_40 = -(*DAT_08019c5c + -0xfff);
      sVar12 = 0xff0 - *DAT_08019c5c;
      goto LAB_08019954;
    }
  }
  else {
    if (*DAT_08019c60 == 0x200) {
      if (DAT_08019c68 < *DAT_08019c64) {
        local_40 = 0x208d - *DAT_08019c5c;
        sVar1 = *DAT_08019c5c;
        sVar12 = 0x207e;
      }
      else {
        local_40 = 0x2b8d - *DAT_08019c5c;
        sVar1 = *DAT_08019c5c;
        sVar12 = 0x2b7e;
      }
      sVar12 = sVar12 - sVar1;
    }
    else if ((*DAT_08019c60 == 0x100) && (*DAT_08019c64 <= DAT_08019c68)) {
      local_40 = -(*DAT_08019c5c + -0xb8d);
      sVar12 = -(*DAT_08019c5c + -0xb7e);
    }
    else {
      local_40 = 0x8d - *DAT_08019c5c;
      sVar12 = 0x7e - *DAT_08019c5c;
    }
LAB_08019954:
    local_34 = (float)CONCAT22(local_34._2_2_,sVar12);
  }
  do {
    for (local_30 = 0; local_30 < 3; local_30 = local_30 + 1) {
      uVar13 = FUN_08018768(0x1c0);
      local_3c[local_30] = uVar13;
    }
  } while ((local_3c[0] != local_3c[1]) || (local_3c[1] != local_3c[2]));
  uVar14 = (uint)local_3c[0];
  do {
    for (local_30 = 0; pcVar2 = DAT_08019c70, local_30 < 3; local_30 = local_30 + 1) {
      uVar13 = FUN_08018768(0x1c2);
      local_3c[local_30] = uVar13;
    }
  } while ((local_3c[0] != local_3c[1]) || (local_3c[1] != local_3c[2]));
  *(ushort *)(DAT_08019c70 + 2) = local_3c[0];
  if (*(short *)(pcVar2 + 2) == -1) {
    uVar13 = 1;
  }
  else if (local_34._0_2_ < *(ushort *)(pcVar2 + 2)) {
    uVar13 = local_34._0_2_;
  }
  else {
    if (local_34._0_2_ <= *(ushort *)(pcVar2 + 2)) goto LAB_08019a34;
    uVar13 = *(short *)(pcVar2 + 2) + 1;
  }
  *(ushort *)(pcVar2 + 2) = uVar13;
LAB_08019a34:
  puVar3 = DAT_08019c74;
  if ((uVar14 < local_40) && (0xf < uVar14)) {
    uVar14 = uVar14 + 1;
  }
  else {
    uVar14 = 0x10;
  }
  *DAT_08019c74 = (char)(uVar14 >> 8);
  puVar3[1] = (char)uVar14;
  puVar3[2] = (char)((ushort)*(undefined2 *)(pcVar2 + 2) >> 8);
  puVar3[3] = (char)*(undefined2 *)(pcVar2 + 2);
  FUN_080127e0(0x1c0,puVar3,4);
  if (*DAT_08019c78 != '\0') {
    FUN_0801806c();
  }
  puVar4 = DAT_08019c7c;
  *puVar3 = *DAT_08019c7c;
  puVar3[1] = puVar4[1];
  puVar3[2] = puVar4[2];
  puVar3[3] = puVar4[3];
  puVar3[4] = puVar4[4];
  puVar3[5] = puVar4[5];
  if (puVar4[5] == *pcVar2) {
    *pcVar2 = '\0';
  }
  else {
    *pcVar2 = puVar4[5];
  }
  fVar15 = DAT_08019c84;
  uVar16 = VectorFloatToUnsigned(*(float *)(DAT_08019c80 + 0x114) * DAT_08019c84,3);
  puVar3[6] = (char)((uint)uVar16 >> 8);
  puVar3[7] = (char)uVar16;
  fVar6 = DAT_08019c8c;
  iVar5 = DAT_08019c88;
  uVar16 = VectorFloatToUnsigned(*(float *)(DAT_08019c88 + 0xc) * DAT_08019c8c,3);
  puVar3[8] = (char)((uint)uVar16 >> 8);
  puVar3[9] = (char)uVar16;
  iVar7 = DAT_08019c90;
  uVar16 = VectorFloatToUnsigned(*(float *)(DAT_08019c90 + 0xc) * fVar6,3);
  puVar3[10] = (char)((uint)uVar16 >> 8);
  puVar3[0xb] = (char)uVar16;
  pbVar8 = DAT_08019c94;
  if (DAT_08019c94[0x3b] == 0) {
    if (DAT_08019c94[0x3a] == 0) {
      local_48 = 0;
    }
    else {
      uVar16 = VectorFloatToUnsigned(*(float *)(DAT_08019c98 + 0x14) * fVar15,3);
      local_48 = (ushort)uVar16;
    }
  }
  else {
    uVar16 = VectorFloatToUnsigned(*(float *)(DAT_08019c98 + 0x10) * fVar15,3);
    local_48 = ~(ushort)uVar16 + 1;
  }
  puVar3[0xc] = (char)(local_48 >> 8);
  puVar3[0xd] = (char)local_48;
  iVar9 = DAT_08019c9c;
  puVar3[0xe] = (char)*(undefined2 *)(DAT_08019c9c + 0x22) + '(';
  puVar3[0xf] = (char)*(undefined2 *)(iVar9 + 0x1e) + '(';
  pfVar10 = DAT_08019ca0;
  if (*(byte *)((int)DAT_08019ca0 + 0x12) >> 1 < 0x65) {
    puVar3[0x10] = *(byte *)((int)DAT_08019ca0 + 0x12) >> 1;
  }
  else {
    puVar3[0x10] = 100;
  }
  if ((int)pfVar10[2] < 0) {
    local_34 = 0.0;
  }
  else {
    local_34 = pfVar10[2];
  }
  puVar3[0x11] = (char)((uint)local_34 >> 0x18);
  puVar3[0x12] = (char)((uint)local_34 >> 0x10);
  puVar3[0x13] = (char)((uint)local_34 >> 8);
  puVar3[0x14] = SUB41(local_34,0);
  puVar3[0x15] = (char)((ushort)*(undefined2 *)(pfVar10 + 4) >> 8);
  puVar3[0x16] = (char)*(undefined2 *)(pfVar10 + 4);
  bVar11 = 0;
  if (((byte)local_2c < 9) && ((byte)local_2c != 0)) {
    if ((byte)local_2c == 1) {
      bVar11 = 0x80;
    }
    if ((byte)local_2c == 2) {
      bVar11 = bVar11 | 0x40;
    }
    if ((byte)local_2c == 3) {
      bVar11 = bVar11 | 0x20;
    }
    if ((byte)local_2c == 4) {
      bVar11 = bVar11 | 0x10;
    }
    if ((byte)local_2c == 5) {
      bVar11 = bVar11 | 8;
    }
    if ((byte)local_2c == 6) {
      bVar11 = bVar11 | 4;
    }
    if ((byte)local_2c == 7) {
      bVar11 = bVar11 | 2;
    }
    if ((byte)local_2c == 8) {
      bVar11 = bVar11 | 1;
    }
  }
  else {
    if ((pbVar8[0x12] & 1) != 0) {
      bVar11 = 0x80;
    }
    if ((int)((uint)pbVar8[0x12] << 0x1e) < 0) {
      bVar11 = bVar11 | 0x40;
    }
    if ((pbVar8[0x1b] & 1) != 0) {
      bVar11 = bVar11 | 0x20;
    }
    if ((int)((uint)pbVar8[0x1b] << 0x1e) < 0) {
      bVar11 = bVar11 | 0x10;
    }
  }
  puVar3[0x17] = bVar11;
  bVar11 = 0;
  if (((byte)local_2c < 9) || (0xe < (byte)local_2c)) {
    if ((int)((uint)pbVar8[0x39] << 0x1d) < 0) {
      bVar11 = 0x80;
    }
    if ((int)((uint)pbVar8[0x39] << 0x1e) < 0) {
      bVar11 = bVar11 | 0x40;
    }
    if ((pbVar8[0x39] & 1) != 0) {
      bVar11 = bVar11 | 0x20;
    }
  }
  else {
    if ((byte)local_2c == 9) {
      bVar11 = 0x80;
    }
    if ((byte)local_2c == 10) {
      bVar11 = bVar11 | 0x40;
    }
    if ((byte)local_2c == 0xb) {
      bVar11 = bVar11 | 0x20;
    }
    if ((byte)local_2c == 0xc) {
      bVar11 = bVar11 | 0x10;
    }
    if ((byte)local_2c == 0xd) {
      bVar11 = bVar11 | 8;
    }
    if ((byte)local_2c == 0xe) {
      bVar11 = bVar11 | 4;
    }
  }
  puVar3[0x18] = bVar11;
  local_48._0_1_ = 0;
  if (((byte)local_2c < 0xf) || (0x16 < (byte)local_2c)) {
    if ((*pbVar8 & 1) != 0) {
      local_48._0_1_ = 0x80;
    }
    if ((int)((uint)*pbVar8 << 0x1e) < 0) {
      local_48._0_1_ = (byte)local_48 | 0x40;
    }
    if ((int)((uint)pbVar8[0x51] << 0x1d) < 0) {
      local_48._0_1_ = (byte)local_48 | 8;
    }
    if ((int)((uint)pbVar8[0x12] << 0x1b) < 0) {
      local_48._0_1_ = (byte)local_48 | 2;
    }
  }
  else {
    local_48._0_1_ = 0;
    if ((byte)local_2c == 0xf) {
      local_48._0_1_ = 0x80;
    }
    if ((byte)local_2c == 0x10) {
      local_48._0_1_ = (byte)local_48 | 0x40;
    }
    if ((byte)local_2c == 0x11) {
      local_48._0_1_ = (byte)local_48 | 0x20;
    }
    if ((byte)local_2c == 0x12) {
      local_48._0_1_ = (byte)local_48 | 0x10;
    }
    if ((byte)local_2c == 0x13) {
      local_48._0_1_ = (byte)local_48 | 8;
      FUN_080196d0(0x1cc);
    }
    if ((byte)local_2c == '\x14') {
      local_48._0_1_ = (byte)local_48 | 4;
    }
    if ((byte)local_2c == '\x15') {
      local_48._0_1_ = (byte)local_48 | 2;
      FUN_080196d0(0x1d6);
    }
    if ((byte)local_2c == '\x16') {
      local_48._0_1_ = (byte)local_48 | 1;
    }
  }
  puVar3[0x19] = (byte)local_48;
  if (pbVar8[0x3a] == 0) {
    if (pbVar8[0x3b] == 0) {
      bVar11 = 0x20;
    }
    else {
      bVar11 = 0x40;
    }
  }
  else {
    bVar11 = 0x80;
  }
  if (pbVar8[0x4d] == 0) {
    bVar11 = bVar11 | 8;
  }
  else {
    bVar11 = bVar11 | 0x10;
  }
  if (pbVar8[0x4c] == 0) {
    bVar11 = bVar11 | 2;
  }
  else {
    bVar11 = bVar11 | 4;
  }
  puVar3[0x1a] = bVar11;
  puVar3[0x1b] = (undefined1)local_28;
  fVar15 = (float)VectorUnsignedToFloat(pfVar10[1],(byte)(in_fpscr >> 0x16) & 3);
  uVar16 = VectorFloatToUnsigned((*pfVar10 * DAT_0801a018) / fVar15,3);
  local_48 = (ushort)uVar16;
  if (100 < local_48) {
    local_48 = 100;
  }
  puVar3[0x1c] = (char)local_48;
  puVar3[0x1d] = (char)*(undefined2 *)(iVar9 + 0x40) + '(';
  puVar3[0x1e] = (char)*(undefined2 *)(iVar5 + 0x10);
  puVar3[0x1f] = (char)*(undefined2 *)(iVar7 + 0x10);
  if ((0xf < uVar14) && (uVar14 <= local_40)) {
    FUN_080127e0(uVar14 << 5,DAT_0801a01c,0x20);
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801a020 at 0x0801a020
// ---------------------------------------------------------------------------

float FUN_0801a020(void)

{
  float *pfVar1;
  float local_8;
  
  if (*(char *)(DAT_0801a068 + 0x3d) == '\x01') {
    pfVar1 = DAT_0801a070;
  }
  else {
    if (*(char *)(DAT_0801a068 + 0x3a) != '\0') {
      return DAT_0801a064;
    }
    pfVar1 = DAT_0801a074;
  }
  local_8 = *pfVar1;
  if (*(char *)(DAT_0801a068 + 0x4c) != '\0') {
    local_8 = local_8 + DAT_0801a06c;
  }
  return local_8;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801a848 at 0x0801a848
// ---------------------------------------------------------------------------

void FUN_0801a848(void)

{
  byte bVar1;
  int *piVar2;
  int *piVar3;
  byte *pbVar4;
  int iVar5;
  int iVar6;
  uint in_fpscr;
  float fVar7;
  float fVar8;
  undefined4 uVar9;
  undefined2 uVar10;
  undefined4 local_2c;
  undefined4 local_28;
  undefined2 local_24;
  
  pbVar4 = DAT_0801aa38;
  piVar3 = DAT_0801aa34;
  piVar2 = DAT_0801aa30;
  local_2c = 0;
  local_28 = 0;
  uVar10 = 0;
  local_24 = 0;
  if ((*DAT_0801aa08 == '\0') && (*DAT_0801aa0c == '\0')) {
    return;
  }
  if (*DAT_0801aa10 == 0) {
    return;
  }
  if (*DAT_0801aa14 != '\x14') {
    if (*DAT_0801aa14 != '\x1d') {
      return;
    }
    if (1 < *DAT_0801aa10) {
      return;
    }
  }
  if (*DAT_0801aa10 == 2) {
    if ((((((int)((uint)DAT_0801aa24[0x39] * 0x20000000) < 0) || ((DAT_0801aa24[0x12] & 0x13) != 0))
         || ((*DAT_0801aa24 & 0x30) != 0)) ||
        ((((int)((uint)DAT_0801aa24[0x51] << 0x1d) < 0 || (*DAT_0801aa18 != '\0')) ||
         (DAT_0801aa24[0x44] != 0)))) && ((*DAT_0801aa28 == '\0' && (*DAT_0801aa2c == '\0'))))
    goto LAB_0801a9f4;
    if ((DAT_0801aa24[0x4d] == 0) && (*DAT_0801aa28 == '\0')) goto LAB_0801a968;
    local_28 = 0;
    if ((DAT_0801aa24[0x4d] == 0) || (*DAT_0801aa28 == '\0')) {
      if ((DAT_0801aa24[0x4d] == 0) && (*DAT_0801aa28 == '\0')) goto LAB_0801a968;
      if (DAT_0801aa24[0x4d] != 0) goto LAB_0801a93c;
      if (*DAT_0801aa28 == '\0') goto LAB_0801a968;
      iVar6 = *DAT_0801aa30;
      bVar1 = *DAT_0801aa38;
      iVar5 = *DAT_0801aa34;
      goto LAB_0801a954;
    }
    fVar7 = (float)FUN_080103c8(*(byte *)(DAT_0801aa20 + 0x14) >> 1,
                                (int)*(short *)(DAT_0801aa1c + 0x1e),
                                (int)*(short *)(DAT_0801aa1c + 0x22));
    fVar8 = (float)FUN_080103c8(*pbVar4,*piVar3,*piVar2);
    fVar7 = fVar7 + fVar8;
  }
  else {
    if ((((((int)((uint)DAT_0801aa24[0x39] * 0x20000000) < 0) || ((DAT_0801aa24[0x12] & 0x13) != 0))
         || ((*DAT_0801aa24 & 0x30) != 0)) ||
        (((int)((uint)DAT_0801aa24[0x51] << 0x1d) < 0 || (*DAT_0801aa18 != '\0')))) ||
       (DAT_0801aa24[0x44] != 0)) {
LAB_0801a9f4:
      local_28 = 1;
      goto LAB_0801a968;
    }
    if (DAT_0801aa24[0x4d] == 0) goto LAB_0801a968;
LAB_0801a93c:
    iVar6 = (int)*(short *)(DAT_0801aa1c + 0x22);
    iVar5 = (int)*(short *)(DAT_0801aa1c + 0x1e);
    bVar1 = *(byte *)(DAT_0801aa20 + 0x14) >> 1;
LAB_0801a954:
    local_28 = 0;
    fVar7 = (float)FUN_080103c8(bVar1,iVar5,iVar6);
  }
  uVar9 = VectorFloatToUnsigned(fVar7 * 10.0,3);
  uVar10 = (short)uVar9;
LAB_0801a968:
  local_24 = uVar10;
  fVar8 = (float)VectorUnsignedToFloat((uint)*DAT_0801aa40,(byte)(in_fpscr >> 0x16) & 3);
  uVar9 = VectorFloatToUnsigned(*DAT_0801aa3c * fVar8 * 10.0,3);
  local_2c = CONCAT13((char)local_24,
                      CONCAT12((char)((ushort)local_24 >> 8),
                               CONCAT11((char)uVar9,(char)((uint)uVar9 >> 8))));
  FUN_08023084(&local_2c,8,DAT_0801aa44,0,4);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801aa48 at 0x0801aa48
// ---------------------------------------------------------------------------

void FUN_0801aa48(undefined1 param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = DAT_0801aa70;
  *DAT_0801aa70 = 0xea;
  puVar1[1] = 0xd1;
  puVar1[2] = 1;
  puVar1[3] = 4;
  puVar1[4] = param_1;
  puVar1[5] = param_2;
  FUN_0801e980();
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801ab24 at 0x0801ab24
// ---------------------------------------------------------------------------

void FUN_0801ab24(void)

{
  undefined1 *puVar1;
  int iVar2;
  
  puVar1 = DAT_0801ab94;
  *DAT_0801ab94 = 0xea;
  puVar1[1] = 0xd1;
  puVar1[2] = 1;
  puVar1[3] = 0x25;
  puVar1[4] = 0xff;
  puVar1[5] = 9;
  puVar1[6] = 1;
  FUN_08012330(0x1c0,puVar1 + 7,0x20);
  FUN_0801e980(puVar1);
  iVar2 = DAT_0801ab98;
  do {
  } while (*(short *)(*(int *)(DAT_0801ab98 + 0x1c) + 0x25a) != 0);
  FUN_0800db18(0x32);
  puVar1[6] = 2;
  FUN_08012330(0x1e0,puVar1 + 7,0x20);
  FUN_0801e980(DAT_0801ab94);
  do {
  } while (*(short *)(*(int *)(iVar2 + 0x1c) + 0x25a) != 0);
  FUN_0800db18(7);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801b55c at 0x0801b55c
// ---------------------------------------------------------------------------

undefined8 FUN_0801b55c(undefined4 param_1)

{
  char *pcVar1;
  int iVar2;
  byte bVar3;
  uint in_fpscr;
  undefined4 uVar4;
  float fVar5;
  undefined8 uVar6;
  undefined1 local_20;
  undefined1 uStack_1f;
  undefined1 local_1c;
  undefined1 uStack_1b;
  undefined1 uStack_1a;
  undefined1 uStack_19;
  undefined4 local_18;
  undefined4 local_14;
  
  uVar4 = VectorFloatToUnsigned(*DAT_0801b740 / 10.0,3);
  local_20 = (undefined1)uVar4;
  local_1c = local_20;
  uStack_1f = (undefined1)((uint)uVar4 >> 8);
  uStack_1b = uStack_1f;
  if ((int)DAT_0801b740[2] < 0) {
    local_20 = 0;
    uStack_1f = 0;
  }
  else {
    local_20 = (undefined1)((int)DAT_0801b740[2] / 10);
    uStack_1f = (undefined1)((uint)((int)DAT_0801b740[2] / 10) >> 8);
  }
  uStack_1a = local_20;
  uStack_19 = uStack_1f;
  local_18 = (uint)(*(byte *)(DAT_0801b740 + 5) >> 1);
  local_14 = param_1;
  if (DAT_0801b740[1] == 0.0) {
    local_18 = (uint)(*(byte *)(DAT_0801b740 + 5) >> 1);
  }
  else {
    fVar5 = (float)VectorUnsignedToFloat(DAT_0801b740[1],(byte)(in_fpscr >> 0x16) & 3);
    uVar6 = FUN_080085d2(*DAT_0801b740 / fVar5);
    uVar6 = FUN_08008364((int)uVar6,(int)((ulonglong)uVar6 >> 0x20),(int)DAT_0801b744,
                         (int)((ulonglong)DAT_0801b744 >> 0x20));
    FUN_08008216((int)uVar6,(int)((ulonglong)uVar6 >> 0x20),(int)DAT_0801b74c,
                 (int)((ulonglong)DAT_0801b74c >> 0x20));
    bVar3 = FUN_080085a0();
    local_18._0_2_ = CONCAT11(bVar3,(undefined1)local_18);
    if (100 < bVar3) {
      local_18._0_2_ = CONCAT11(100,(undefined1)local_18);
    }
  }
  pcVar1 = DAT_0801b758;
  if (((*(char *)(DAT_0801b754 + 0x4c) != '\0') && (*(char *)(DAT_0801b754 + 0x44) == '\0')) &&
     (*(char *)(DAT_0801b754 + 0x45) == '\0')) {
    if (*DAT_0801b758 != '\x01') {
      uVar4 = FUN_08010654();
      iVar2 = DAT_0801b75c;
      fVar5 = (float)VectorUnsignedToFloat(uVar4,(byte)(in_fpscr >> 0x16) & 3);
      if (pcVar1[7] == '\0') {
        uVar4 = VectorFloatToUnsigned(fVar5,3);
        local_18._0_3_ = CONCAT12((char)uVar4,(undefined2)local_18);
        if (fVar5 + 3.0 < *(float *)(DAT_0801b75c + 0x10)) {
          pcVar1[9] = pcVar1[9] + '\x01';
          if (0x14 < (byte)pcVar1[9]) {
            pcVar1[9] = '\0';
            uVar4 = VectorFloatToUnsigned
                              ((1.0 - ((*(float *)(iVar2 + 0x10) - fVar5) * 2.0) / fVar5) * fVar5,3)
            ;
            pcVar1[8] = (char)uVar4;
            if (pcVar1[8] == '\0') {
              pcVar1[8] = '\x01';
            }
            pcVar1[7] = '\x01';
          }
          goto LAB_0801b708;
        }
      }
      else {
        if (pcVar1[7] == '\x01') {
          local_18._0_3_ = CONCAT12(pcVar1[8],(undefined2)local_18);
          if (DAT_0801b760 <= (int)fVar5) {
            if (fVar5 - 5.0 <= *(float *)(DAT_0801b75c + 0x10)) {
              if (*(float *)(DAT_0801b75c + 0x10) <= fVar5 + 3.0) goto LAB_0801b6bc;
            }
          }
          pcVar1[9] = pcVar1[9] + '\x01';
          if (0x32 < (byte)pcVar1[9]) {
            pcVar1[9] = '\0';
            pcVar1[7] = '\0';
          }
          goto LAB_0801b708;
        }
        pcVar1[7] = '\0';
      }
LAB_0801b6bc:
      pcVar1[9] = '\0';
      goto LAB_0801b708;
    }
  }
  local_18._0_3_ = CONCAT12(1,(undefined2)local_18);
LAB_0801b708:
  uVar4 = FUN_0801ef94(local_14);
  FUN_08023084(&local_1c,7,uVar4,0);
  return CONCAT17(uStack_19,CONCAT16(uStack_1a,CONCAT15(uStack_1b,CONCAT14(local_1c,4))));
}



// ---------------------------------------------------------------------------
// Function: FUN_0801b764 at 0x0801b764
// ---------------------------------------------------------------------------

void FUN_0801b764(undefined4 param_1)

{
  undefined1 uVar1;
  undefined4 uVar2;
  float fVar3;
  undefined2 uVar4;
  undefined1 local_14;
  undefined1 uStack_13;
  undefined1 uStack_12;
  undefined1 uStack_11;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if (*(char *)(DAT_0801b854 + 0x3b) == '\0') {
    if (*(char *)(DAT_0801b854 + 0x3a) == '\0') {
      uVar1 = 2;
    }
    else {
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  uVar4 = 0;
  if (*(char *)(DAT_0801b854 + 0x3b) == '\0') {
    if (*(char *)(DAT_0801b854 + 0x3a) == '\0') goto LAB_0801b7c2;
    fVar3 = *(float *)(DAT_0801b858 + 0x14);
  }
  else {
    fVar3 = *(float *)(DAT_0801b858 + 0x10);
  }
  uVar2 = VectorFloatToUnsigned(fVar3 * DAT_0801b85c,3);
  uVar4 = (undefined2)uVar2;
LAB_0801b7c2:
  local_c = VectorFloatToUnsigned(*(float *)(DAT_0801b860 + 0x114) * DAT_0801b864,3);
  _local_14 = CONCAT13((char)local_c,
                       CONCAT12((char)((ushort)uVar4 >> 8),CONCAT11((char)uVar4,uVar1)));
  local_10 = CONCAT13((char)*(undefined2 *)(DAT_0801b868 + 0x22) + '(',
                      CONCAT12((char)*(undefined2 *)(DAT_0801b868 + 0x1e) + '(',
                               (short)((uint)local_c >> 8)));
  local_8 = param_1;
  uVar2 = FUN_0801ef94(param_1);
  FUN_08023084(&local_14,8,uVar2,0,4);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801ba30 at 0x0801ba30
// ---------------------------------------------------------------------------

void FUN_0801ba30(undefined4 param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_8;
  
  local_14 = (uint)(*DAT_0801bac4 != '\0');
  if ((*DAT_0801bac8 != '\0') || (*DAT_0801bacc != '\0')) {
    local_14 = (uint)CONCAT12(1,(ushort)(*DAT_0801bac4 != '\0'));
  }
  if (*(char *)(DAT_0801bad0 + 0xf) == '\0') {
    bVar1 = *(char *)(DAT_0801bad8 + 0x4c) != '\0';
    local_10 = (uint)bVar1;
    if (*(char *)(DAT_0801bad8 + 0x4d) != '\0') {
      local_10._0_2_ = CONCAT11(1,bVar1);
      local_10 = (uint)(ushort)local_10;
    }
  }
  else {
    local_10 = 0;
  }
  if (*DAT_0801bad4 != '\0') {
    local_10 = (uint)CONCAT12(1,(ushort)local_10);
  }
  local_8 = param_1;
  uVar2 = FUN_0801ef94(param_1);
  FUN_08023084(&local_14,7,uVar2,0,4);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801badc at 0x0801badc
// ---------------------------------------------------------------------------

void FUN_0801badc(undefined4 param_1)

{
  byte bVar1;
  uint3 uVar2;
  undefined4 uVar3;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_18;
  
  local_20 = 0;
  bVar1 = *(byte *)(DAT_0801bbe8 + 5);
  local_24._0_2_ = (ushort)bVar1;
  if (DAT_0801bbec[0x3a] == 0) {
    if (DAT_0801bbec[0x3b] == 0) {
      local_24._0_2_ = CONCAT11(2,bVar1);
    }
  }
  else {
    local_24._0_2_ = CONCAT11(1,bVar1);
  }
  if ((((((DAT_0801bbec[0x39] & 3) == 0) && ((DAT_0801bbec[0x1b] & 3) == 0)) &&
       (-1 < (int)((uint)*DAT_0801bbec << 0x1e))) &&
      ((-1 < (int)((uint)DAT_0801bbec[0x51] << 0x1d) && ((DAT_0801bbec[0x10] & 3) == 0)))) &&
     (*DAT_0801bbf0 != '\x11')) {
    local_24._0_3_ = (uint3)(ushort)local_24;
    uVar2 = (uint3)local_24;
  }
  else {
    local_24._0_3_ = CONCAT12(1,(ushort)local_24);
    uVar2 = (uint3)local_24;
  }
  local_24 = (uint)uVar2;
  if (*(char *)(DAT_0801bbe8 + 6) == '\x14') {
    if ((*DAT_0801bbf4 == '\0') && (*DAT_0801bbf8 == '\0')) {
      if (((*DAT_0801bbfc != '\0') || (*DAT_0801bc00 != '\0')) && (DAT_0801bbec[0x4c] != 0)) {
        local_24 = CONCAT13(1,uVar2);
      }
    }
    else if (DAT_0801bbec[0x4d] != 0) {
      local_20 = 1;
    }
  }
  else if (*(char *)(DAT_0801bbe8 + 6) == '\x1d') {
    if ((*DAT_0801bbf4 == '\0') && (*DAT_0801bbf8 == '\0')) {
      if (((*DAT_0801bbfc != '\0') || (*DAT_0801bc00 != '\0')) && (DAT_0801bbec[0x4c] != 0)) {
        local_24 = CONCAT13(2,uVar2);
      }
    }
    else if (DAT_0801bbec[0x4d] != 0) {
      local_20 = 2;
    }
  }
  local_18 = param_1;
  uVar3 = FUN_0801ef94(param_1);
  FUN_08023084(&local_24,5,uVar3,0,4);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801bc04 at 0x0801bc04
// ---------------------------------------------------------------------------

void FUN_0801bc04(undefined4 param_1)

{
  short sVar1;
  int iVar2;
  undefined1 uVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  undefined1 local_1c;
  undefined1 uStack_1b;
  undefined1 uStack_1a;
  undefined1 uStack_19;
  undefined4 local_18;
  
  iVar2 = DAT_0801bcec;
  local_18 = 0;
  sVar1 = ((short)*(int *)(DAT_0801bce8 + 4) + (short)(*(int *)(DAT_0801bce8 + 4) << 2)) * 2;
  _local_1c = CONCAT13((char)((ushort)sVar1 >> 8),
                       CONCAT12((char)sVar1,CONCAT11(*DAT_0801bce4,*DAT_0801bce0)));
  uVar5 = FUN_080085d2(*(float *)(DAT_0801bcec + 8) - 1.0);
  FUN_08008364((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),(int)DAT_0801bcf0,
               (int)((ulonglong)DAT_0801bcf0 >> 0x20));
  uVar3 = FUN_080085a0();
  uVar4 = VectorFloatToUnsigned(*(float *)(iVar2 + 4) - 1.0,3);
  local_18 = CONCAT13(3,CONCAT12(0xe8,CONCAT11((char)uVar4,uVar3)));
  uVar4 = FUN_0801ef94(param_1);
  FUN_08023084(&local_1c,8,uVar4,0,4);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801ca08 at 0x0801ca08
// ---------------------------------------------------------------------------

void FUN_0801ca08(void)

{
  FUN_0800a670(DAT_0801ca50,8,0x104,0,4);
  FUN_0800db18(1);
  FUN_0800a670(DAT_0801ca50 + 8,8,0x105,0,4);
  FUN_0800db18(1);
  FUN_0800a670(DAT_0801ca50 + 0x10,8,0x106,0,4);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801ca54 at 0x0801ca54
// ---------------------------------------------------------------------------

void FUN_0801ca54(void)

{
  undefined4 *puVar1;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  
  FUN_0801eb74();
  puVar1 = DAT_0801cd48;
  pcVar4 = DAT_0801cd44;
  if (DAT_0801cd44[0x25c] == '\x01') {
    if (*DAT_0801cd44 == -0x16) {
      if (DAT_0801cd44[1] == -0x2f) {
        if ((DAT_0801cd44[2] == -1) || (DAT_0801cd44[2] == '\x01')) {
          DAT_0801cd44[0x262] = '\x01';
          *puVar1 = pcVar4;
          iVar3 = FUN_0801832c();
          if (iVar3 != 0) {
            FUN_0801cd64(pcVar4 + 4);
            if ((pcVar4[4] == -1) && (pcVar4[5] == '\x12')) {
              FUN_0800bc4c();
            }
            goto LAB_0801cacc;
          }
        }
LAB_0801ca86:
        pcVar4 = DAT_0801cd44;
        goto LAB_0801cd38;
      }
    }
    else if (*DAT_0801cd44 == -0x15) {
      if (DAT_0801cd44[1] != '\x01') goto LAB_0801ca86;
      DAT_0801cd44[0x262] = '\x01';
      *puVar1 = pcVar4;
      iVar3 = FUN_08016764();
      if (iVar3 == 0) {
        FUN_0800c5fe(DAT_0801cd44);
      }
      FUN_08016684();
    }
LAB_0801cacc:
    FUN_0800c5fe(DAT_0801cd44);
  }
  pcVar4 = DAT_0801cd4c;
  if (DAT_0801cd4c[0x25c] == '\x01') {
    if (*DAT_0801cd4c == -0x16) {
      if (DAT_0801cd4c[1] == -0x2f) {
        if ((DAT_0801cd4c[2] == -1) || (DAT_0801cd4c[2] == '\x01')) {
          DAT_0801cd4c[0x262] = '\x02';
          *puVar1 = pcVar4;
          iVar3 = FUN_0801832c();
          if (iVar3 != 0) {
            FUN_0801cd64(pcVar4 + 4);
            if ((pcVar4[4] == -1) && (pcVar4[5] == '\x12')) {
              FUN_0800bc4c();
            }
            goto LAB_0801cb44;
          }
        }
LAB_0801cafe:
        pcVar4 = DAT_0801cd4c;
        goto LAB_0801cd38;
      }
    }
    else if (*DAT_0801cd4c == -0x15) {
      if (DAT_0801cd4c[1] != '\x01') goto LAB_0801cafe;
      DAT_0801cd4c[0x262] = '\x02';
      *puVar1 = pcVar4;
      iVar3 = FUN_08016764();
      if (iVar3 == 0) {
        FUN_0800c5fe(DAT_0801cd4c);
      }
      FUN_08016684();
    }
LAB_0801cb44:
    FUN_0800c5fe(DAT_0801cd4c);
  }
  pcVar4 = DAT_0801cd50;
  if (DAT_0801cd50[0x25c] == '\x01') {
    if (*DAT_0801cd50 == -0x16) {
      if (DAT_0801cd50[1] == -0x2f) {
        if ((DAT_0801cd50[2] == -1) || (DAT_0801cd50[2] == '\x01')) {
          DAT_0801cd50[0x262] = '\x03';
          *puVar1 = pcVar4;
          iVar3 = FUN_0801832c();
          if (iVar3 != 0) {
            FUN_0801cd64(pcVar4 + 4);
            goto LAB_0801cbac;
          }
        }
LAB_0801cb76:
        pcVar4 = DAT_0801cd50;
        goto LAB_0801cd38;
      }
    }
    else if (*DAT_0801cd50 == -0x15) {
      if (DAT_0801cd50[1] != '\x01') goto LAB_0801cb76;
      DAT_0801cd50[0x262] = '\x03';
      *puVar1 = pcVar4;
      iVar3 = FUN_08016764();
      if (iVar3 == 0) {
        FUN_0800c5fe(DAT_0801cd50);
      }
      FUN_08016684();
    }
LAB_0801cbac:
    FUN_0800c5fe(DAT_0801cd50);
  }
  pcVar4 = DAT_0801cd54;
  if (DAT_0801cd54[0x25c] == '\x01') {
    if (*DAT_0801cd54 == -0x16) {
      if (DAT_0801cd54[1] == -0x2f) {
        if ((DAT_0801cd54[2] == -1) || (DAT_0801cd54[2] == '\x01')) {
          DAT_0801cd54[0x262] = '\x04';
          *puVar1 = pcVar4;
          iVar3 = FUN_0801832c();
          if (iVar3 != 0) {
            FUN_0801cd64(pcVar4 + 4);
            if ((pcVar4[4] == -1) && (pcVar4[5] == '\x12')) {
              FUN_0800bc4c();
            }
            goto LAB_0801cc42;
          }
        }
LAB_0801cbe8:
        pcVar4 = DAT_0801cd54;
        goto LAB_0801cd38;
      }
    }
    else if (*DAT_0801cd54 == -0x15) {
      if (DAT_0801cd54[1] != '\x01') goto LAB_0801cbe8;
      DAT_0801cd54[0x262] = '\x04';
      *puVar1 = pcVar4;
      iVar3 = FUN_08016764();
      if (iVar3 == 0) {
        FUN_0800c5fe(DAT_0801cd54);
      }
      FUN_08016684();
    }
LAB_0801cc42:
    FUN_0800c5fe(DAT_0801cd54);
  }
  else if (DAT_0801cd54[0x25c] == '\x02') {
    if (*DAT_0801cd54 == '\x01') {
      DAT_0801cd54[0x262] = '\x04';
    }
    goto LAB_0801cc42;
  }
  pcVar2 = DAT_0801cd5c;
  pcVar4 = DAT_0801cd58;
  if (DAT_0801cd58[0x25c] == '\x01') {
    if (*DAT_0801cd58 == -0x16) {
      if (DAT_0801cd58[1] == -0x2f) {
        if ((DAT_0801cd58[2] == -1) || (DAT_0801cd58[2] == *DAT_0801cd5c)) {
          DAT_0801cd58[0x262] = '\x05';
          *puVar1 = pcVar4;
          iVar3 = FUN_0801832c();
          if (iVar3 != 0) {
            if ((pcVar4[4] == -1) && (pcVar4[5] == '&')) {
              FUN_0800c260();
            }
            FUN_0801cd64(pcVar4 + 4);
            if ((pcVar4[4] == -1) && (pcVar4[5] == '\x12')) {
              FUN_0800bc4c();
            }
            goto LAB_0801ccd0;
          }
        }
LAB_0801cc8c:
        pcVar4 = DAT_0801cd58;
        goto LAB_0801cd38;
      }
    }
    else if (*DAT_0801cd58 == -0x15) {
      if (DAT_0801cd58[1] != *DAT_0801cd5c) goto LAB_0801cc8c;
      DAT_0801cd58[0x262] = '\x05';
      *puVar1 = pcVar4;
      iVar3 = FUN_08016764();
      if (iVar3 == 0) {
        FUN_0800c5fe(DAT_0801cd58);
      }
      FUN_08016684();
    }
LAB_0801ccd0:
    FUN_0800c5fe(DAT_0801cd58);
  }
  pcVar4 = DAT_0801cd60;
  if (DAT_0801cd60[0x25c] != '\x01') {
    return;
  }
  if (*DAT_0801cd60 == -0x16) {
    if ((DAT_0801cd60[1] == -0x2f) && ((DAT_0801cd60[2] == -1 || (DAT_0801cd60[2] == *pcVar2)))) {
      DAT_0801cd60[0x262] = '\x06';
      *puVar1 = pcVar4;
      iVar3 = FUN_0801832c();
      if (iVar3 != 0) {
        FUN_0801cd64(pcVar4 + 4);
      }
    }
  }
  else if ((*DAT_0801cd60 == -0x15) && (DAT_0801cd60[1] == *pcVar2)) {
    DAT_0801cd60[0x262] = '\x06';
    *puVar1 = pcVar4;
    iVar3 = FUN_08016764();
    if (iVar3 == 0) {
      FUN_0800c5fe(DAT_0801cd60);
    }
    FUN_08016684();
  }
  pcVar4 = DAT_0801cd60;
LAB_0801cd38:
  FUN_0800c5fe(pcVar4);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801cd64 at 0x0801cd64
// ---------------------------------------------------------------------------

/* WARNING: Removing unreachable block (ram,0x0801a17c) */

byte * FUN_0801cd64(byte *param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  undefined2 uVar1;
  float *pfVar2;
  float fVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  undefined1 *puVar8;
  undefined1 *puVar9;
  undefined1 *puVar10;
  undefined1 *puVar11;
  undefined1 *puVar12;
  undefined4 *puVar13;
  undefined1 *puVar14;
  char *pcVar15;
  char *pcVar16;
  undefined1 *puVar17;
  undefined1 *puVar18;
  float *pfVar19;
  undefined2 *puVar20;
  undefined1 *puVar21;
  undefined1 *puVar22;
  undefined1 *puVar23;
  undefined1 *puVar24;
  int *piVar25;
  undefined4 *puVar26;
  int iVar27;
  int iVar28;
  undefined1 uVar29;
  byte bVar30;
  char cVar31;
  char cVar32;
  undefined1 uVar33;
  short sVar34;
  ushort uVar35;
  undefined2 uVar36;
  int iVar37;
  byte *pbVar38;
  byte *pbVar39;
  undefined4 uVar40;
  int iVar41;
  byte *pbVar42;
  short sVar43;
  undefined4 uVar44;
  uint uVar45;
  uint uVar46;
  byte *unaff_r4;
  uint unaff_r6;
  bool bVar47;
  uint in_fpscr;
  float fVar48;
  float fVar49;
  undefined8 unaff_d8;
  byte local_60 [8];
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined1 auStack_48 [8];
  undefined4 uStack_40;
  undefined4 local_3c;
  ushort uStack_38;
  undefined1 uStack_36;
  undefined1 uStack_35;
  byte abStack_34 [4];
  ushort local_30;
  undefined1 uStack_2e;
  undefined1 uStack_2d;
  undefined4 local_2c;
  undefined4 local_28;
  undefined2 local_24;
  undefined1 uStack_22;
  undefined1 uStack_21;
  undefined2 local_20;
  undefined2 uStack_1e;
  byte local_1c;
  char cStack_1b;
  undefined1 uStack_1a;
  byte bStack_19;
  byte bVar50;
  longlong lVar51;
  ulonglong uVar52;
  uint3 uVar53;
  
  uVar33 = local_24._1_1_;
  iVar28 = DAT_08022e74;
  iVar27 = DAT_080229c4;
  puVar26 = DAT_0802239c;
  puVar24 = DAT_0801e96c;
  puVar23 = DAT_0801e7a8;
  puVar22 = DAT_0801e6d8;
  puVar21 = DAT_0801e5bc;
  puVar18 = DAT_0801e528;
  puVar17 = DAT_0801e248;
  puVar14 = DAT_0801e174;
  fVar48 = DAT_0801d180;
  fVar3 = DAT_0801d17c;
  iVar41 = DAT_0801d178;
  puVar13 = DAT_0801d170;
  puVar12 = DAT_0801b44c;
  puVar11 = DAT_0801b3f4;
  puVar10 = DAT_0801ab1c;
  puVar9 = DAT_0801aac4;
  puVar8 = DAT_0801a814;
  puVar7 = DAT_0801a438;
  puVar6 = DAT_0801a3a0;
  puVar5 = DAT_0801a304;
  puVar4 = DAT_08018568;
  pfVar2 = DAT_0800c3f4;
  iVar37 = DAT_0800c2f0;
  local_20._0_1_ = (byte)unaff_d8;
  local_20._1_1_ = (char)((ulonglong)unaff_d8 >> 8);
  uStack_1e = (undefined2)((ulonglong)unaff_d8 >> 0x10);
  uVar36 = uStack_1e;
  local_1c = (byte)((ulonglong)unaff_d8 >> 0x20);
  bVar30 = local_1c;
  cStack_1b = (char)((ulonglong)unaff_d8 >> 0x28);
  cVar31 = cStack_1b;
  uStack_1a = (undefined1)((ulonglong)unaff_d8 >> 0x30);
  uVar29 = uStack_1a;
  bStack_19 = (byte)((ulonglong)unaff_d8 >> 0x38);
  bVar50 = bStack_19;
  pbVar38 = (byte *)(uint)*param_1;
  if (pbVar38 == &Reset) {
    return pbVar38;
  }
  if (pbVar38 != (byte *)0xff) {
    return pbVar38;
  }
  uVar45 = (uint)param_1[1];
  if (0x8a < uVar45) {
    return DAT_0801d174;
  }
  uVar46 = (&switchD_0801cd98::switchdataD_0801cd9c)[uVar45];
  local_24._1_1_ = (undefined1)(uVar46 >> 8);
  uStack_1e = (undefined2)(uVar46 >> 0x10);
  cStack_1b = (char)(param_4 >> 8);
  uStack_1a = (undefined1)(param_4 >> 0x10);
  bStack_19 = (byte)(param_4 >> 0x18);
  pbVar38 = DAT_0801d174;
  switch(uVar45) {
  case 0:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_080127e0(0xc0,param_1 + 2,0x20);
    FUN_08012330(0xc0,DAT_08022a74,0x20);
    bVar30 = 0;
    while( true ) {
      if (0x1f < bVar30) {
        bVar30 = FUN_0800ba48(DAT_08022a74,0x20);
        FUN_080127e0(0x15b,abStack_34 + 0x20,1);
        pbVar38 = (byte *)FUN_08018354(0x15b);
        if (pbVar38 == (byte *)(uint)bVar30) {
          FUN_08014060();
          pbVar38 = (byte *)FUN_0801aa48(0xff);
        }
        return pbVar38;
      }
      pbVar38 = (byte *)(uint)(param_1 + 2)[bVar30];
      if (pbVar38 != (byte *)(uint)*(byte *)(DAT_08022a74 + (uint)bVar30)) break;
      bVar30 = bVar30 + 1;
    }
    return pbVar38;
  case 1:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_08008200(&local_24,0x20);
    uVar40 = *DAT_0801c6b8;
    uVar44 = DAT_0801c6b8[1];
    local_30 = local_30 & 0xff00;
    iVar37 = *DAT_0801c6bc;
    while (((byte)local_30 < 0x1f && (*(char *)(iVar37 + (uint)(byte)local_30) != '\0'))) {
      *(undefined1 *)((int)&local_28 + (byte)local_30 + 3) =
           *(undefined1 *)(iVar37 + (uint)(byte)local_30);
      local_30 = CONCAT11(local_30._1_1_,(byte)local_30 + 1);
    }
    local_2c._0_3_ = (undefined3)uVar40;
    if ((byte)local_30 == 0) {
      local_2c = CONCAT13(5,(undefined3)local_2c);
      local_28 = uVar44;
    }
    else {
      local_2c = CONCAT13((byte)local_30 + 5,(undefined3)local_2c);
      local_28._3_1_ = (byte)((uint)uVar44 >> 0x18);
      local_28._0_2_ = (short)uVar44;
      local_28._0_3_ = CONCAT12((byte)local_30,(short)local_28);
    }
    pbVar38 = (byte *)FUN_0801e980(&local_2c);
    return pbVar38;
  case 2:
    bVar47 = false;
    goto LAB_0801d09e;
  case 3:
    local_1c = 0xff;
    cStack_1b = 0;
    uStack_1a = 0;
    bStack_19 = 0;
    *DAT_0801e174 = 0xea;
    puVar14[1] = 0xd1;
    puVar14[2] = 1;
    pcVar16 = DAT_0801e180;
    pcVar15 = DAT_0801e17c;
    pbVar38 = DAT_0801e178;
    puVar14[3] = *DAT_0801e178 + *DAT_0801e17c + *DAT_0801e180 + '\x17';
    puVar14[4] = 0xff;
    puVar14[5] = 3;
    pbVar39 = DAT_0801e184;
    if (DAT_0801e184[0x3b] == 0) {
      if (DAT_0801e184[0x3a] == 0) {
        puVar14[6] = 0;
        puVar14[7] = 0;
        puVar14[8] = 0;
        goto LAB_0801dec0;
      }
      uVar40 = VectorFloatToUnsigned(*(float *)(DAT_0801e188 + 0x14) * DAT_0801e18c,3);
      uVar1 = (undefined2)uVar40;
      puVar14[6] = 2;
    }
    else {
      uVar40 = VectorFloatToUnsigned(*(float *)(DAT_0801e188 + 0x10) * DAT_0801e18c,3);
      uVar1 = (undefined2)uVar40;
      puVar14[6] = 1;
    }
    local_2c = CONCAT22(local_2c._2_2_,uVar1);
    puVar14[7] = (char)((ushort)uVar1 >> 8);
    puVar14[8] = (char)uVar1;
LAB_0801dec0:
    puVar14[6] = *pcVar15 << 4 | *pcVar16 << 5 | puVar14[6];
    puVar14[9] = pbVar39[0x12];
    puVar14[10] = pbVar39[0x1b];
    puVar14[0xb] = *pbVar39 | pbVar39[0x51];
    puVar14[0xc] = pbVar39[0x39] | pbVar39[0x10] << 4;
    if (*DAT_0801e190 == '\x01') {
      puVar14[0xc] = puVar14[0xc] & 0xfb;
    }
    bVar30 = *pbVar38 + *pcVar15 + *pcVar16;
    local_30 = CONCAT11(local_30._1_1_,bVar30);
    puVar14[0xd] = bVar30;
    iVar37 = DAT_0801e194;
    local_28 = (uint)local_28._2_2_ << 0x10;
    while ((local_28 & 0xffff) < (uint)*pbVar38) {
      puVar14[(local_28 & 0xffff) + 0xe] =
           (char)*(undefined2 *)(iVar37 + (local_28 & 0xffff) * 2 + 0x102) + '(';
      local_28 = CONCAT22(local_28._2_2_,(short)local_28 + 1);
    }
    local_20._0_1_ = *pcVar15 == '\x01';
    if ((bool)(byte)local_20) {
      puVar14[*pbVar38 + 0xe] = (char)*(undefined2 *)(DAT_0801e198 + 0x40) + '(';
    }
    if (*pcVar16 == '\x01') {
      puVar14[(uint)*pbVar38 + (uint)(byte)local_20 + 0xe] =
           (char)*(undefined2 *)(iVar37 + 0x118) + '(';
    }
    uVar40 = VectorFloatToUnsigned((*DAT_0801e19c + DAT_0801e1a0) * DAT_0801e1a4,3);
    puVar14[bVar30 + 0xe] = (char)((uint)uVar40 >> 8);
    puVar14[bVar30 + 0xf] = (char)uVar40;
    uVar40 = *(undefined4 *)(DAT_0801e1a8 + 0xc);
    local_24._0_1_ = (byte)uVar40;
    local_24._1_1_ = (undefined1)((uint)uVar40 >> 8);
    uStack_22 = (undefined1)((uint)uVar40 >> 0x10);
    uStack_21 = (undefined1)((uint)uVar40 >> 0x18);
    puVar14[bVar30 + 0x10] = uStack_22;
    puVar14[bVar30 + 0x11] = local_24._1_1_;
    puVar14[bVar30 + 0x12] = (byte)local_24;
    uVar40 = VectorFloatToUnsigned((*DAT_0801e1ac + DAT_0801e1b0) * 10.0,3);
    puVar14[bVar30 + 0x13] = (char)uVar40;
    if ((*DAT_0801e1b4 == '\x01') && (*DAT_0801e1b8 == '\x02')) {
      local_2c = CONCAT22(local_2c._2_2_,1);
    }
    else {
      local_2c = (uint)local_2c._2_2_ << 0x10;
    }
    puVar14[bVar30 + 0x14] = (byte)local_2c | pbVar39[0x4c] << 1 | pbVar39[0x4d] << 2;
    if (*(char *)(DAT_0801e1bc + 5) == '\x02') {
      puVar14[bVar30 + 0x14] = puVar14[bVar30 + 0x14] | 8;
    }
    if (*DAT_0801e1c0 == '\0') {
      puVar14[bVar30 + 0x14] = puVar14[bVar30 + 0x14] | 0x10;
    }
    if (*DAT_0801e1c4 == '\0') {
      puVar14[bVar30 + 0x14] = puVar14[bVar30 + 0x14] | 0x20;
    }
    if (*DAT_0801e1c8 == '\x01') {
      puVar14[bVar30 + 0x14] = puVar14[bVar30 + 0x14] | 0x40;
    }
    if (*DAT_0801e1cc != '\0') {
      puVar14[bVar30 + 0x14] = puVar14[bVar30 + 0x14] | 0x80;
    }
    puVar14[bVar30 + 0x15] =
         (pbVar39[7] & 0x10) << 3 | (pbVar39[8] & 0x10) << 2 | pbVar39[0x50] << 4 |
         pbVar39[0x44] << 3 | pbVar39[0x45] << 2 | pbVar39[0x46] << 1 | pbVar39[0x47];
    puVar14[bVar30 + 0x16] =
         pbVar39[7] << 7 | (pbVar39[8] & 1) << 6 | pbVar39[0x48] << 5 | pbVar39[0x49] << 4 |
         pbVar39[0x34] << 3 | pbVar39[0x2f] << 2 | pbVar39[0x2a] << 1 | pbVar39[0x25];
    puVar14[bVar30 + 0x17] = pbVar39[0x52] << 2 | pbVar39[0x11] << 3 | pbVar39[0xf];
    puVar14[bVar30 + 0x18] = uStack_21;
    uStack_1e = uVar36;
    pbVar38 = (byte *)FUN_0801e980(DAT_0801e174);
    return pbVar38;
  case 4:
    *DAT_0801e528 = 0xea;
    puVar18[1] = 0xd1;
    bVar30 = 1;
    puVar18[2] = 1;
    puVar18[3] = 0x39;
    puVar18[4] = 0xff;
    puVar18[5] = 4;
    puVar18[6] = 1;
    pfVar2 = DAT_0801e534;
    iVar37 = DAT_0801e530;
    if ((*DAT_0801e52c == '\x01') && (*(byte *)(DAT_0801e534 + 5) >> 1 == 0)) {
      if ((*(char *)(DAT_0801e530 + 0x1b) != '\0') || (*DAT_0801e538 != '\0')) {
        puVar18[7] = 0;
        goto LAB_0801e2a4;
      }
    }
    else {
      bVar30 = *(byte *)(DAT_0801e534 + 5) >> 1;
    }
    puVar18[7] = bVar30;
LAB_0801e2a4:
    puVar18[8] = 2;
    puVar18[9] = (char)((ushort)*(undefined2 *)(pfVar2 + 4) >> 8);
    puVar18[10] = (char)*(undefined2 *)(pfVar2 + 4);
    puVar18[0xb] = 3;
    fVar3 = DAT_0801e540;
    pfVar19 = DAT_0801e53c;
    fVar48 = (float)VectorUnsignedToFloat(pfVar2[1],(byte)(in_fpscr >> 0x16) & 3);
    iVar41 = VectorFloatToUnsigned(fVar48 * (*DAT_0801e53c + DAT_0801e540),3);
    iVar41 = iVar41 * 100;
    local_20._0_1_ = (byte)iVar41;
    local_20._1_1_ = (char)((uint)iVar41 >> 8);
    puVar18[0xc] = (char)((uint)iVar41 >> 0x18);
    puVar18[0xd] = (char)((uint)iVar41 >> 0x10);
    puVar18[0xe] = 4;
    puVar18[0xf] = local_20._1_1_;
    puVar18[0x10] = (byte)local_20;
    puVar18[0x11] = 5;
    uVar40 = VectorFloatToUnsigned(*pfVar2 * (*pfVar19 + fVar3),3);
    puVar18[0x12] = (char)((uint)uVar40 >> 0x18);
    puVar18[0x13] = (char)((uint)uVar40 >> 0x10);
    puVar18[0x14] = 6;
    puVar18[0x15] = (char)((uint)uVar40 >> 8);
    puVar18[0x16] = (char)uVar40;
    puVar18[0x17] = 7;
    if ((int)pfVar2[2] < 1) {
      local_20._0_1_ = 0;
      local_20._1_1_ = 0;
      uStack_1e = 0;
    }
    else {
      fVar48 = pfVar2[2];
      local_20._0_1_ = SUB41(fVar48,0);
      local_20._1_1_ = (char)((uint)fVar48 >> 8);
      uStack_1e = (undefined2)((uint)fVar48 >> 0x10);
    }
    fVar48 = (float)VectorUnsignedToFloat
                              (CONCAT22(uStack_1e,CONCAT11(local_20._1_1_,(byte)local_20)),
                               (byte)(in_fpscr >> 0x16) & 3);
    if (*pfVar2 < fVar48) {
      uVar40 = VectorFloatToUnsigned(*pfVar2,3);
      local_20._0_1_ = (byte)uVar40;
      local_20._1_1_ = (char)((uint)uVar40 >> 8);
      uStack_1e = (undefined2)((uint)uVar40 >> 0x10);
    }
    fVar48 = (float)VectorUnsignedToFloat
                              (CONCAT22(uStack_1e,CONCAT11(local_20._1_1_,(byte)local_20)),
                               (byte)((in_fpscr & 0xfffffff) >> 0x16) & 3);
    uVar40 = VectorFloatToUnsigned((*pfVar19 + fVar3) * fVar48,3);
    local_20._0_1_ = (byte)uVar40;
    local_20._1_1_ = (char)((uint)uVar40 >> 8);
    uStack_1e = (undefined2)((uint)uVar40 >> 0x10);
    puVar18[0x18] = (char)((uint)uVar40 >> 0x18);
    puVar18[0x19] = (char)((uint)uVar40 >> 0x10);
    puVar18[0x1a] = 8;
    puVar18[0x1b] = local_20._1_1_;
    puVar18[0x1c] = (byte)local_20;
    puVar18[0x1d] = 9;
    puVar20 = DAT_0801e544;
    puVar18[0x1e] = (char)((ushort)DAT_0801e544[1] >> 8);
    puVar18[0x1f] = (char)puVar20[1];
    puVar18[0x20] = 10;
    puVar18[0x21] = (char)((ushort)*puVar20 >> 8);
    puVar18[0x22] = (char)*puVar20;
    puVar18[0x23] = 0xb;
    puVar18[0x24] = (char)((ushort)puVar20[0x10] >> 8);
    puVar18[0x25] = (char)puVar20[0x10];
    puVar18[0x26] = (char)((ushort)puVar20[0x11] >> 8);
    puVar18[0x27] = (char)puVar20[0x11];
    if (*DAT_0801e548 == '\0') {
      puVar18[0x28] = 0;
      cStack_1b = cVar31;
      uStack_1a = uVar29;
      bStack_19 = bVar50;
    }
    else {
      cStack_1b = cVar31;
      uStack_1a = uVar29;
      bStack_19 = bVar50;
      FUN_0801806c();
      puVar18[0x28] = 0xc;
      puVar4 = DAT_0801e54c;
      puVar18[0x29] = *DAT_0801e54c;
      puVar18[0x2a] = puVar4[1];
      puVar18[0x2b] = puVar4[2];
      puVar18[0x2c] = puVar4[3];
      puVar18[0x2d] = puVar4[4];
      puVar18[0x2e] = puVar4[5];
    }
    uVar40 = VectorFloatToUnsigned(*(float *)(DAT_0801e550 + 0x114) * DAT_0801e554,3);
    puVar18[0x2f] = (char)((uint)uVar40 >> 8);
    puVar18[0x30] = (char)uVar40;
    fVar3 = DAT_0801e55c;
    uVar40 = VectorFloatToUnsigned(*(float *)(DAT_0801e558 + 0xc) * DAT_0801e55c,3);
    puVar18[0x31] = (char)((uint)uVar40 >> 8);
    puVar18[0x32] = (char)uVar40;
    uVar40 = VectorFloatToUnsigned(*(float *)(DAT_0801e560 + 0xc) * fVar3,3);
    local_20._0_1_ = (byte)uVar40;
    local_20._1_1_ = (char)((uint)uVar40 >> 8);
    uStack_1e = (undefined2)((uint)uVar40 >> 0x10);
    puVar18[0x33] = local_20._1_1_;
    puVar18[0x34] = (byte)local_20;
    puVar18[0x35] = 0xd;
    puVar18[0x36] = *DAT_0801e564;
    pcVar15 = DAT_0801e568;
    if (*DAT_0801e568 == '\x01') {
      uVar33 = 0xce;
    }
    else {
      uVar33 = 0x4e;
    }
    puVar18[0x37] = uVar33;
    puVar18[0x38] = *DAT_0801e56c;
    puVar18[0x39] = 0;
    puVar18[0x39] = puVar18[0x39] | 4;
    if (*pcVar15 == '\x01') {
      puVar18[0x39] = puVar18[0x39] + -0x80;
    }
    if (*DAT_0801e570 != '\0') {
      puVar18[0x39] = puVar18[0x39] + '@';
    }
    if (*(char *)(iVar37 + 0x4b) != '\0') {
      puVar18[0x39] = puVar18[0x39] + ' ';
    }
    if (*pcVar15 == '\x02') {
      puVar18[0x39] = puVar18[0x39] + '\x10';
    }
    puVar18[0x3a] = *DAT_0801e574;
    pbVar38 = (byte *)FUN_0801e980(DAT_0801e528);
    return pbVar38;
  default:
    goto switchD_0801cd98_caseD_5;
  case 6:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_080127e0(0x20,param_1 + 2,0x1b);
    FUN_08012330(0x20,DAT_0802206c,0x1b);
    uVar52 = ZEXT48(unaff_r4) & 0xffffffffffffff00;
    while( true ) {
      bVar30 = (byte)uVar52;
      if (0x1a < bVar30) {
        pbVar38 = (byte *)FUN_0801aa48(0xff);
        return pbVar38;
      }
      if ((param_1 + 2)[bVar30] != *(byte *)(DAT_0802206c + (uint)bVar30)) break;
      uVar52 = CONCAT71((int7)(uVar52 >> 8),bVar30 + 1);
    }
    return (byte *)uVar52;
  case 7:
    *DAT_0801aac4 = 0xea;
    puVar9[1] = 0xd1;
    puVar9[2] = 1;
    puVar9[3] = 0x1f;
    puVar9[4] = 0xff;
    puVar9[5] = 7;
    iVar37 = DAT_0801aac8;
    for (uVar45 = 0; uVar45 < 0x1b; uVar45 = (uint)(byte)((char)uVar45 + 1)) {
      puVar9[uVar45 + 6] = *(undefined1 *)(iVar37 + uVar45);
    }
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    pbVar38 = (byte *)FUN_0801e980(DAT_0801aac4);
    return pbVar38;
  case 8:
    local_2c._0_2_ = 0x10;
    local_28 = (uint)local_28._2_2_ << 0x10;
    local_20._0_1_ = 0;
    local_20._1_1_ = 0;
    local_24._1_1_ = uVar33;
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_0801ab24();
    puVar4 = DAT_0801c9e8;
    *DAT_0801c9e8 = 0xea;
    puVar4[1] = 0xd1;
    puVar4[2] = 1;
    puVar4[3] = 0x25;
    puVar4[4] = 0xff;
    puVar4[5] = 8;
    if (*DAT_0801c9ec == '\0') {
      if (*DAT_0801ca00 == 0x20) {
        local_30 = 0x7f - *DAT_0801c9f0;
        local_24 = 0x70 - *DAT_0801c9f0;
      }
      if (*DAT_0801ca00 == 0x80) {
        local_30 = -(*DAT_0801c9f0 + -0x1ff);
        local_24 = 0x1f0 - *DAT_0801c9f0;
      }
      if (*DAT_0801ca00 == 0x100) {
        local_30 = -(*DAT_0801c9f0 + -0x3ff);
        local_24 = 0x3f0 - *DAT_0801c9f0;
      }
      if (*DAT_0801ca00 == 0x200) {
        local_30 = -(*DAT_0801c9f0 + -0x7ff);
        local_24 = 0x7f0 - *DAT_0801c9f0;
      }
      if (*DAT_0801ca00 == 0x400) {
        local_30 = -(*DAT_0801c9f0 + -0xfff);
        local_24 = 0xff0 - *DAT_0801c9f0;
      }
    }
    else if (*DAT_0801c9f4 == 0x200) {
      if (DAT_0801c9fc < *DAT_0801c9f8) {
        local_30 = 0x208d - *DAT_0801c9f0;
        sVar34 = *DAT_0801c9f0;
        sVar43 = 0x207e;
      }
      else {
        local_30 = 0x2b8d - *DAT_0801c9f0;
        sVar34 = *DAT_0801c9f0;
        sVar43 = 0x2b7e;
      }
      local_24 = sVar43 - sVar34;
    }
    else if ((*DAT_0801c9f4 == 0x100) && (*DAT_0801c9f8 <= DAT_0801c9fc)) {
      local_30 = -(*DAT_0801c9f0 + -0xb8d);
      local_24 = -(*DAT_0801c9f0 + -0xb7e);
    }
    else {
      local_30 = 0x8d - *DAT_0801c9f0;
      local_24 = 0x7e - *DAT_0801c9f0;
    }
    puVar4[6] = 0;
    uVar35 = FUN_08018768(0x1c0);
    local_2c = CONCAT22(local_2c._2_2_,uVar35);
    if (uVar35 != 0xffff) {
      if ((local_30 < uVar35) || (uVar35 < 0x10)) {
        local_2c = CONCAT22(local_2c._2_2_,0x10);
      }
      uVar35 = FUN_08018768(0x1c2);
      iVar37 = DAT_0801ca04;
      if (local_24 < uVar35) {
        uVar35 = local_24;
      }
      local_28 = CONCAT22(local_28._2_2_,uVar35);
      if (uVar35 < local_24) {
        for (local_28 = 0x10; local_28 <= (local_2c & 0xffff); local_28 = local_28 + 1) {
          puVar4[6] = (char)local_28 + -0xf;
          FUN_08012330(local_28 << 5,puVar4 + 7,0x20);
          FUN_0801e980(DAT_0801c9e8);
          do {
          } while (*(short *)(*(int *)(iVar37 + 0x1c) + 0x25a) != 0);
          FUN_0800db18(7);
          local_20 = local_20 + 1;
          if (local_24 < local_20) break;
        }
      }
      else if (uVar35 == local_24) {
        local_28 = local_2c & 0xffff;
        do {
          local_28 = local_28 + 1;
          if (local_30 < local_28) break;
          puVar4[6] = ((char)local_28 - (char)local_2c) + -1;
          FUN_08012330(local_28 * 0x20,puVar4 + 7,0x20);
          FUN_0801e980(DAT_0801c9e8);
          do {
          } while (*(short *)(*(int *)(iVar37 + 0x1c) + 0x25a) != 0);
          FUN_0800db18(7);
          local_20 = local_20 + 1;
        } while (local_20 <= local_24);
        for (local_28 = 0x10; local_28 <= (local_2c & 0xffff); local_28 = local_28 + 1) {
          puVar4[6] = ((char)local_30 - (char)local_2c) + (char)local_28 + -0x10;
          FUN_08012330(local_28 << 5,puVar4 + 7,0x20);
          FUN_0801e980(DAT_0801c9e8);
          do {
          } while (*(short *)(*(int *)(iVar37 + 0x1c) + 0x25a) != 0);
          FUN_0800db18(7);
          local_20 = local_20 + 1;
          if (local_24 < local_20) break;
        }
      }
      FUN_0800db18(10);
    }
    pbVar38 = (byte *)FUN_0801aa48(0xff,0xfe);
    return pbVar38;
  case 9:
    for (uVar35 = 0; uVar35 < 0x20; uVar35 = uVar35 + 1) {
      *(undefined1 *)(iVar37 + (uint)uVar35) = 0xff;
    }
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_080127e0(0x1c0,DAT_0800c2f0,0x20);
    FUN_080127e0(0x1e0,DAT_0800c2f0,0x20);
    pbVar38 = (byte *)FUN_0801aa48(0xff);
    return pbVar38;
  case 10:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_080127e0(0x120,param_1 + 2,0x14);
    FUN_08012330(0x120,DAT_080220d4,0x14);
    uVar52 = CONCAT44(0x14,unaff_r4) & 0xffffffffffffff00;
    while( true ) {
      bVar30 = (byte)uVar52;
      if ((byte)(uVar52 >> 0x20) <= bVar30) {
        pbVar38 = (byte *)FUN_0801aa48(0xff);
        return pbVar38;
      }
      pbVar38 = (byte *)(uint)(param_1 + 2)[bVar30];
      if (pbVar38 != (byte *)(uint)*(byte *)(DAT_080220d4 + (uint)bVar30)) break;
      uVar52 = CONCAT71((int7)(uVar52 >> 8),bVar30 + 1);
    }
    return pbVar38;
  case 0xb:
    *DAT_0801ab1c = 0xea;
    puVar10[1] = 0xd1;
    puVar10[2] = 1;
    puVar10[3] = 0x18;
    puVar10[4] = 0xff;
    puVar10[5] = 0xb;
    puVar10[6] = 0;
    iVar37 = DAT_0801ab20;
    for (uVar45 = 0; uVar45 < 0x14; uVar45 = (uint)(byte)((char)uVar45 + 1)) {
      puVar10[uVar45 + 6] = *(undefined1 *)(iVar37 + uVar45);
    }
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    pbVar38 = (byte *)FUN_0801e980(DAT_0801ab1c);
    return pbVar38;
  case 0xc:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_080127e0(0x140,param_1 + 2,0x18);
    FUN_08012330(0x140,DAT_08021b50,0x18);
    local_1c = FUN_0800ba48(DAT_08021b50,0x18);
    FUN_080127e0(0x15d,&local_1c,1);
    iVar37 = FUN_08018354(0x15d);
    iVar41 = FUN_0800ba48(DAT_08021b50,0x18);
    if (iVar37 == iVar41) {
      local_20._0_1_ = 0;
      while( true ) {
        if (0x17 < (byte)local_20) {
          FUN_08012a74();
          FUN_08019844(0,0xc);
          FUN_0801aa48(0xff);
          return (byte *)CONCAT22(uStack_1e,CONCAT11(local_20._1_1_,(byte)local_20));
        }
        if ((param_1 + 2)[(byte)local_20] != *(byte *)(DAT_08021b50 + (uint)(byte)local_20)) break;
        local_20._0_1_ = (byte)local_20 + 1;
      }
      local_1c = 0;
      FUN_080127e0(0x15d,&local_1c,1);
    }
    return (byte *)CONCAT22(uStack_1e,CONCAT11(local_20._1_1_,(byte)local_20));
  case 0xd:
    *DAT_0801a304 = 0xea;
    puVar5[1] = 0xd1;
    puVar5[2] = 1;
    puVar5[3] = 0x1c;
    puVar5[4] = 0xff;
    puVar5[5] = 0xd;
    puVar5[6] = 0;
    iVar37 = DAT_0801a308;
    for (uVar45 = 0; uVar45 < 0x18; uVar45 = (uint)(byte)((char)uVar45 + 1)) {
      puVar5[uVar45 + 6] = *(undefined1 *)(iVar37 + uVar45);
    }
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    pbVar38 = (byte *)FUN_0801e980(DAT_0801a304);
    return pbVar38;
  case 0xe:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_080127e0(0x48,param_1 + 2,1);
    FUN_08012330(0x48,abStack_34 + 0x1c,1);
    if ((byte)unaff_r4 == param_1[2]) {
      *DAT_08021e4c = 0xfe;
      FUN_080136a4();
      FUN_0801aa48(0xff);
    }
    return unaff_r4;
  case 0xf:
    pbVar38 = (byte *)(uint)param_1[2];
    switch(pbVar38) {
    case (byte *)0x0:
      bVar47 = true;
      break;
    case (byte *)0x1:
      local_1c = 0xf;
      cStack_1b = 0;
      uStack_1a = 0;
      bStack_19 = 0;
      uStack_22 = (undefined1)((ulonglong)unaff_d8 >> 0x10);
      uStack_21 = (undefined1)((ulonglong)unaff_d8 >> 0x18);
      uStack_1e = (undefined2)((ulonglong)unaff_d8 >> 0x30);
      local_2c._1_3_ = (undefined3)(local_2c >> 8);
      *DAT_0801e96c = 0xea;
      puVar24[1] = 0xd1;
      puVar24[2] = 1;
      puVar24[3] = 0x36;
      puVar24[4] = 0xff;
      puVar24[5] = 0xf;
      puVar24[6] = 1;
      pbVar38 = DAT_0801e970;
      if (*DAT_0801e970 < 0x10) {
        local_2c._0_1_ = *DAT_0801e970;
      }
      else {
        local_2c._0_1_ = 0x10;
      }
      puVar24[3] = (byte)local_2c * '\x03' + '\x06';
      puVar24[7] = (byte)local_2c;
      fVar3 = DAT_0801e978;
      iVar37 = DAT_0801e974;
      for (local_30._0_1_ = 0; (byte)local_30 < (byte)local_2c; local_30._0_1_ = (byte)local_30 + 1)
      {
        uVar40 = VectorFloatToUnsigned(*(float *)(iVar37 + (uint)(byte)local_30 * 4 + 4) * fVar3,3);
        local_28 = CONCAT22(local_28._2_2_,(short)uVar40);
        puVar24[(uint)(byte)local_30 * 3 + 8] = (byte)local_30 + 1;
        puVar24[(uint)(byte)local_30 * 3 + 10] = (char)((uint)uVar40 >> 8);
        puVar24[(uint)(byte)local_30 * 3 + 9] = (char)uVar40;
      }
      puVar24[5] = 0xf;
      puVar24[6] = 1;
      local_24._0_1_ = (byte)local_20;
      local_24._1_1_ = local_20._1_1_;
      local_20._0_1_ = bVar30;
      local_20._1_1_ = cVar31;
      FUN_0801e980(DAT_0801e96c);
      piVar25 = DAT_0801e97c;
      pbVar39 = (byte *)(uint)*pbVar38;
      if ((pbVar39 <= &MemManage) || (pbVar39 = (byte *)(uint)*pbVar38, pbVar39 <= &MemManage)) {
        return pbVar39;
      }
      local_2c = CONCAT31(local_2c._1_3_,*pbVar38 - 0x10);
      while (*(short *)(*piVar25 + 0x25a) != 0) {
        FUN_0800db18(1);
      }
      FUN_0800db18(0x32);
      puVar24[3] = (byte)local_2c * '\x03' + '\x06';
      puVar24[7] = (byte)local_2c;
      for (local_30._0_1_ = 0; (byte)local_30 < (byte)local_2c; local_30._0_1_ = (byte)local_30 + 1)
      {
        uVar40 = VectorFloatToUnsigned
                           (*(float *)(iVar37 + (uint)(byte)local_30 * 4 + 0x44) * fVar3,3);
        local_28 = CONCAT22(local_28._2_2_,(short)uVar40);
        puVar24[(uint)(byte)local_30 * 3 + 8] = (byte)local_30 + 0x11;
        puVar24[(uint)(byte)local_30 * 3 + 10] = (char)((uint)uVar40 >> 8);
        puVar24[(uint)(byte)local_30 * 3 + 9] = (char)uVar40;
      }
      pbVar38 = (byte *)FUN_0801e980(DAT_0801e96c,(byte)local_2c,
                                     CONCAT13(bStack_19,
                                              CONCAT12(uStack_1a,CONCAT11(cStack_1b,local_1c))),1);
      return pbVar38;
    case (byte *)0x2:
      pbVar38 = param_1 + 3;
      local_1c = *pbVar38;
      for (local_20._0_1_ = 0; pbVar39 = DAT_08022e78, (byte)local_20 < *pbVar38;
          local_20._0_1_ = (byte)local_20 + 1) {
        *(byte *)(iVar28 + (uint)(byte)local_20 * 2) = pbVar38[(uint)(byte)local_20 * 3 + 2];
        *(byte *)(iVar28 + (uint)(byte)local_20 * 2 + 1) = pbVar38[(uint)(byte)local_20 * 3 + 3];
      }
      iVar37 = DAT_08022e74 + -0x20;
      if (param_1[4] < 0x11) {
        local_20._1_1_ = local_24._1_1_;
        FUN_080127e0(0x60,DAT_08022e74,(uint)*pbVar38 << 1);
        FUN_08012330(0x60,iVar37,(uint)*pbVar38 << 1);
        for (local_20._0_1_ = 0; (uint)(byte)local_20 < (uint)*pbVar38 << 1;
            local_20._0_1_ = (byte)local_20 + 1) {
          if (*(char *)(iVar28 + (uint)(byte)local_20) != *(char *)(iVar37 + (uint)(byte)local_20))
          {
            return (byte *)0x0;
          }
        }
        if (*pbVar38 != *pbVar39) {
          FUN_0801aa48(0xff);
          return (byte *)0x1;
        }
      }
      else {
        if (*DAT_08022e78 < 0x11) {
          return (byte *)0x1;
        }
        if (param_1[4] != 0x11) {
          return (byte *)0x1;
        }
        local_20._1_1_ = local_24._1_1_;
        FUN_080127e0(0x80,DAT_08022e74,(*DAT_08022e78 - 0x10) * 2);
        FUN_08012330(0x80,DAT_08022e74 + -0x20,(*pbVar39 - 0x10) * 2);
        for (local_20._0_1_ = 0; (uint)(byte)local_20 < (uint)local_1c << 1;
            local_20._0_1_ = (byte)local_20 + 1) {
          if (*(char *)(iVar28 + (uint)(byte)local_20) != *(char *)(iVar37 + (uint)(byte)local_20))
          {
            return (byte *)0x0;
          }
        }
      }
      FUN_0801aa48(0xff);
      FUN_0800db18(10);
      FUN_08017b3c();
      FUN_08016000();
      FUN_08009144();
      FUN_08013448();
      FUN_08019844(0,0xf);
      FUN_0800c940();
      FUN_0800acd8();
      return (byte *)0x1;
    case (byte *)0x3:
      local_1c = 0;
      cStack_1b = 0;
      uStack_1e = uVar36;
      uStack_1a = uVar29;
      bStack_19 = bVar50;
      iVar37 = FUN_08009c48(DAT_0800c3f4 + 1,1);
      fVar48 = DAT_0800c3fc;
      fVar3 = DAT_0800c3f8;
      if (iVar37 != 0) {
        if (0.0 <= pfVar2[1]) {
          uVar40 = VectorFloatToUnsigned(pfVar2[1] * DAT_0800c3fc,3);
          sVar34 = (short)uVar40;
        }
        else {
          uVar40 = VectorFloatToUnsigned(pfVar2[1] * DAT_0800c3f8,3);
          sVar34 = ~(ushort)uVar40 + 1;
        }
        local_20._0_1_ = (byte)sVar34;
        local_20._1_1_ = (char)((ushort)sVar34 >> 8);
        if (sVar34 == -1) {
          local_20._0_1_ = 0;
          local_20._1_1_ = 0;
        }
        iVar37 = FUN_08021fae(0x42,CONCAT11(local_20._1_1_,(byte)local_20));
        if ((iVar37 != 0) && (iVar37 = FUN_08009c48(DAT_0800c3f4,2), iVar37 != 0)) {
          if (0.0 <= *pfVar2) {
            uVar40 = VectorFloatToUnsigned(*pfVar2 * fVar48,3);
            sVar34 = (short)uVar40;
          }
          else {
            uVar40 = VectorFloatToUnsigned(*pfVar2 * fVar3,3);
            sVar34 = ~(ushort)uVar40 + 1;
          }
          local_20._0_1_ = (byte)sVar34;
          local_20._1_1_ = (char)((ushort)sVar34 >> 8);
          if (sVar34 == -1) {
            local_20._0_1_ = 0;
            local_20._1_1_ = 0;
          }
          iVar37 = FUN_08021fae(0x40,CONCAT11(local_20._1_1_,(byte)local_20));
          if (iVar37 != 0) {
            FUN_08019844(0,0x59);
            FUN_0801aa48(0xff);
          }
          FUN_08013448();
          FUN_0800c940();
          pbVar38 = (byte *)FUN_0800acd8();
          return pbVar38;
        }
      }
      return (byte *)0x0;
    case (byte *)0x4:
      *DAT_0801e248 = 0xea;
      puVar17[1] = 0xd1;
      puVar17[2] = 1;
      puVar17[3] = 9;
      puVar17[4] = 0xff;
      puVar17[5] = 0xf;
      puVar17[6] = 4;
      fVar3 = DAT_0801e250;
      iVar37 = DAT_0801e24c;
      uVar40 = VectorFloatToUnsigned(*(float *)(DAT_0801e24c + 8) * DAT_0801e250,3);
      puVar17[7] = (char)((uint)uVar40 >> 8);
      puVar17[8] = (char)uVar40;
      uVar40 = VectorFloatToUnsigned(*(float *)(iVar37 + 0xc) * fVar3,3);
      puVar17[9] = (char)((uint)uVar40 >> 8);
      puVar17[10] = (char)uVar40;
      uStack_1e = uVar36;
      cStack_1b = cVar31;
      uStack_1a = uVar29;
      bStack_19 = bVar50;
      pbVar38 = (byte *)FUN_0801e980();
      return pbVar38;
    case (byte *)0x5:
      pbVar38 = (byte *)(uint)param_1[3];
      if (pbVar38 == (byte *)0x1) {
        uStack_1e = uVar36;
        cStack_1b = cVar31;
        uStack_1a = uVar29;
        bStack_19 = bVar50;
        iVar37 = FUN_08021fae(0x44,CONCAT11(param_1[4],param_1[5]));
        if (iVar37 != 0) {
          FUN_0801aa48(0xff);
        }
        uVar40 = 0xe;
      }
      else {
        if (pbVar38 != &Reset) {
          return pbVar38;
        }
        uStack_1e = uVar36;
        cStack_1b = cVar31;
        uStack_1a = uVar29;
        bStack_19 = bVar50;
        iVar37 = FUN_08021fae(0x4a,CONCAT11(param_1[4],param_1[5]));
        if (iVar37 != 0) {
          FUN_0801aa48(0xff);
        }
        uVar40 = 0xd;
      }
      FUN_08019844(0,uVar40);
      pbVar38 = (byte *)FUN_08013448();
      return pbVar38;
    case (byte *)0x6:
      if (param_1[3] == 1) {
        uVar40 = VectorUnsignedToFloat
                           ((uint)param_1[7] + (uint)param_1[4] * 0x1000000 +
                            (uint)param_1[5] * 0x10000 + (uint)param_1[6] * 0x100,
                            (byte)(in_fpscr >> 0x16) & 3);
        *DAT_0802239c = uVar40;
      }
      if (param_1[8] == 2) {
        puVar26[2] = (uint)param_1[0xc] + (uint)param_1[9] * 0x1000000 +
                     (uint)param_1[10] * 0x10000 + (uint)param_1[0xb] * 0x100;
      }
      uStack_1e = uVar36;
      cStack_1b = cVar31;
      uStack_1a = uVar29;
      bStack_19 = bVar50;
      FUN_0801975c();
      FUN_0800b460();
      FUN_08019844(0,0x5d);
      pbVar38 = (byte *)FUN_0801aa48(0xff);
      return pbVar38;
    case (byte *)0x7:
      uStack_1e = uVar36;
      cStack_1b = cVar31;
      uStack_1a = uVar29;
      bStack_19 = bVar50;
      if (*DAT_08022b3c != '\0') {
        param_4 = (uint)param_1[8];
        uVar46 = (uint)param_1[7];
        FUN_08018198(param_1[3],param_1[4],param_1[5],param_1[6]);
        FUN_0801806c();
      }
      pbVar38 = (byte *)FUN_0801aa48(0xff,0xff,uVar46,param_4);
      return pbVar38;
    case (byte *)0x8:
      if (param_1[3] == 3) {
        *(uint *)(DAT_08021ea8 + 4) =
             ((uint)param_1[7] + (uint)param_1[4] * 0x1000000 +
             (uint)param_1[5] * 0x10000 + (uint)param_1[6] * 0x100) / 100;
      }
      uStack_1e = uVar36;
      cStack_1b = cVar31;
      uStack_1a = uVar29;
      bStack_19 = bVar50;
      FUN_0801975c();
      FUN_0800b460();
      FUN_08019844(0,0x5c);
      pbVar38 = (byte *)FUN_0801aa48(0xff);
      return pbVar38;
    default:
      goto switchD_0801cd98_caseD_5;
    }
LAB_0801d09e:
    *DAT_0801e7a8 = 0xea;
    puVar23[1] = 0xd1;
    puVar23[2] = 1;
    pbVar38 = DAT_0801e7ac;
    puVar23[3] = *DAT_0801e7ac * '\x02' + '\a';
    puVar23[4] = 0xff;
    puVar23[5] = 2;
    puVar23[6] = *pbVar38;
    puVar23[7] = *DAT_0801e7b0 + *DAT_0801e7b4 + *DAT_0801e7b8;
    puVar23[8] = *pbVar38;
    fVar48 = DAT_0801e7c0;
    fVar3 = DAT_0801e7bc;
    for (uVar35 = 0; uVar35 < *pbVar38; uVar35 = uVar35 + 1) {
      if (bVar47) {
        fVar49 = *(float *)(DAT_0801e7c4 + (uint)uVar35 * 4 + 4);
      }
      else {
        fVar49 = *(float *)(DAT_0801e7c8 + (uint)uVar35 * 4 + 0x80);
      }
      uVar40 = VectorFloatToUnsigned((fVar49 + fVar3) * fVar48,3);
      puVar23[(uint)uVar35 * 2 + 9] = (char)((uint)uVar40 >> 8);
      puVar23[(uint)uVar35 * 2 + 10] = (char)uVar40;
    }
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    pbVar38 = (byte *)FUN_0801e980(DAT_0801e7a8);
    return pbVar38;
  case 0x10:
    bVar30 = param_1[2] + 1;
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_080127e0(0xe0,param_1 + 2,bVar30);
    FUN_08012330(0xe0,DAT_08022544,bVar30);
    uVar52 = ZEXT48(unaff_r4) & 0xffffffffffffff00;
    while( true ) {
      bVar50 = (byte)uVar52;
      if (bVar30 <= bVar50) {
        pbVar38 = (byte *)FUN_0801aa48(0xff);
        return pbVar38;
      }
      if ((param_1 + 2)[bVar50] != *(byte *)(DAT_08022544 + (uint)bVar50)) break;
      uVar52 = CONCAT71((int7)(uVar52 >> 8),bVar50 + 1);
    }
    return (byte *)uVar52;
  case 0x11:
    *DAT_0801b3f4 = 0xea;
    puVar11[1] = 0xd1;
    puVar11[2] = 1;
    puVar11[3] = 0;
    puVar11[4] = 0xff;
    puVar11[5] = 0x11;
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_08012330(0xe0,puVar11 + 3,1);
    if ((byte)puVar11[3] < 0x20) {
      puVar11[3] = puVar11[3] + '\x05';
      FUN_08012330(0xe0,puVar11 + 6,(byte)puVar11[3] - 4);
    }
    else {
      puVar11[3] = 5;
    }
    pbVar38 = (byte *)FUN_0801e980(DAT_0801b3f4);
    return pbVar38;
  case 0x12:
    cVar32 = param_1[2] + 4;
    param_1 = param_1 + 2;
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_080127e0(0x162,param_1,cVar32);
    FUN_08012330(0x162,DAT_080225ac,cVar32);
    lVar51 = (ulonglong)(uint)(CONCAT14(cVar32,unaff_r4) >> 8) << 8;
    while( true ) {
      bVar30 = (byte)lVar51;
      if ((byte)((ulonglong)lVar51 >> 0x20) <= bVar30) {
        uVar40 = FUN_0801aa48(0xff);
        pbVar38 = (byte *)FUN_080159fc(uVar40,(int)lVar51,(int)((ulonglong)lVar51 >> 0x20),param_1);
        return pbVar38;
      }
      if ((byte *)(uint)param_1[bVar30] != (byte *)(uint)*(byte *)(DAT_080225ac + (uint)bVar30))
      break;
      lVar51 = CONCAT71((int7)((ulonglong)lVar51 >> 8),bVar30 + 1);
    }
    return (byte *)(uint)param_1[bVar30];
  case 0x13:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_0801aa48(0xff);
    FUN_0800db18(0x32);
    FUN_08019844(0,2);
    FUN_080196d0(0x1e8);
    if (*DAT_0801d580 == '\x01') {
      pbVar38 = (byte *)FUN_08009e18();
      return pbVar38;
    }
    pbVar38 = (byte *)FUN_08016e44();
    return pbVar38;
  case 0x14:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_0801aa48(0xff);
    FUN_0800db18(200);
    FUN_08009902();
    FUN_0800b2d8();
    FUN_0800db18(0xf);
    uVar36 = FUN_0800d5cc();
    *DAT_0801d584 = uVar36;
    pbVar38 = DAT_0801d588;
    DAT_0801d588[0x3d] = 1;
    return pbVar38;
  case 0x15:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_0800b3ac();
    goto LAB_0801d3fe;
  case 0x16:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_0800b2a8();
    goto LAB_0801d3fe;
  case 0x17:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_0800b2c0();
    break;
  case 0x18:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_0800b2cc();
    break;
  case 0x19:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_0800b28c();
    goto LAB_0801d57c;
  case 0x1a:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_0800b260();
    goto LAB_0801d57c;
  case 0x1b:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_0800b158();
    goto LAB_0801d57c;
  case 0x1c:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_0800b12c();
    goto LAB_0801d57c;
  case 0x1d:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_0800b210();
    break;
  case 0x1e:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_0800b1dc();
    break;
  case 0x1f:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_0800b3cc();
    break;
  case 0x20:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_0800b174();
    break;
  case 0x21:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_0800b404();
    break;
  case 0x22:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_0800b1a4();
    break;
  case 0x23:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_0800b430();
    break;
  case 0x24:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_0800b1d0();
    break;
  case 0x26:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_08022e7c(0xac,0xffff);
    FUN_0800db18(100);
    pbVar38 = (byte *)FUN_08018768(0xac);
    bVar47 = pbVar38 == (byte *)0xffff;
    goto LAB_0801d282;
  case 0x27:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_080127e0(0x4e,param_1 + 2,0x10);
    FUN_08012330(0x4e,DAT_08022b08,0x10);
    FUN_0800ba48(DAT_08022b08,0x10);
    FUN_080127e0(0x5e,abStack_34 + 0x20,1);
    pbVar38 = (byte *)FUN_08018354(0x5e);
    pbVar39 = (byte *)FUN_0800ba48(DAT_08022b08,0x10);
    if (pbVar38 == pbVar39) {
      bVar30 = 0;
      while( true ) {
        if (0xf < bVar30) {
          FUN_08022b0c();
          pbVar38 = (byte *)FUN_0801aa48(0xff);
          return pbVar38;
        }
        if ((param_1 + 2)[bVar30] != *(byte *)(DAT_08022b08 + (uint)bVar30)) break;
        bVar30 = bVar30 + 1;
      }
      pbVar39 = (byte *)FUN_080127e0(0x5e,abStack_34 + 0x20,1);
    }
    return pbVar39;
  case 0x28:
    *DAT_0801e5bc = 0xea;
    puVar21[1] = 0xd1;
    puVar21[2] = 1;
    puVar21[3] = 0x1a;
    puVar21[4] = 0xff;
    puVar21[5] = 0x28;
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_08012330(0x4e,puVar21 + 6,0x10);
    puVar21[0x18] = 0;
    puVar21[0x19] = 0;
    puVar21[0x1a] = 0;
    puVar21[0x1b] = 0;
    FUN_0801e5c0(puVar21 + 0x16);
    pbVar38 = (byte *)FUN_0801e980(puVar21);
    return pbVar38;
  case 0x29:
    *DAT_0801d58c = 0x55;
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_0800f4c8();
    FUN_0800f49c();
    break;
  case 0x30:
    *DAT_0801b44c = 0xea;
    puVar12[1] = 0xd1;
    puVar12[2] = 1;
    puVar12[3] = 0;
    puVar12[4] = 0xff;
    puVar12[5] = 0x13;
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_08012330(0x162,puVar12 + 3,1);
    if ((byte)puVar12[3] < 0x1d) {
      puVar12[3] = puVar12[3] + '\b';
      FUN_08012330(0x162,puVar12 + 6,(byte)puVar12[3] - 4);
    }
    else {
      puVar12[3] = 5;
    }
    pbVar38 = (byte *)FUN_0801e980(DAT_0801b44c);
    return pbVar38;
  case 0x31:
    DAT_0801d174[5] = 2;
    iVar37 = puVar13[1] * 0x78;
    goto LAB_0801d2e2;
  case 0x32:
    DAT_0801d174[5] = 1;
    iVar37 = puVar13[1] * 100;
LAB_0801d2e2:
    uVar40 = VectorUnsignedToFloat(iVar37,(byte)(in_fpscr >> 0x16) & 3);
    *puVar13 = uVar40;
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    break;
  case 0x33:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_08021b54(0x104);
    FUN_08021b54(0x105);
    *param_1 = 0xff;
    param_1[1] = 0xff;
    param_1[2] = 0xff;
    param_1[3] = 0xff;
    param_1[4] = 0xff;
    FUN_080127e0(0x15b,param_1,5);
    break;
  case 0x5f:
    pbVar38 = (byte *)(uint)param_1[2];
    bVar47 = false;
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    if (pbVar38 == (byte *)0xf5) {
      pbVar38 = (byte *)FUN_08017b3c();
      return pbVar38;
    }
LAB_0801d282:
    if (!bVar47) {
switchD_0801cd98_caseD_5:
      return pbVar38;
    }
    *(undefined2 *)(puVar13 + 4) = 0;
    FUN_080225b0(0xa8,0xffffffff);
    puVar13[3] = 0;
    goto LAB_0801d3fe;
  case 0x60:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_080127e0(0xb4,param_1 + 2,2);
    uVar40 = FUN_08018768(0xb4);
    uVar40 = VectorUnsignedToFloat(uVar40,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(iVar41 + 0x28) = uVar40;
    *(float *)(iVar41 + 0x28) = *(float *)(iVar41 + 0x28) / fVar3;
    goto LAB_0801d3fe;
  case 0x61:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_080127e0(2,param_1 + 2);
    uVar40 = FUN_08018768(2);
    uVar40 = VectorUnsignedToFloat(uVar40,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(iVar41 + 0x2c) = uVar40;
    *(float *)(iVar41 + 0x2c) = *(float *)(iVar41 + 0x2c) / fVar3;
    goto LAB_0801d3fe;
  case 0x62:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_080127e0(6,param_1 + 2,2);
    uVar40 = FUN_08018768(6);
    uVar40 = VectorUnsignedToFloat(uVar40,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(iVar41 + 0x30) = uVar40;
    *(float *)(iVar41 + 0x30) = *(float *)(iVar41 + 0x30) / fVar48;
    goto LAB_0801d3fe;
  case 99:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_080127e0(8,param_1 + 2,2);
    uVar40 = FUN_08018768(8);
    uVar40 = VectorUnsignedToFloat(uVar40,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(iVar41 + 0x34) = uVar40;
    *(float *)(iVar41 + 0x34) = *(float *)(iVar41 + 0x34) / fVar48;
    goto LAB_0801d3fe;
  case 100:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_080127e0(4,param_1 + 2,2);
    uVar40 = FUN_08018768(4);
    uVar40 = VectorUnsignedToFloat(uVar40,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(iVar41 + 0x38) = uVar40;
    *(float *)(iVar41 + 0x38) = *(float *)(iVar41 + 0x38) / fVar48;
    goto LAB_0801d3fe;
  case 0x6d:
    local_20._0_1_ = (byte)uVar46;
    local_1c = 0;
    local_20._1_1_ = local_24._1_1_;
    FUN_080127e0(0xb4,param_1 + 2,0xb);
    FUN_08012330(0xb4,DAT_08022448,0xb);
    local_1c = FUN_0800ba48(DAT_08022448,0xb);
    FUN_080127e0(0x15c,&local_1c,1);
    pbVar38 = (byte *)FUN_08018354(0x15c);
    pbVar39 = (byte *)FUN_0800ba48(DAT_08022448,0xb);
    if (pbVar38 == pbVar39) {
      for (local_20._0_1_ = 0; (byte)local_20 < 10; local_20._0_1_ = (byte)local_20 + 1) {
        if ((param_1 + 2)[(byte)local_20] != *(byte *)(DAT_08022448 + (uint)(byte)local_20)) {
          local_1c = 0;
          pbVar38 = (byte *)FUN_080127e0(0x15c,&local_1c,1);
          return pbVar38;
        }
      }
      FUN_0801aa48(0xff);
      FUN_08014824();
      FUN_0800db18(100);
      pbVar39 = (byte *)*DAT_0802244c;
      *pbVar39 = 0;
      pbVar39[1] = 0;
    }
    return pbVar39;
  case 0x6e:
    *DAT_0801e6d8 = 0xea;
    puVar22[1] = 0xd1;
    puVar22[2] = 1;
    puVar22[3] = 0xf;
    puVar22[4] = 0xff;
    puVar22[5] = 0x6e;
    iVar37 = DAT_0801e6dc;
    for (uVar45 = 0; uVar45 < 0xb; uVar45 = (uint)(byte)((char)uVar45 + 1)) {
      puVar22[uVar45 + 6] = *(undefined1 *)(iVar37 + uVar45);
    }
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    pbVar38 = (byte *)FUN_0801e980(DAT_0801e6d8);
    return pbVar38;
  case 0x6f:
    pbVar39 = param_1 + 2;
    cStack_1b = (char)((uint)unaff_r4 >> 8);
    uStack_1a = (undefined1)((uint)unaff_r4 >> 0x10);
    bStack_19 = (byte)((uint)unaff_r4 >> 0x18);
    uStack_22 = (undefined1)(uVar46 >> 0x10);
    uStack_21 = (undefined1)(uVar46 >> 0x18);
    local_24._0_1_ = 0;
    local_20._1_1_ = (char)((uint)DAT_0802223c >> 8);
    uStack_1e = (undefined2)((uint)DAT_0802223c >> 0x10);
    local_20._0_1_ = 0;
    local_28 = uVar45;
    local_1c = (byte)unaff_r4;
    FUN_080127e0(0x134,pbVar39,10);
    FUN_08012330(0x120,DAT_08022240,0x1e);
    local_24._0_1_ = FUN_0800ba48(DAT_08022240,0x1e);
    FUN_080127e0(0x15e,&local_24,1);
    pbVar42 = (byte *)FUN_08018354(0x15e);
    pbVar38 = (byte *)FUN_0800ba48(DAT_08022240,0x1e);
    iVar37 = DAT_08022240;
    if (pbVar42 == pbVar38) {
      local_28 = local_28 & 0xffffff00;
      while ((byte)local_28 < 10) {
        if (pbVar39[local_28 & 0xff] != *(byte *)((local_28 & 0xff) + DAT_08022240 + 0x14)) {
          uVar40 = 0x15e;
          goto LAB_080221da;
        }
        local_28 = CONCAT31(local_28._1_3_,(byte)local_28 + 1);
      }
      FUN_080127e0(0x3b,param_1 + 0xc,5);
      FUN_08012330(0x20,DAT_08022240);
      local_24._0_1_ = FUN_0800ba48(DAT_08022240,0x20);
      FUN_080127e0(0x15f,&local_24,1);
      pbVar42 = (byte *)FUN_08018354(0x15f);
      pbVar38 = (byte *)FUN_0800ba48(DAT_08022240,0x20);
      if (pbVar42 == pbVar38) {
        local_28 = local_28 & 0xffffff00;
        while ((local_28 & 0xff) < 5) {
          if (pbVar39[(local_28 & 0xff) + 10] != *(byte *)((local_28 & 0xff) + iVar37 + 0x1b)) {
            uVar40 = 0x15f;
LAB_080221da:
            local_24._0_1_ = 0;
            pbVar38 = (byte *)FUN_080127e0(uVar40,&local_24,1);
            return pbVar38;
          }
          local_28 = CONCAT31(local_28._1_3_,(byte)local_28 + '\x01');
        }
        FUN_0801301c();
        FUN_080141cc();
        if (*DAT_08022244 == '\x01') {
          FUN_0800d5fc();
          if (DAT_0802224c < *DAT_08022248) {
            *DAT_08022250 = 1;
          }
          else {
            *DAT_08022250 = 0;
          }
        }
        iVar37 = FUN_08009934();
        pbVar38 = (byte *)0x0;
        if (iVar37 != 0) {
          iVar37 = FUN_080098bc();
          pbVar38 = (byte *)0x0;
          if (iVar37 != 0) {
            pbVar38 = (byte *)FUN_0801aa48(0xff);
          }
        }
      }
    }
    return pbVar38;
  case 0x70:
    *DAT_08018568 = 0xea;
    puVar4[1] = 0xd1;
    puVar4[2] = 1;
    puVar4[3] = 0x14;
    puVar4[4] = 0xff;
    puVar4[5] = 0x70;
    iVar37 = DAT_0801856c;
    uVar45 = unaff_r6 & 0xffffff00;
    while( true ) {
      iVar41 = DAT_08018570;
      uVar53 = (uint3)(uVar45 >> 8);
      if (9 < (byte)uVar45) break;
      puVar4[(uVar45 & 0xff) + 6] = *(undefined1 *)((uVar45 & 0xff) + iVar37 + 0x14);
      uVar45 = CONCAT31(uVar53,(byte)uVar45 + 1);
    }
    for (uVar45 = (uint)uVar53 << 8; (byte)uVar45 < 5;
        uVar45 = CONCAT31((int3)(uVar45 >> 8),(byte)uVar45 + 1)) {
      puVar4[(uVar45 & 0xff) + 0x10] = *(undefined1 *)((uVar45 & 0xff) + iVar41 + 0x1b);
    }
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    pbVar38 = (byte *)FUN_0801e980(DAT_08018568,uVar45,0xff,0x70);
    return pbVar38;
  case 0x71:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_08008200(&uStack_38,0x2a);
    uStack_40 = *(undefined4 *)(DAT_0801c710 + 8);
    local_3c = *(undefined4 *)(DAT_0801c710 + 0xc);
    for (bVar30 = 0; bVar30 < 0x20; bVar30 = bVar30 + 1) {
      abStack_34[bVar30 - 6] = *(byte *)(DAT_0801c714 + (uint)bVar30);
    }
    pbVar38 = (byte *)FUN_0801e980(&uStack_40);
    return pbVar38;
  case 0x72:
    pbVar38 = (byte *)(uint)*DAT_0801af6c;
    if (pbVar38 == (byte *)0x1) {
      uStack_1e = uVar36;
      cStack_1b = cVar31;
      uStack_1a = uVar29;
      bStack_19 = bVar50;
      FUN_08008200(auStack_48,0x38);
      uStack_50 = *DAT_0801af70;
      uStack_4c = DAT_0801af70[1];
      bVar30 = 0;
      if ((*DAT_0801af74 == 0x200) || (*DAT_0801af74 == 0x100)) {
        iVar37 = *DAT_0801af78;
      }
      else {
        iVar37 = DAT_0801af7c;
      }
      for (uVar45 = 0; uVar45 < 0x18; uVar45 = (uint)(byte)((char)uVar45 + 1)) {
        auStack_48[uVar45 - 2] = *(undefined1 *)(iVar37 + uVar45 + 0x180);
      }
      for (; bVar30 < 0x16; bVar30 = bVar30 + 1) {
        abStack_34[bVar30 + 2] = *(byte *)(iVar37 + (uint)bVar30 + 0x1a0);
      }
      pbVar38 = (byte *)FUN_0801e980(&uStack_50);
    }
    return pbVar38;
  case 0x73:
    pbVar38 = (byte *)(uint)*DAT_080224d0;
    if (pbVar38 == (byte *)0x1) {
      uStack_1e = uVar36;
      cStack_1b = cVar31;
      uStack_1a = uVar29;
      bStack_19 = bVar50;
      for (bVar30 = 0; bVar30 < 0x18; bVar30 = bVar30 + 1) {
        abStack_34[bVar30 + 4] = (param_1 + 2)[bVar30];
      }
      FUN_0800c0d0(param_1 + 2,0x18);
      FUN_0800f850(0x180,&local_30,0x19);
      bVar30 = FUN_0800c0d0(param_1 + 0x1a,0x16);
      param_1[0x30] = bVar30;
      FUN_0800f850(0x1a0,param_1 + 0x1a,0x17);
      FUN_08014b50();
      pbVar38 = (byte *)FUN_0801aa48(0xff);
    }
    return pbVar38;
  case 0x74:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_08008200(&uStack_50,0x38);
    uStack_58 = *(undefined4 *)(DAT_0801b508 + 8);
    uStack_54._0_3_ = CONCAT12(*DAT_0801b50c,(short)*(undefined4 *)(DAT_0801b508 + 0xc));
    uStack_54 = (uint)(uint3)uStack_54;
    lVar51 = 0;
    while( true ) {
      bVar30 = (byte)((ulonglong)lVar51 >> 0x20);
      if (&Reset < (byte *)(uint)bVar30) break;
      uStack_54 = CONCAT13(bVar30 + 1,(uint3)uStack_54);
      iVar37 = *DAT_0801b510;
      while( true ) {
        bVar30 = (byte)lVar51;
        bVar50 = (byte)((ulonglong)lVar51 >> 0x20);
        if (0x13 < bVar30) break;
        uVar40 = *(undefined4 *)(iVar37 + ((uint)bVar30 + (uint)bVar50 * 0x14) * 4);
        auStack_48[(uint)bVar30 * 2 + -8] = (char)((uint)uVar40 >> 8);
        auStack_48[(uint)bVar30 * 2 + -7] = (char)uVar40;
        lVar51 = CONCAT71((int7)((ulonglong)lVar51 >> 8),bVar30 + 1);
      }
      FUN_0801e980();
      do {
      } while (*(short *)(*DAT_0801b514 + 0x25a) != 0);
      FUN_0800db18(0x32);
      lVar51 = (ulonglong)(byte)(bVar50 + 1) << 0x20;
    }
    return (byte *)(uint)bVar30;
  case 0x75:
    if (*DAT_0802266c == '\0') {
      return param_1 + 2;
    }
    if (*DAT_08022670 == '\0') {
      iVar37 = DAT_08022690;
    }
    else if (*DAT_08022678 == '\0') {
      iVar37 = DAT_08022694;
    }
    else if (*DAT_0802267c == '\0') {
      iVar37 = DAT_08022698;
    }
    else if (*DAT_08022680 == '\0') {
      iVar37 = DAT_0802269c;
    }
    else if (*DAT_08022684 == '\0') {
      iVar37 = DAT_080226a0;
    }
    else if (*DAT_08022688 == '\0') {
      iVar37 = DAT_080226a4;
    }
    else {
      iVar37 = DAT_0802268c;
    }
    *(int *)(DAT_08022674 + 0x34) = iVar37;
    for (uVar45 = 0; uVar45 < 0x28; uVar45 = (uint)(byte)((char)uVar45 + 1)) {
      *(byte *)(iVar37 + uVar45) = (param_1 + 2)[uVar45 + 1];
    }
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    pbVar38 = (byte *)FUN_0801aa48(0xff);
    return pbVar38;
  case 0x76:
    if (*DAT_08022738 == '\0') {
      return param_1 + 2;
    }
    if (*DAT_0802273c == '\0') {
      iVar37 = DAT_0802275c;
    }
    else if (*DAT_08022744 == '\0') {
      iVar37 = DAT_08022760;
    }
    else if (*DAT_08022748 == '\0') {
      iVar37 = DAT_08022764;
    }
    else if (*DAT_0802274c == '\0') {
      iVar37 = DAT_08022768;
    }
    else if (*DAT_08022750 == '\0') {
      iVar37 = DAT_0802276c;
    }
    else if (*DAT_08022754 == '\0') {
      iVar37 = DAT_08022770;
    }
    else {
      iVar37 = DAT_08022758;
    }
    *(int *)(DAT_08022740 + 0x34) = iVar37;
    for (uVar45 = 0; uVar45 < 0x28; uVar45 = (uint)(byte)((char)uVar45 + 1)) {
      *(byte *)(uVar45 + iVar37 + 0x28) = (param_1 + 2)[uVar45 + 1];
    }
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    pbVar38 = (byte *)FUN_0801aa48(0xff);
    return pbVar38;
  case 0x77:
    if (*DAT_08022804 == '\0') {
      return param_1 + 2;
    }
    if (*DAT_08022808 == '\0') {
      iVar37 = DAT_08022828;
    }
    else if (*DAT_08022810 == '\0') {
      iVar37 = DAT_0802282c;
    }
    else if (*DAT_08022814 == '\0') {
      iVar37 = DAT_08022830;
    }
    else if (*DAT_08022818 == '\0') {
      iVar37 = DAT_08022834;
    }
    else if (*DAT_0802281c == '\0') {
      iVar37 = DAT_08022838;
    }
    else if (*DAT_08022820 == '\0') {
      iVar37 = DAT_0802283c;
    }
    else {
      iVar37 = DAT_08022824;
    }
    *(int *)(DAT_0802280c + 0x34) = iVar37;
    for (uVar45 = 0; uVar45 < 0x28; uVar45 = (uint)(byte)((char)uVar45 + 1)) {
      *(byte *)(uVar45 + iVar37 + 0x50) = (param_1 + 2)[uVar45 + 1];
    }
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    pbVar38 = (byte *)FUN_0801aa48(0xff);
    return pbVar38;
  case 0x78:
    if (*DAT_080228d0 == '\0') {
      return param_1 + 2;
    }
    if (*DAT_080228d4 == '\0') {
      iVar37 = DAT_080228f4;
    }
    else if (*DAT_080228dc == '\0') {
      iVar37 = DAT_080228f8;
    }
    else if (*DAT_080228e0 == '\0') {
      iVar37 = DAT_080228fc;
    }
    else if (*DAT_080228e4 == '\0') {
      iVar37 = DAT_08022900;
    }
    else if (*DAT_080228e8 == '\0') {
      iVar37 = DAT_08022904;
    }
    else if (*DAT_080228ec == '\0') {
      iVar37 = DAT_08022908;
    }
    else {
      iVar37 = DAT_080228f0;
    }
    *(int *)(DAT_080228d8 + 0x34) = iVar37;
    for (uVar45 = 0; uVar45 < 0x28; uVar45 = (uint)(byte)((char)uVar45 + 1)) {
      *(byte *)(uVar45 + iVar37 + 0x78) = (param_1 + 2)[uVar45 + 1];
    }
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    pbVar38 = (byte *)FUN_0801aa48(0xff);
    return pbVar38;
  case 0x79:
    param_1 = param_1 + 2;
    if (*DAT_080229bc == '\0') {
      return param_1;
    }
    if (*DAT_080229c0 == '\0') {
      iVar37 = DAT_080229e0;
    }
    else if (*DAT_080229c8 == '\0') {
      iVar37 = DAT_080229e4;
    }
    else if (*DAT_080229cc == '\0') {
      iVar37 = DAT_080229e8;
    }
    else if (*DAT_080229d0 == '\0') {
      iVar37 = DAT_080229ec;
    }
    else if (*DAT_080229d4 == '\0') {
      iVar37 = DAT_080229f0;
    }
    else if (*DAT_080229d8 == '\0') {
      iVar37 = DAT_080229f4;
    }
    else {
      iVar37 = DAT_080229dc;
    }
    *(int *)(DAT_080229c4 + 0x34) = iVar37;
    for (bVar30 = 0; bVar30 < 0x2a; bVar30 = bVar30 + 1) {
      *(byte *)((uint)bVar30 + iVar37 + 0xa0) = param_1[bVar30 + 1];
    }
    iVar37 = *(int *)(iVar27 + 0x34);
    *(byte *)(iVar37 + 200) = *param_1;
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    uVar33 = FUN_0800c0d0(iVar37,0xc9);
    iVar37 = *(int *)(iVar27 + 0x34);
    *(undefined1 *)(iVar37 + 0xc9) = uVar33;
    FUN_0800f850(0x1c0,iVar37,0xca);
    FUN_080153bc();
    pbVar38 = (byte *)FUN_0801aa48(0xff);
    return pbVar38;
  case 0x7a:
    pbVar38 = abStack_34 + 0x24;
    if ((*DAT_08021f44 != '\x01') || (*DAT_08021f48 != '\x01')) {
      return param_1 + 2;
    }
    bVar30 = 0;
    while( true ) {
      uStack_1e = uVar36;
      cStack_1b = cVar31;
      uStack_1a = uVar29;
      bStack_19 = bVar50;
      if (2 < bVar30) break;
      pbVar38[bVar30] = (param_1 + 2)[bVar30];
      bVar30 = bVar30 + 1;
    }
    do {
      FUN_08016658(pbVar38,3);
      FUN_0800f850(0x28a,pbVar38,4);
      FUN_08019844(0,0x84);
      FUN_08013a04();
      FUN_08017b3c();
      FUN_0800db18(100);
      FUN_08022f60();
    } while( true );
  case 0x7b:
    if ((*DAT_0801a5a4 == 0x200) || (*DAT_0801a5a4 == 0x100)) {
      local_2c = *DAT_0801a5a8;
    }
    else {
      local_2c = DAT_0801a5ac;
    }
    pbVar38 = (byte *)(uint)*DAT_0801a5b0;
    if (pbVar38 == (byte *)0x1) {
      uStack_1e = uVar36;
      cStack_1b = cVar31;
      uStack_1a = uVar29;
      bStack_19 = bVar50;
      for (local_30._0_1_ = 0; (byte)local_30 < 4; local_30._0_1_ = (byte)local_30 + 1) {
        *(undefined1 *)((int)&local_28 + (uint)(byte)local_30) =
             *(undefined1 *)(local_2c + (byte)local_30 + 0x28a);
      }
      bVar30 = FUN_08016658(&local_28,3);
      puVar4 = DAT_0801a5b4;
      if (bVar30 != local_28._3_1_) {
        local_28 = (uint)local_28._3_1_ << 0x18;
      }
      *DAT_0801a5b4 = 0xea;
      puVar4[1] = 0xd1;
      puVar4[2] = 1;
      puVar4[3] = 6;
      puVar4[4] = 0xff;
      puVar4[5] = 0x7b;
      puVar4[6] = (byte)local_28;
      puVar4[7] = local_28._1_1_;
      puVar4[8] = local_28._2_1_;
      pbVar38 = (byte *)FUN_0801e980();
    }
    return pbVar38;
  case 0x7c:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_08021a50(param_1 + 2);
    FUN_0800db18(100);
    pbVar38 = (byte *)FUN_08015f28();
    return pbVar38;
  case 0x7d:
    if ((*DAT_0801a124 == 0x200) || (*DAT_0801a124 == 0x100)) {
      local_2c = *DAT_0801a128;
    }
    else {
      local_2c = DAT_0801a12c;
    }
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    for (local_30._0_1_ = 0; (byte)local_30 < 5; local_30._0_1_ = (byte)local_30 + 1) {
      *(undefined1 *)((int)&local_28 + (uint)(byte)local_30) =
           *(undefined1 *)(local_2c + (byte)local_30 + 0x28e);
    }
    cVar31 = FUN_08016658(&local_28,4);
    puVar4 = DAT_0801a130;
    if (cVar31 != (byte)local_24) {
      local_28 = 0;
    }
    *DAT_0801a130 = 0xea;
    puVar4[1] = 0xd1;
    puVar4[2] = 1;
    puVar4[3] = 8;
    puVar4[4] = 0xff;
    puVar4[5] = 0x7d;
    puVar4[6] = (byte)local_28;
    puVar4[7] = local_28._1_1_;
    puVar4[8] = local_28._2_1_;
    puVar4[9] = local_28._3_1_;
    pbVar38 = (byte *)FUN_0801e980();
    return pbVar38;
  case 0x7e:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_08021db6(param_1 + 2);
    FUN_0800db18(100);
    uVar45 = DAT_08013370;
    uVar46 = FUN_08010920();
    if (uVar46 != 0) {
      uVar45 = uVar46;
    }
    FUN_08017c80(0x2000000);
    uVar40 = DAT_0801335c;
    local_1c = 0;
    cStack_1b = 8;
    bStack_19 = 0x48;
    FUN_0801031c(DAT_0801335c,&local_1c);
    local_1c = (byte)((int)uVar40 >> 0x12);
    cStack_1b = (char)((int)uVar40 >> 0x1a);
    bStack_19 = 0x18;
    uStack_1a = 3;
    FUN_0801031c(uVar40,&local_1c);
    uVar40 = DAT_08013360;
    FUN_0800a6e4(DAT_08013360);
    FUN_0800a808(&uStack_38);
    abStack_34[2] = 0;
    abStack_34[3] = 1;
    abStack_34[0] = 4;
    uStack_36 = 0;
    local_30 = 0x100;
    uStack_35 = 0;
    uStack_2e = 0;
    uStack_38 = (ushort)(DAT_08013364 / uVar45);
    uStack_2d = 1;
    abStack_34[1] = 1;
    FUN_0800a720(uVar40,&uStack_38);
    uStack_22 = 0;
    uStack_21 = 0;
    local_20._0_1_ = 1;
    local_2c = 0;
    local_28 = 0;
    local_24._0_1_ = 0;
    local_24._1_1_ = 0;
    local_20._1_1_ = 1;
    FUN_0800a568(&local_2c);
    pbVar38 = (byte *)FUN_0800a710(uVar40,2,1);
    return pbVar38;
  case 0x7f:
    if ((*DAT_0801a4e8 == 0x200) || (*DAT_0801a4e8 == 0x100)) {
      local_2c = *DAT_0801a4ec;
    }
    else {
      local_2c = DAT_0801a4f0;
    }
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    for (local_30._0_1_ = 0; (byte)local_30 < 5; local_30._0_1_ = (byte)local_30 + 1) {
      *(undefined1 *)((int)&local_28 + (uint)(byte)local_30) =
           *(undefined1 *)(local_2c + (byte)local_30 + 0x293);
    }
    cVar31 = FUN_08016658(&local_28,4);
    puVar4 = DAT_0801a4f4;
    if (cVar31 != (byte)local_24) {
      local_28 = 0;
    }
    *DAT_0801a4f4 = 0xea;
    puVar4[1] = 0xd1;
    puVar4[2] = 1;
    puVar4[3] = 8;
    puVar4[4] = 0xff;
    puVar4[5] = 0x7f;
    puVar4[6] = (byte)local_28;
    puVar4[7] = local_28._1_1_;
    puVar4[8] = local_28._2_1_;
    puVar4[9] = local_28._3_1_;
    pbVar38 = (byte *)FUN_0801e980();
    return pbVar38;
  case 0x80:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_080222c0(param_1 + 2);
    FUN_0800db18(100);
    pbVar38 = (byte *)FUN_08013fb8();
    return pbVar38;
  case 0x81:
    if ((*DAT_0801ac5c == 0x200) || (*DAT_0801ac5c == 0x100)) {
      local_2c = *DAT_0801ac60;
    }
    else {
      local_2c = DAT_0801ac64;
    }
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    for (local_30._0_1_ = 0; (byte)local_30 < 3; local_30._0_1_ = (byte)local_30 + 1) {
      *(undefined1 *)((int)&local_28 + (uint)(byte)local_30) =
           *(undefined1 *)(local_2c + (byte)local_30 + 0x298);
    }
    cVar31 = FUN_08016658(&local_28,2);
    puVar4 = DAT_0801ac70;
    if (cVar31 != local_28._2_1_) {
      uVar40 = VectorFloatToUnsigned(*DAT_0801ac68 * DAT_0801ac6c,3);
      local_2c = CONCAT22(local_2c._2_2_,(short)uVar40);
      local_28._0_2_ = CONCAT11((char)uVar40,(char)((uint)uVar40 >> 8));
    }
    *DAT_0801ac70 = 0xea;
    puVar4[1] = 0xd1;
    puVar4[2] = 1;
    puVar4[3] = 6;
    puVar4[4] = 0xff;
    puVar4[5] = 0x81;
    puVar4[6] = (byte)local_28;
    puVar4[7] = local_28._1_1_;
    pbVar38 = (byte *)FUN_0801e980();
    return pbVar38;
  case 0x82:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_08021f50(param_1 + 2);
    FUN_0800db18(100);
    pbVar38 = (byte *)FUN_08013b48();
    return pbVar38;
  case 0x83:
    if ((*DAT_0801a808 == 0x200) || (*DAT_0801a808 == 0x100)) {
      iVar37 = *DAT_0801a80c;
    }
    else {
      iVar37 = DAT_0801a810;
    }
    *DAT_0801a814 = 0xea;
    puVar8[1] = 0xd1;
    puVar8[2] = 1;
    puVar8[3] = 0x13;
    puVar8[4] = 0xff;
    puVar8[5] = 0x83;
    uStack_38 = uStack_38 & 0xff00;
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    while( true ) {
      if (0xf < (byte)uStack_38) break;
      abStack_34[(byte)uStack_38] = *(byte *)(iVar37 + (uint)(byte)uStack_38 + 0x29b);
      uStack_38 = CONCAT11(uStack_38._1_1_,(byte)uStack_38 + 1);
    }
    cVar31 = FUN_08016658(abStack_34,0xf);
    uStack_38 = uStack_38 & 0xff00;
    if (cVar31 == local_28._3_1_) {
      while ((byte)uStack_38 < 0xf) {
        puVar8[(byte)uStack_38 + 6] = abStack_34[(byte)uStack_38];
        uStack_38 = CONCAT11(uStack_38._1_1_,(byte)uStack_38 + 1);
      }
    }
    else {
      while ((byte)uStack_38 < 0xf) {
        puVar8[(byte)uStack_38] = 0;
        uStack_38 = CONCAT11(uStack_38._1_1_,(byte)uStack_38 + 1);
      }
      puVar8[6] = *DAT_0801a818;
      puVar8[7] = *DAT_0801a81c;
      puVar8[8] = *DAT_0801a820;
      puVar8[9] = *DAT_0801a824;
      puVar8[10] = *DAT_0801a828;
      fVar48 = DAT_0801a834;
      fVar3 = DAT_0801a830;
      if (0.0 <= *DAT_0801a82c) {
        uVar40 = VectorFloatToUnsigned(*DAT_0801a82c * DAT_0801a834,3);
        uVar33 = (undefined1)uVar40;
      }
      else {
        uVar40 = VectorFloatToUnsigned(*DAT_0801a82c * DAT_0801a830,3);
        uVar33 = (undefined1)uVar40;
        puVar8[0xb] = 0x80;
      }
      puVar8[0xb] = puVar8[0xb];
      puVar8[0xc] = uVar33;
      if (0.0 <= *DAT_0801a838) {
        uVar40 = VectorFloatToUnsigned(*DAT_0801a838 * fVar48,3);
        uVar33 = (undefined1)uVar40;
      }
      else {
        uVar40 = VectorFloatToUnsigned(*DAT_0801a838 * fVar3,3);
        uVar33 = (undefined1)uVar40;
        puVar8[0xd] = 0x80;
      }
      puVar8[0xd] = puVar8[0xd];
      puVar8[0xe] = uVar33;
      if (0.0 <= *DAT_0801a83c) {
        uVar40 = VectorFloatToUnsigned(*DAT_0801a83c * fVar48,3);
        uVar33 = (undefined1)uVar40;
      }
      else {
        uVar40 = VectorFloatToUnsigned(*DAT_0801a83c * fVar3,3);
        uVar33 = (undefined1)uVar40;
        puVar8[0xf] = 0x80;
      }
      puVar8[0xf] = puVar8[0xf];
      puVar8[0x10] = uVar33;
      if (0.0 <= *DAT_0801a840) {
        uVar40 = VectorFloatToUnsigned(*DAT_0801a840 * fVar48,3);
        uVar33 = (undefined1)uVar40;
      }
      else {
        uVar40 = VectorFloatToUnsigned(*DAT_0801a840 * fVar3,3);
        uVar33 = (undefined1)uVar40;
        puVar8[0x11] = 0x80;
      }
      puVar8[0x11] = puVar8[0x11];
      puVar8[0x12] = uVar33;
      if (0.0 <= *DAT_0801a844) {
        uVar40 = VectorFloatToUnsigned(*DAT_0801a844 * fVar48,3);
        uVar33 = (undefined1)uVar40;
      }
      else {
        uVar40 = VectorFloatToUnsigned(*DAT_0801a844 * fVar3,3);
        uVar33 = (undefined1)uVar40;
        puVar8[0x13] = 0x80;
      }
      puVar8[0x13] = puVar8[0x13];
      puVar8[0x14] = uVar33;
    }
    pbVar38 = (byte *)FUN_0801e980(DAT_0801a814);
    return pbVar38;
  case 0x84:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    iVar37 = FUN_08022b40(param_1 + 2);
    if (iVar37 == 0) {
      return (byte *)0x0;
    }
LAB_0801d57c:
    uVar40 = 10;
    goto LAB_0801d200;
  case 0x85:
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    iVar37 = FUN_080112ec(abStack_34 + 0x20,&uStack_58);
    puVar4 = DAT_0801a1ac;
    pbVar38 = (byte *)0x0;
    if (iVar37 != 0) {
      *DAT_0801a1ac = 0xea;
      puVar4[1] = 0xd1;
      puVar4[2] = 1;
      puVar4[3] = 5;
      puVar4[4] = 0xff;
      puVar4[5] = 0x85;
      puVar4[6] = 0;
      pbVar38 = (byte *)FUN_0801e980(DAT_0801a1ac);
    }
    return pbVar38;
  case 0x86:
    uStack_1a = 0;
    bStack_19 = 0;
    cStack_1b = 0;
    local_1c = 0;
    uStack_1e = uVar36;
    iVar37 = FUN_080112f8(local_60);
    puVar4 = DAT_0801a2b0;
    pbVar38 = (byte *)0x0;
    if (iVar37 != 0) {
      *DAT_0801a2b0 = 0xea;
      puVar4[1] = 0xd1;
      puVar4[2] = 1;
      puVar4[3] = 0x37;
      puVar4[4] = 0xff;
      puVar4[5] = 0x86;
      for (local_20._0_1_ = 0; (byte)local_20 < 0x33; local_20._0_1_ = (byte)local_20 + 1) {
        puVar4[(byte)local_20 + 6] = local_60[(byte)local_20];
      }
      FUN_0801e980(DAT_0801a2b0);
      FUN_0800db18(100);
      iVar37 = FUN_080112f0(local_60);
      pbVar38 = (byte *)0x0;
      if (iVar37 != 0) {
        puVar4[3] = 0x3a;
        puVar4[4] = 0xff;
        puVar4[5] = 0x89;
        for (local_20._0_1_ = 0; (byte)local_20 < 0x36; local_20._0_1_ = (byte)local_20 + 1) {
          puVar4[(byte)local_20 + 6] = local_60[(byte)local_20];
        }
        FUN_0801e980(DAT_0801a2b0);
        FUN_0800db18(100);
        iVar37 = FUN_080112f4(local_60);
        pbVar38 = (byte *)0x0;
        if (iVar37 != 0) {
          puVar4[3] = 0x37;
          puVar4[4] = 0xff;
          puVar4[5] = 0x8a;
          for (local_20._0_1_ = 0; (byte)local_20 < 0x33; local_20._0_1_ = (byte)local_20 + 1) {
            puVar4[(byte)local_20 + 6] = local_60[(byte)local_20];
          }
          pbVar38 = (byte *)FUN_0801e980(DAT_0801a2b0);
        }
      }
    }
    return pbVar38;
  case 0x87:
    bVar30 = param_1[2] + 1;
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_08008200(local_60 + 4,0x20);
    FUN_08008200(&uStack_38,0x20);
    if ((*DAT_08022c20 == 0x200) || (*DAT_08022c20 == 0x100)) {
      local_3c = *DAT_08022c24;
    }
    else {
      local_3c = DAT_08022c28;
    }
    for (local_60[0] = 0; local_60[0] < bVar30; local_60[0] = local_60[0] + 1) {
      *(byte *)((int)&uStack_38 + (uint)local_60[0]) = param_1[local_60[0] + 2];
    }
    FUN_0800f850(0x2ab,&uStack_38,bVar30);
    pbVar38 = local_60 + 4;
    for (local_60[0] = 0; local_60[0] < bVar30; local_60[0] = local_60[0] + 1) {
      pbVar38[local_60[0]] = *(byte *)(local_3c + (uint)local_60[0] + 0x2ab);
    }
    local_60[0] = 0;
    while( true ) {
      if (bVar30 <= local_60[0]) {
        pbVar38 = (byte *)FUN_0801aa48(0xff);
        return pbVar38;
      }
      if (param_1[local_60[0] + 2] != pbVar38[local_60[0]]) break;
      local_60[0] = local_60[0] + 1;
    }
    return pbVar38;
  case 0x88:
    bVar30 = 0;
    if ((*DAT_0801a394 == 0x200) || (*DAT_0801a394 == 0x100)) {
      iVar37 = *DAT_0801a398;
    }
    else {
      iVar37 = DAT_0801a39c;
    }
    *DAT_0801a3a0 = 0xea;
    puVar6[1] = 0xd1;
    puVar6[2] = 1;
    puVar6[3] = 0;
    puVar6[4] = 0xff;
    puVar6[5] = 0x88;
    puVar6[3] = *(undefined1 *)(iVar37 + 0x2ab);
    if ((byte)puVar6[3] < 0x20) {
      puVar6[3] = puVar6[3] + '\x05';
      for (; (int)(uint)bVar30 < (int)((byte)puVar6[3] - 4); bVar30 = bVar30 + 1) {
        puVar6[bVar30 + 6] = *(undefined1 *)(iVar37 + (uint)bVar30 + 0x2ab);
      }
    }
    else {
      puVar6[3] = 5;
    }
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    pbVar38 = (byte *)FUN_0801e980(DAT_0801a3a0);
    return pbVar38;
  case 0x89:
    bVar30 = param_1[2] + 1;
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    FUN_08008200(local_60 + 4,0x20);
    FUN_08008200(&uStack_38,0x20);
    if ((*DAT_08022d08 == 0x200) || (*DAT_08022d08 == 0x100)) {
      local_3c = *DAT_08022d0c;
    }
    else {
      local_3c = DAT_08022d10;
    }
    for (local_60[0] = 0; local_60[0] < bVar30; local_60[0] = local_60[0] + 1) {
      *(byte *)((int)&uStack_38 + (uint)local_60[0]) = param_1[local_60[0] + 2];
    }
    FUN_0800f850(0x2cb,&uStack_38,bVar30);
    pbVar38 = local_60 + 4;
    for (local_60[0] = 0; local_60[0] < bVar30; local_60[0] = local_60[0] + 1) {
      pbVar38[local_60[0]] = *(byte *)(local_3c + (uint)local_60[0] + 0x2cb);
    }
    local_60[0] = 0;
    while( true ) {
      if (bVar30 <= local_60[0]) {
        pbVar38 = (byte *)FUN_0801aa48(0xff);
        return pbVar38;
      }
      if (param_1[local_60[0] + 2] != pbVar38[local_60[0]]) break;
      local_60[0] = local_60[0] + 1;
    }
    return pbVar38;
  case 0x8a:
    bVar30 = 0;
    if ((*DAT_0801a42c == 0x200) || (*DAT_0801a42c == 0x100)) {
      iVar37 = *DAT_0801a430;
    }
    else {
      iVar37 = DAT_0801a434;
    }
    *DAT_0801a438 = 0xea;
    puVar7[1] = 0xd1;
    puVar7[2] = 1;
    puVar7[3] = 0;
    puVar7[4] = 0xff;
    puVar7[5] = 0x8a;
    puVar7[3] = *(undefined1 *)(iVar37 + 0x2cb);
    if ((byte)puVar7[3] < 0x20) {
      puVar7[3] = puVar7[3] + '\x05';
      for (; (int)(uint)bVar30 < (int)((byte)puVar7[3] - 4); bVar30 = bVar30 + 1) {
        puVar7[bVar30 + 6] = *(undefined1 *)(iVar37 + (uint)bVar30 + 0x2cb);
      }
    }
    else {
      puVar7[3] = 5;
    }
    uStack_1e = uVar36;
    cStack_1b = cVar31;
    uStack_1a = uVar29;
    bStack_19 = bVar50;
    pbVar38 = (byte *)FUN_0801e980(DAT_0801a438);
    return pbVar38;
  }
  uVar40 = 100;
LAB_0801d200:
  FUN_0800db18(uVar40);
LAB_0801d3fe:
  pbVar38 = (byte *)FUN_0801aa48(0xff);
  return pbVar38;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801d5e8 at 0x0801d5e8
// ---------------------------------------------------------------------------

void FUN_0801d5e8(char param_1)

{
  ushort uVar1;
  char *pcVar2;
  undefined1 *puVar3;
  char *pcVar4;
  
  puVar3 = DAT_0801d6f4;
  pcVar2 = DAT_0801d6f0;
  if (DAT_0801d6f0[0x25c] != '\0') {
    return;
  }
  if ((param_1 == -0x16) && (*(short *)(DAT_0801d6f0 + 300) == 0)) {
    pcVar2[0x260] = '\0';
    pcVar2[0x261] = '\0';
    *puVar3 = 0;
    *pcVar2 = -0x16;
    pcVar2[300] = '\x01';
    pcVar2[0x12d] = '\0';
  }
  else {
    if ((*DAT_0801d6f0 == -0x16) && (*(ushort *)(DAT_0801d6f0 + 300) < 300)) {
      pcVar4 = DAT_0801d6f0 + *(ushort *)(DAT_0801d6f0 + 300);
      *(ushort *)(DAT_0801d6f0 + 300) = *(ushort *)(DAT_0801d6f0 + 300) + 1;
      *pcVar4 = param_1;
      if ((*(ushort *)(pcVar2 + 300) < 2) || (pcVar2[1] == -0x2f)) goto LAB_0801d654;
    }
    else if (*DAT_0801d6f0 == -0x15) goto LAB_0801d654;
    pcVar2[300] = '\0';
    pcVar2[0x12d] = '\0';
  }
LAB_0801d654:
  if (((*pcVar2 == -0x16) && (param_1 == -0xb)) &&
     (*(short *)(pcVar2 + 300) == (ushort)((byte)pcVar2[3] + 4))) {
    pcVar2[0x25c] = '\x01';
    pcVar2[0x25e] = '\0';
    pcVar2[0x25f] = '\0';
    pcVar2[300] = '\0';
    pcVar2[0x12d] = '\0';
  }
  if ((param_1 == -0x15) && (*(short *)(pcVar2 + 300) == 0)) {
    *pcVar2 = -0x15;
    pcVar2[300] = '\x01';
    pcVar2[0x12d] = '\0';
    pcVar2[0x260] = '\0';
    pcVar2[0x261] = '\0';
    *puVar3 = 0;
  }
  else if ((*pcVar2 == -0x15) && (*(ushort *)(pcVar2 + 300) < 0x4b)) {
    uVar1 = *(ushort *)(pcVar2 + 300);
    *(ushort *)(pcVar2 + 300) = uVar1 + 1;
    pcVar2[uVar1] = param_1;
  }
  else if (*pcVar2 != -0x16) {
    pcVar2[300] = '\0';
    pcVar2[0x12d] = '\0';
  }
  if (((*pcVar2 == -0x15) && (param_1 == -0xb)) &&
     (*(short *)(pcVar2 + 300) == (ushort)((byte)pcVar2[3] + 4))) {
    pcVar2[0x25c] = '\x01';
    pcVar2[0x25e] = '\0';
    pcVar2[0x25f] = '\0';
    pcVar2[300] = '\0';
    pcVar2[0x12d] = '\0';
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801d6f8 at 0x0801d6f8
// ---------------------------------------------------------------------------

void FUN_0801d6f8(char param_1)

{
  ushort uVar1;
  char *pcVar2;
  undefined1 *puVar3;
  char *pcVar4;
  char *pcVar5;
  
  pcVar4 = DAT_0801d8bc;
  puVar3 = DAT_0801d8b8;
  pcVar2 = DAT_0801d8b4;
  if (DAT_0801d8b4[0x25c] != '\0') {
    return;
  }
  if ((param_1 == -0x16) && (*(short *)(DAT_0801d8b4 + 300) == 0)) {
    pcVar2[0x260] = '\0';
    pcVar2[0x261] = '\0';
    *puVar3 = 0;
    *pcVar2 = -0x16;
    pcVar2[300] = '\x01';
    pcVar2[0x12d] = '\0';
  }
  else if ((*DAT_0801d8b4 == -0x16) && (*(ushort *)(DAT_0801d8b4 + 300) < 300)) {
    pcVar5 = DAT_0801d8b4 + *(ushort *)(DAT_0801d8b4 + 300);
    *(ushort *)(DAT_0801d8b4 + 300) = *(ushort *)(DAT_0801d8b4 + 300) + 1;
    *pcVar5 = param_1;
    if ((1 < *(ushort *)(pcVar2 + 300)) && (pcVar2[1] != -0x2f)) {
LAB_0801d772:
      pcVar2[300] = '\0';
      pcVar2[0x12d] = '\0';
    }
  }
  else if (((*DAT_0801d8b4 != -0x15) && (*DAT_0801d8b4 != *DAT_0801d8bc)) &&
          (*DAT_0801d8b4 != -0x5b)) goto LAB_0801d772;
  if (((*pcVar2 == -0x16) && (param_1 == -0xb)) &&
     (*(short *)(pcVar2 + 300) == (ushort)((byte)pcVar2[3] + 4))) {
    pcVar2[0x25c] = '\x01';
    pcVar2[0x25e] = '\0';
    pcVar2[0x25f] = '\0';
    pcVar2[300] = '\0';
    pcVar2[0x12d] = '\0';
  }
  if ((param_1 == -0x15) && (*(short *)(pcVar2 + 300) == 0)) {
    *pcVar2 = -0x15;
    pcVar2[300] = '\x01';
    pcVar2[0x12d] = '\0';
    pcVar2[0x260] = '\0';
    pcVar2[0x261] = '\0';
    *puVar3 = 0;
  }
  else {
    if ((*pcVar2 == -0x15) && (*(ushort *)(pcVar2 + 300) < 0x4b)) {
      uVar1 = *(ushort *)(pcVar2 + 300);
      *(ushort *)(pcVar2 + 300) = uVar1 + 1;
      pcVar2[uVar1] = param_1;
      if ((*(ushort *)(pcVar2 + 300) < 2) || (pcVar2[1] == *pcVar4)) goto LAB_0801d808;
    }
    else if (((*pcVar2 == -0x16) || (*pcVar2 == *pcVar4)) || (*pcVar2 == -0x5b)) goto LAB_0801d808;
    pcVar2[300] = '\0';
    pcVar2[0x12d] = '\0';
  }
LAB_0801d808:
  if (((*pcVar2 == -0x15) && (param_1 == -0xb)) &&
     (*(short *)(pcVar2 + 300) == (ushort)((byte)pcVar2[3] + 4))) {
    pcVar2[0x25c] = '\x01';
    pcVar2[0x25e] = '\0';
    pcVar2[0x25f] = '\0';
    pcVar2[300] = '\0';
    pcVar2[0x12d] = '\0';
  }
  if ((param_1 == -0x5b) && (*(short *)(pcVar2 + 300) == 0)) {
    pcVar2[0x260] = '\0';
    pcVar2[0x261] = '\0';
    *puVar3 = 0;
    *pcVar2 = -0x5b;
    pcVar2[300] = '\x01';
    pcVar2[0x12d] = '\0';
  }
  else if ((*(short *)(pcVar2 + 300) == 0) ||
          ((*pcVar2 != -0x5b || (299 < *(ushort *)(pcVar2 + 300))))) {
    if ((*pcVar2 != -0x16) && ((*pcVar2 != -0x15 && (*pcVar2 != *pcVar4)))) {
      pcVar2[300] = '\0';
      pcVar2[0x12d] = '\0';
    }
  }
  else {
    uVar1 = *(ushort *)(pcVar2 + 300);
    *(ushort *)(pcVar2 + 300) = uVar1 + 1;
    pcVar2[uVar1] = param_1;
  }
  if (((*pcVar2 == -0x5b) && (pcVar2[3] == '\b')) && (*(short *)(pcVar2 + 300) == 0xd)) {
    pcVar2[0x25c] = '\x01';
    pcVar2[0x25e] = '\0';
    pcVar2[0x25f] = '\0';
    pcVar2[300] = '\0';
    pcVar2[0x12d] = '\0';
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801d8c0 at 0x0801d8c0
// ---------------------------------------------------------------------------

void FUN_0801d8c0(char param_1)

{
  ushort uVar1;
  char *pcVar2;
  undefined1 *puVar3;
  char *pcVar4;
  
  puVar3 = DAT_0801d9c0;
  pcVar2 = DAT_0801d9bc;
  if (DAT_0801d9bc[0x25c] == '\0') {
    if ((param_1 == -0x16) && (*(short *)(DAT_0801d9bc + 300) == 0)) {
      pcVar2[0x260] = '\0';
      pcVar2[0x261] = '\0';
      *puVar3 = 0;
      *pcVar2 = -0x16;
      pcVar2[300] = '\x01';
      pcVar2[0x12d] = '\0';
    }
    else if ((*DAT_0801d9bc == -0x16) && (*(ushort *)(DAT_0801d9bc + 300) < 300)) {
      pcVar4 = DAT_0801d9bc + *(ushort *)(DAT_0801d9bc + 300);
      *(ushort *)(DAT_0801d9bc + 300) = *(ushort *)(DAT_0801d9bc + 300) + 1;
      *pcVar4 = param_1;
    }
    else if ((*DAT_0801d9bc != -0x15) && (*DAT_0801d9bc != ':')) {
      pcVar2[300] = '\0';
      pcVar2[0x12d] = '\0';
    }
    if (((*pcVar2 == -0x16) && (param_1 == -0xb)) &&
       (*(short *)(pcVar2 + 300) == (ushort)((byte)pcVar2[3] + 4))) {
      pcVar2[0x25c] = '\x01';
      pcVar2[0x25e] = '\0';
      pcVar2[0x25f] = '\0';
    }
    if ((param_1 == -0x15) && (*(short *)(pcVar2 + 300) == 0)) {
      *pcVar2 = -0x15;
      pcVar2[300] = '\x01';
      pcVar2[0x12d] = '\0';
      pcVar2[0x260] = '\0';
      pcVar2[0x261] = '\0';
      *puVar3 = 0;
    }
    else if ((*pcVar2 == -0x15) && (*(ushort *)(pcVar2 + 300) < 0x4b)) {
      uVar1 = *(ushort *)(pcVar2 + 300);
      *(ushort *)(pcVar2 + 300) = uVar1 + 1;
      pcVar2[uVar1] = param_1;
    }
    else if ((*pcVar2 != -0x16) && (*pcVar2 != ':')) {
      pcVar2[300] = '\0';
      pcVar2[0x12d] = '\0';
    }
    if (((*pcVar2 == -0x15) && (param_1 == -0xb)) &&
       (*(short *)(pcVar2 + 300) == (ushort)((byte)pcVar2[3] + 4))) {
      pcVar2[0x25c] = '\x01';
      pcVar2[0x25e] = '\0';
      pcVar2[0x25f] = '\0';
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801d9c4 at 0x0801d9c4
// ---------------------------------------------------------------------------

void FUN_0801d9c4(char param_1)

{
  ushort uVar1;
  char *pcVar2;
  undefined1 *puVar3;
  char *pcVar4;
  
  puVar3 = DAT_0801db4c;
  pcVar2 = DAT_0801db48;
  if (DAT_0801db48[0x25c] == '\0') {
    if ((param_1 == -0x16) && (*(short *)(DAT_0801db48 + 300) == 0)) {
      pcVar2[0x260] = '\0';
      pcVar2[0x261] = '\0';
      *puVar3 = 0;
      *pcVar2 = -0x16;
      pcVar2[300] = '\x01';
      pcVar2[0x12d] = '\0';
    }
    else if ((*DAT_0801db48 == -0x16) && (*(ushort *)(DAT_0801db48 + 300) < 300)) {
      pcVar4 = DAT_0801db48 + *(ushort *)(DAT_0801db48 + 300);
      *(ushort *)(DAT_0801db48 + 300) = *(ushort *)(DAT_0801db48 + 300) + 1;
      *pcVar4 = param_1;
    }
    else if ((*DAT_0801db48 != -0x15) && (*DAT_0801db48 != '\x01')) {
      pcVar2[300] = '\0';
      pcVar2[0x12d] = '\0';
    }
    if (((*pcVar2 == -0x16) && (param_1 == -0xb)) &&
       (*(short *)(pcVar2 + 300) == (ushort)((byte)pcVar2[3] + 4))) {
      pcVar2[0x25c] = '\x01';
      pcVar2[0x25e] = '\0';
      pcVar2[0x25f] = '\0';
    }
    if ((param_1 == -0x15) && (*(short *)(pcVar2 + 300) == 0)) {
      *pcVar2 = -0x15;
      pcVar2[300] = '\x01';
      pcVar2[0x12d] = '\0';
      pcVar2[0x260] = '\0';
      pcVar2[0x261] = '\0';
      *puVar3 = 0;
    }
    else if ((*pcVar2 == -0x15) && (*(ushort *)(pcVar2 + 300) < 0x4b)) {
      uVar1 = *(ushort *)(pcVar2 + 300);
      *(ushort *)(pcVar2 + 300) = uVar1 + 1;
      pcVar2[uVar1] = param_1;
    }
    else if ((*pcVar2 != -0x16) && (*pcVar2 != '\x01')) {
      pcVar2[300] = '\0';
      pcVar2[0x12d] = '\0';
    }
    if (((*pcVar2 == -0x15) && (param_1 == -0xb)) &&
       (*(short *)(pcVar2 + 300) == (ushort)((byte)pcVar2[3] + 4))) {
      pcVar2[0x25c] = '\x01';
      pcVar2[0x25e] = '\0';
      pcVar2[0x25f] = '\0';
    }
    if ((param_1 == '\x01') && (*(short *)(pcVar2 + 300) == 0)) {
      pcVar2[0x260] = '\0';
      pcVar2[0x261] = '\0';
      *puVar3 = 0;
      *pcVar2 = '\x01';
      pcVar2[300] = '\x01';
      pcVar2[0x12d] = '\0';
    }
    else if ((*(short *)(pcVar2 + 300) == 0) ||
            ((*pcVar2 != '\x01' || (299 < *(ushort *)(pcVar2 + 300))))) {
      if ((*pcVar2 != -0x16) && (*pcVar2 != -0x15)) {
        pcVar2[300] = '\0';
        pcVar2[0x12d] = '\0';
      }
    }
    else {
      uVar1 = *(ushort *)(pcVar2 + 300);
      *(ushort *)(pcVar2 + 300) = uVar1 + 1;
      pcVar2[uVar1] = param_1;
    }
    if ((*pcVar2 == '\x01') &&
       (((pcVar2[1] == '\x03' || (pcVar2[1] == '\x01')) && (*(short *)(pcVar2 + 300) == 8)))) {
      pcVar2[0x25c] = '\x02';
      pcVar2[0x25e] = '\0';
      pcVar2[0x25f] = '\0';
      pcVar2[300] = '\0';
      pcVar2[0x12d] = '\0';
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801db50 at 0x0801db50
// ---------------------------------------------------------------------------

void FUN_0801db50(void)

{
  byte bVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  byte *pbVar5;
  ushort *puVar6;
  
  pbVar5 = DAT_0801dbfc;
  pcVar4 = DAT_0801dbf8;
  pcVar3 = DAT_0801dbf4;
  iVar2 = DAT_0801dbf0;
  if (*(short *)(DAT_0801dbf0 + 0x25a) == 0) {
    FUN_0800c5fe(DAT_0801dbf0);
    *pbVar5 = 0;
    *(undefined2 *)(iVar2 + 0x25a) = 0;
    if (*pcVar4 != '\0') {
      puVar6 = DAT_0801dc04 + 4;
      *puVar6 = *puVar6 & 0xff7f;
      *puVar6 = *puVar6 | 0x20;
    }
    if (*pcVar3 != '\0') {
      FUN_08017e10();
      return;
    }
  }
  else {
    *DAT_0801dc00 = 0xaaaa;
    *(short *)(iVar2 + 0x25a) = *(short *)(iVar2 + 0x25a) + -1;
    if ((*pcVar4 != '\0') && (*(char *)(iVar2 + 0x262) == '\x01')) {
      bVar1 = *pbVar5;
      *pbVar5 = bVar1 + 1;
      *DAT_0801dc04 = (ushort)*(byte *)(iVar2 + (uint)bVar1 + 0x12e);
    }
    if (((*(short *)(iVar2 + 0x25a) == 0) && (*pbVar5 = 0, *(char *)(iVar2 + 0x262) == '\x01')) &&
       (*pcVar3 != '\0')) {
      do {
      } while (-1 < (int)((uint)DAT_0801dc04[-2] << 0x19));
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801dc08 at 0x0801dc08
// ---------------------------------------------------------------------------

void FUN_0801dc08(void)

{
  byte bVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  ushort *puVar6;
  
  iVar5 = DAT_0801dcb4;
  pcVar4 = DAT_0801dcb0;
  pcVar3 = DAT_0801dcac;
  iVar2 = DAT_0801dca8;
  if (*(short *)(DAT_0801dca8 + 0x25a) == 0) {
    FUN_0800c5fe(DAT_0801dca8);
    *(undefined1 *)(iVar5 + 1) = 0;
    *(undefined2 *)(iVar2 + 0x25a) = 0;
    if (*pcVar4 != '\0') {
      puVar6 = DAT_0801dcbc + 4;
      *puVar6 = *puVar6 & 0xff7f;
      *puVar6 = *puVar6 | 0x20;
    }
    if (*pcVar3 != '\0') {
      FUN_08017e28();
      return;
    }
  }
  else {
    *DAT_0801dcb8 = 0xaaaa;
    *(short *)(iVar2 + 0x25a) = *(short *)(iVar2 + 0x25a) + -1;
    if ((*pcVar4 != '\0') && (*(char *)(iVar2 + 0x262) == '\x02')) {
      bVar1 = *(byte *)(iVar5 + 1);
      *(byte *)(iVar5 + 1) = bVar1 + 1;
      *DAT_0801dcbc = (ushort)*(byte *)(iVar2 + (uint)bVar1 + 0x12e);
    }
    if (((*(short *)(iVar2 + 0x25a) == 0) &&
        (*(undefined1 *)(iVar5 + 1) = 0, *(char *)(iVar2 + 0x262) == '\x02')) && (*pcVar3 != '\0'))
    {
      do {
      } while (-1 < (int)((uint)DAT_0801dcbc[-2] << 0x19));
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801dcc0 at 0x0801dcc0
// ---------------------------------------------------------------------------

void FUN_0801dcc0(void)

{
  byte bVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  ushort *puVar6;
  
  puVar6 = DAT_0801dd68;
  iVar5 = DAT_0801dd64;
  pcVar4 = DAT_0801dd60;
  pcVar3 = DAT_0801dd5c;
  iVar2 = DAT_0801dd58;
  if (*(short *)(DAT_0801dd58 + 0x25a) == 0) {
    *(undefined1 *)(DAT_0801dd64 + 2) = 0;
    *(undefined2 *)(iVar2 + 0x25a) = 0;
    if (*pcVar4 != '\0') {
      FUN_08020654(puVar6,0x727,0);
      FUN_08020654(puVar6,0x525,1);
    }
    if (*pcVar3 != '\0') {
      FUN_08017e40();
      return;
    }
  }
  else {
    *DAT_0801dd6c = 0xaaaa;
    *(short *)(iVar2 + 0x25a) = *(short *)(iVar2 + 0x25a) + -1;
    if ((*pcVar4 != '\0') && (*(char *)(iVar2 + 0x262) == '\x03')) {
      bVar1 = *(byte *)(iVar5 + 2);
      *(byte *)(iVar5 + 2) = bVar1 + 1;
      puVar6[2] = (ushort)*(byte *)(iVar2 + (uint)bVar1 + 0x12e);
    }
    if (((*(short *)(iVar2 + 0x25a) == 0) &&
        (*(undefined1 *)(iVar5 + 2) = 0, *(char *)(iVar2 + 0x262) == '\x03')) && (*pcVar3 != '\0'))
    {
      do {
      } while (-1 < (int)((uint)*puVar6 << 0x19));
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801dd70 at 0x0801dd70
// ---------------------------------------------------------------------------

void FUN_0801dd70(void)

{
  byte bVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  ushort *puVar6;
  
  puVar6 = DAT_0801de18;
  iVar5 = DAT_0801de14;
  pcVar4 = DAT_0801de10;
  pcVar3 = DAT_0801de0c;
  iVar2 = DAT_0801de08;
  if (*(short *)(DAT_0801de08 + 0x25a) == 0) {
    *(undefined1 *)(DAT_0801de14 + 3) = 0;
    *(undefined2 *)(iVar2 + 0x25a) = 0;
    if (*pcVar4 != '\0') {
      FUN_08020654(puVar6,0x727,0);
      FUN_08020654(puVar6,0x525,1);
    }
    if (*pcVar3 != '\0') {
      FUN_08017e58();
      return;
    }
  }
  else {
    *DAT_0801de1c = 0xaaaa;
    *(short *)(iVar2 + 0x25a) = *(short *)(iVar2 + 0x25a) + -1;
    if ((*pcVar4 != '\0') && (*(char *)(iVar2 + 0x262) == '\x04')) {
      bVar1 = *(byte *)(iVar5 + 3);
      *(byte *)(iVar5 + 3) = bVar1 + 1;
      puVar6[2] = (ushort)*(byte *)(iVar2 + (uint)bVar1 + 0x12e);
    }
    if (((*(short *)(iVar2 + 0x25a) == 0) &&
        (*(undefined1 *)(iVar5 + 3) = 0, *(char *)(iVar2 + 0x262) == '\x04')) && (*pcVar3 != '\0'))
    {
      do {
      } while (-1 < (int)((uint)*puVar6 << 0x19));
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801e5c0 at 0x0801e5c0
// ---------------------------------------------------------------------------

void FUN_0801e5c0(byte *param_1,undefined1 *param_2)

{
  byte bVar1;
  
  bVar1 = *DAT_0801e664 != '\0';
  if (*DAT_0801e668 != '\0') {
    bVar1 = bVar1 | 2;
  }
  if (*DAT_0801e66c != '\0') {
    bVar1 = bVar1 | 4;
  }
  if (*DAT_0801e670 != '\0') {
    bVar1 = bVar1 | 8;
  }
  if (*DAT_0801e674 != '\0') {
    bVar1 = bVar1 | 0x10;
  }
  if (*DAT_0801e678 != '\0') {
    bVar1 = bVar1 | 0x20;
  }
  if (*DAT_0801e67c != '\0') {
    bVar1 = bVar1 | 0x40;
  }
  if (*DAT_0801e680 != '\0') {
    bVar1 = bVar1 | 0x80;
  }
  *param_1 = bVar1;
  *param_2 = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801e980 at 0x0801e980
// ---------------------------------------------------------------------------

void FUN_0801e980(int param_1)

{
  int iVar1;
  ushort *puVar2;
  undefined4 uVar3;
  undefined1 uVar4;
  int iVar5;
  byte bVar6;
  
  iVar1 = DAT_0801eb30;
  if ((*DAT_0801eb2c == '\x01') && (*(char *)(*(int *)(DAT_0801eb30 + 0x1c) + 0x262) == '\x01')) {
    FUN_08017e04();
  }
  if ((*DAT_0801eb34 == '\x01') && (*(char *)(*(int *)(iVar1 + 0x1c) + 0x262) == '\x02')) {
    FUN_08017e1c();
  }
  if ((*DAT_0801eb38 == '\x01') && (*(char *)(*(int *)(iVar1 + 0x1c) + 0x262) == '\x03')) {
    FUN_08017e34();
  }
  if ((*DAT_0801eb3c == '\x01') && (*(char *)(*(int *)(iVar1 + 0x1c) + 0x262) == '\x04')) {
    FUN_08017e4c();
  }
  *(undefined1 *)((uint)*(byte *)(param_1 + 3) + param_1 + 3) = 0xf5;
  uVar4 = FUN_0800c0d0(param_1 + 3,*(undefined1 *)(param_1 + 3));
  *(undefined1 *)((uint)*(byte *)(param_1 + 3) + param_1 + 2) = uVar4;
  iVar5 = *(int *)(iVar1 + 0x1c);
  for (bVar6 = 0; (uint)bVar6 < *(byte *)(param_1 + 3) + 4; bVar6 = bVar6 + 1) {
    *(undefined1 *)((uint)bVar6 + iVar5 + 0x12e) = *(undefined1 *)(param_1 + (uint)bVar6);
  }
  iVar5 = *(int *)(iVar1 + 0x1c);
  *(ushort *)(iVar5 + 0x25a) = *(byte *)(param_1 + 3) + 4;
  *(undefined1 *)(iVar5 + 0x130) = *(undefined1 *)(iVar1 + 10);
  thunk_FUN_0800a8b8();
  puVar2 = DAT_0801eb44;
  if ((*DAT_0801eb40 != '\0') && (*(char *)(*(int *)(iVar1 + 0x1c) + 0x262) == '\x01')) {
    *DAT_0801eb44 = *DAT_0801eb44 & 0xffdf;
    *puVar2 = *puVar2 | 0x80;
  }
  puVar2 = DAT_0801eb4c;
  if ((*DAT_0801eb48 != '\0') && (*(char *)(*(int *)(iVar1 + 0x1c) + 0x262) == '\x02')) {
    *DAT_0801eb4c = *DAT_0801eb4c & 0xffdf;
    *puVar2 = *puVar2 | 0x80;
  }
  uVar3 = DAT_0801eb54;
  if ((*DAT_0801eb50 != '\0') && (*(char *)(*(int *)(iVar1 + 0x1c) + 0x262) == '\x03')) {
    FUN_08020654(DAT_0801eb54,0x525,0);
    FUN_08020654(uVar3,0x727,1);
  }
  uVar3 = DAT_0801eb5c;
  if ((*DAT_0801eb58 != '\0') && (*(char *)(*(int *)(iVar1 + 0x1c) + 0x262) == '\x04')) {
    FUN_08020654(DAT_0801eb5c,0x525,0);
    FUN_08020654(uVar3,0x727,1);
  }
  uVar3 = DAT_0801eb64;
  if ((*DAT_0801eb60 != '\0') && (*(char *)(*(int *)(iVar1 + 0x1c) + 0x262) == '\x05')) {
    FUN_08020654(DAT_0801eb64,0x525,0);
    FUN_08020654(uVar3,0x727,1);
  }
  uVar3 = DAT_0801eb6c;
  if ((*DAT_0801eb68 != '\0') && (*(char *)(*(int *)(iVar1 + 0x1c) + 0x262) == '\x06')) {
    FUN_08020654(DAT_0801eb6c,0x525,0);
    FUN_08020654(uVar3,0x727,1);
  }
  *(undefined1 *)(iVar1 + 4) = 0;
  *(undefined2 *)(DAT_0801eb70 + 0x260) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801eb74 at 0x0801eb74
// ---------------------------------------------------------------------------

void FUN_0801eb74(void)

{
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801ed44 at 0x0801ed44
// ---------------------------------------------------------------------------

void FUN_0801ed44(void)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  undefined1 *puVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  
  iVar10 = DAT_0801ef74;
  iVar9 = DAT_0801ef70;
  if (((*(short *)(DAT_0801ef70 + 300) != 0) &&
      (*(short *)(DAT_0801ef70 + 300) == *(short *)(DAT_0801ef74 + 0xc))) &&
     (*(char *)(DAT_0801ef70 + 0x25c) != '\x01')) {
    *(short *)(DAT_0801ef70 + 0x25e) = *(short *)(DAT_0801ef70 + 0x25e) + 1;
  }
  iVar11 = DAT_0801ef78;
  if (((*(short *)(DAT_0801ef78 + 300) != 0) &&
      (*(short *)(DAT_0801ef78 + 300) == *(short *)(iVar10 + 0xe))) &&
     (*(char *)(DAT_0801ef78 + 0x25c) != '\x01')) {
    *(short *)(DAT_0801ef78 + 0x25e) = *(short *)(DAT_0801ef78 + 0x25e) + 1;
  }
  iVar12 = DAT_0801ef7c;
  if (((*(short *)(DAT_0801ef7c + 300) != 0) &&
      (*(short *)(DAT_0801ef7c + 300) == *(short *)(iVar10 + 0x10))) &&
     (*(char *)(DAT_0801ef7c + 0x25c) != '\x01')) {
    *(short *)(DAT_0801ef7c + 0x25e) = *(short *)(DAT_0801ef7c + 0x25e) + 1;
  }
  iVar13 = DAT_0801ef80;
  if (((*(short *)(DAT_0801ef80 + 300) != 0) &&
      (*(short *)(DAT_0801ef80 + 300) == *(short *)(iVar10 + 0x12))) &&
     (*(char *)(DAT_0801ef80 + 0x25c) != '\x01')) {
    *(short *)(DAT_0801ef80 + 0x25e) = *(short *)(DAT_0801ef80 + 0x25e) + 1;
  }
  iVar14 = DAT_0801ef84;
  if (((*(short *)(DAT_0801ef84 + 300) != 0) &&
      (*(short *)(DAT_0801ef84 + 300) == *(short *)(iVar10 + 0x14))) &&
     (*(char *)(DAT_0801ef84 + 0x25c) != '\x01')) {
    *(short *)(DAT_0801ef84 + 0x25e) = *(short *)(DAT_0801ef84 + 0x25e) + 1;
  }
  iVar15 = DAT_0801ef88;
  if (((*(short *)(DAT_0801ef88 + 300) != 0) &&
      (*(short *)(DAT_0801ef88 + 300) == *(short *)(iVar10 + 0x16))) &&
     (*(char *)(DAT_0801ef88 + 0x25c) != '\x01')) {
    *(short *)(DAT_0801ef88 + 0x25e) = *(short *)(DAT_0801ef88 + 0x25e) + 1;
  }
  iVar16 = DAT_0801ef8c;
  if (((*(short *)(DAT_0801ef8c + 300) != 0) &&
      (*(short *)(DAT_0801ef8c + 300) == *(short *)(iVar10 + 0x18))) &&
     (*(char *)(DAT_0801ef8c + 0x25c) != '\x01')) {
    *(short *)(DAT_0801ef8c + 0x25e) = *(short *)(DAT_0801ef8c + 0x25e) + 1;
  }
  iVar17 = DAT_0801ef90;
  if (((*(short *)(DAT_0801ef90 + 300) != 0) &&
      (*(short *)(DAT_0801ef90 + 300) == *(short *)(iVar10 + 0x1a))) &&
     (*(char *)(DAT_0801ef90 + 0x25c) != '\x01')) {
    *(short *)(DAT_0801ef90 + 0x25e) = *(short *)(DAT_0801ef90 + 0x25e) + 1;
  }
  if (*(short *)(iVar9 + 300) == 0) {
    *(short *)(iVar9 + 0x260) = *(short *)(iVar9 + 0x260) + 1;
  }
  if (*(short *)(iVar11 + 300) == 0) {
    *(short *)(iVar11 + 0x260) = *(short *)(iVar11 + 0x260) + 1;
  }
  if (*(short *)(iVar12 + 300) == 0) {
    *(short *)(iVar12 + 0x260) = *(short *)(iVar12 + 0x260) + 1;
  }
  if (*(short *)(iVar13 + 300) == 0) {
    *(short *)(iVar13 + 0x260) = *(short *)(iVar13 + 0x260) + 1;
  }
  if (*(short *)(iVar14 + 300) == 0) {
    *(short *)(iVar14 + 0x260) = *(short *)(iVar14 + 0x260) + 1;
  }
  if (*(short *)(iVar15 + 300) == 0) {
    *(short *)(iVar15 + 0x260) = *(short *)(iVar15 + 0x260) + 1;
  }
  if (*(short *)(iVar16 + 300) == 0) {
    *(short *)(iVar16 + 0x260) = *(short *)(iVar16 + 0x260) + 1;
  }
  if (*(short *)(iVar17 + 300) == 0) {
    *(short *)(iVar17 + 0x260) = *(short *)(iVar17 + 0x260) + 1;
  }
  *(undefined2 *)(iVar10 + 0xc) = *(undefined2 *)(iVar9 + 300);
  *(undefined2 *)(iVar10 + 0xe) = *(undefined2 *)(iVar11 + 300);
  *(undefined2 *)(iVar10 + 0x10) = *(undefined2 *)(iVar12 + 300);
  *(undefined2 *)(iVar10 + 0x12) = *(undefined2 *)(iVar13 + 300);
  *(undefined2 *)(iVar10 + 0x14) = *(undefined2 *)(iVar14 + 300);
  *(undefined2 *)(iVar10 + 0x16) = *(undefined2 *)(iVar15 + 300);
  *(undefined2 *)(iVar10 + 0x18) = *(undefined2 *)(iVar16 + 300);
  *(undefined2 *)(iVar10 + 0x1a) = *(undefined2 *)(iVar17 + 300);
  puVar1 = DAT_0801ed20;
  if (1 < *(ushort *)(DAT_0801ed20 + 0x25e)) {
    *(undefined2 *)(DAT_0801ed20 + 300) = 0;
    *(undefined2 *)(puVar1 + 0x25e) = 0;
    puVar1[0x25c] = 0;
    *puVar1 = 0;
  }
  puVar2 = DAT_0801ed24;
  if (1 < *(ushort *)(DAT_0801ed24 + 0x25e)) {
    *(undefined2 *)(DAT_0801ed24 + 300) = 0;
    *(undefined2 *)(puVar2 + 0x25e) = 0;
    puVar2[0x25c] = 0;
    *puVar2 = 0;
  }
  puVar3 = DAT_0801ed28;
  if (1 < *(ushort *)(DAT_0801ed28 + 0x25e)) {
    *(undefined2 *)(DAT_0801ed28 + 300) = 0;
    *(undefined2 *)(puVar3 + 0x25e) = 0;
    puVar3[0x25c] = 0;
    *puVar3 = 0;
  }
  puVar4 = DAT_0801ed2c;
  if (1 < *(ushort *)(DAT_0801ed2c + 0x25e)) {
    *(undefined2 *)(DAT_0801ed2c + 300) = 0;
    *(undefined2 *)(puVar4 + 0x25e) = 0;
    puVar4[0x25c] = 0;
    *puVar4 = 0;
  }
  puVar5 = DAT_0801ed30;
  if (1 < *(ushort *)(DAT_0801ed30 + 0x25e)) {
    *(undefined2 *)(DAT_0801ed30 + 300) = 0;
    *(undefined2 *)(puVar5 + 0x25e) = 0;
    puVar5[0x25c] = 0;
    *puVar5 = 0;
  }
  puVar6 = DAT_0801ed34;
  if (1 < *(ushort *)(DAT_0801ed34 + 0x25e)) {
    *(undefined2 *)(DAT_0801ed34 + 300) = 0;
    *(undefined2 *)(puVar6 + 0x25e) = 0;
    puVar6[0x25c] = 0;
    *puVar6 = 0;
  }
  puVar7 = DAT_0801ed38;
  if (1 < *(ushort *)(DAT_0801ed38 + 0x25e)) {
    *(undefined2 *)(DAT_0801ed38 + 300) = 0;
    *(undefined2 *)(puVar7 + 0x25e) = 0;
    puVar7[0x25c] = 0;
    *puVar7 = 0;
  }
  puVar8 = DAT_0801ed3c;
  if (1 < *(ushort *)(DAT_0801ed3c + 0x25e)) {
    *(undefined2 *)(DAT_0801ed3c + 300) = 0;
    *(undefined2 *)(puVar8 + 0x25e) = 0;
    puVar8[0x25c] = 0;
    *puVar8 = 0;
  }
  iVar9 = DAT_0801ed40;
  if ((*(char *)(DAT_0801ed40 + 2) == '\0') && (1000 < *(ushort *)(puVar1 + 0x260))) {
    *(undefined1 *)(DAT_0801ed40 + 2) = 1;
  }
  if ((*(char *)(iVar9 + 3) == '\0') && (1000 < *(ushort *)(puVar2 + 0x260))) {
    *(undefined1 *)(iVar9 + 3) = 1;
  }
  if ((*(char *)(iVar9 + 4) == '\0') && (1000 < *(ushort *)(puVar3 + 0x260))) {
    *(undefined1 *)(iVar9 + 4) = 1;
  }
  if ((*(char *)(iVar9 + 5) == '\0') && (1000 < *(ushort *)(puVar4 + 0x260))) {
    *(undefined1 *)(iVar9 + 5) = 1;
  }
  if ((*(char *)(iVar9 + 6) == '\0') && (1000 < *(ushort *)(puVar5 + 0x260))) {
    *(undefined1 *)(iVar9 + 6) = 1;
  }
  if ((*(char *)(iVar9 + 7) == '\0') && (1000 < *(ushort *)(puVar6 + 0x260))) {
    *(undefined1 *)(iVar9 + 7) = 1;
  }
  if ((*(char *)(iVar9 + 8) == '\0') && (1000 < *(ushort *)(puVar7 + 0x260))) {
    *(undefined1 *)(iVar9 + 8) = 1;
  }
  if ((*(char *)(iVar9 + 9) == '\0') && (1000 < *(ushort *)(puVar8 + 0x260))) {
    *(undefined1 *)(iVar9 + 9) = 1;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801ef94 at 0x0801ef94
// ---------------------------------------------------------------------------

void FUN_0801ef94(void)

{
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801efb8 at 0x0801efb8
// ---------------------------------------------------------------------------

undefined4 FUN_0801efb8(void)

{
  *(undefined1 *)(DAT_0801efcc + 3) = 1;
  FUN_08017ed8(0x4000,1);
  return 1;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801efd0 at 0x0801efd0
// ---------------------------------------------------------------------------

void FUN_0801efd0(void)

{
  uint *puVar1;
  uint *puVar2;
  int iVar3;
  
  puVar1 = DAT_0801f034;
  iVar3 = 0;
  *DAT_0801f034 = *DAT_0801f034 | 0x10000;
  puVar2 = DAT_0801f038;
  do {
    iVar3 = iVar3 + 1;
    if ((int)(*puVar1 << 0xe) < 0) break;
  } while (iVar3 != 0x8000);
  if (-1 < (int)(*puVar1 << 0xe)) {
    *DAT_0801f040 = DAT_0801f03c;
    return;
  }
  *DAT_0801f038 = *DAT_0801f038 & 0xfffffffc;
  *puVar2 = *puVar2;
  puVar1[1] = puVar1[1];
  puVar1[1] = puVar1[1];
  puVar1[1] = puVar1[1];
  puVar1[1] = puVar1[1] & 0xfffffffc;
  puVar1[1] = puVar1[1] | 1;
  do {
  } while ((puVar1[1] & 0xf) >> 2 != 1);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801f044 at 0x0801f044
// ---------------------------------------------------------------------------

void FUN_0801f044(undefined1 param_1)

{
  byte bVar1;
  undefined1 *puVar2;
  byte *pbVar3;
  char *pcVar4;
  byte *pbVar5;
  char *pcVar6;
  char *pcVar7;
  float fVar8;
  byte bVar9;
  uint uVar10;
  undefined4 uVar11;
  int iVar12;
  
  puVar2 = DAT_0801f304;
  *DAT_0801f304 = param_1;
  pcVar7 = DAT_0801f320;
  pcVar6 = DAT_0801f318;
  pbVar5 = DAT_0801f314;
  pcVar4 = DAT_0801f30c;
  pbVar3 = DAT_0801f308;
  bVar9 = DAT_0801f308[0x4d] != 0;
  if (DAT_0801f308[0x4c] != 0) {
    bVar9 = bVar9 | 2;
  }
  if ((*DAT_0801f30c == '\0') && (*DAT_0801f318 == '\0')) {
    if (-1 < (int)((uint)DAT_0801f308[0x39] << 0x1d)) {
LAB_0801f0ac:
      if (((((*DAT_0801f308 & 1) == 0) && (-1 < (int)((uint)DAT_0801f308[0x51] << 0x1d))) &&
          (*DAT_0801f310 == '\0')) && (*DAT_0801f314 == 0)) {
        bVar9 = bVar9 | 4;
      }
    }
  }
  else if ((-1 < (int)((uint)DAT_0801f308[0x39] << 0x1d)) && ((DAT_0801f308[0x12] & 0x13) == 0))
  goto LAB_0801f0ac;
  if ((*DAT_0801f30c == '\0') && (*DAT_0801f318 == '\0')) {
    if ((DAT_0801f308[0x39] & 3) != 0) goto LAB_0801f134;
    bVar1 = DAT_0801f308[0x1b];
  }
  else {
    bVar1 = DAT_0801f308[0x39];
  }
  if ((((bVar1 & 3) == 0) && (-1 < (int)((uint)*DAT_0801f308 << 0x1e))) &&
     ((-1 < (int)((uint)DAT_0801f308[0x51] << 0x1d) &&
      ((((DAT_0801f308[0x10] & 3) == 0 && (*DAT_0801f31c != '\x11')) && (*DAT_0801f320 == '\0'))))))
  {
    bVar9 = bVar9 | 8;
  }
LAB_0801f134:
  if ((*DAT_0801f324 != '\0') || (DAT_0801f308[0x44] != 0)) {
    bVar9 = bVar9 | 0x10;
  }
  if ((*DAT_0801f328 != '\0') || (DAT_0801f308[0x45] != 0)) {
    bVar9 = bVar9 | 0x20;
  }
  puVar2[1] = bVar9;
  bVar9 = *pcVar6 != '\0';
  if (*DAT_0801f32c != '\0') {
    bVar9 = bVar9 | 2;
  }
  if (pbVar3[0x3a] != 0) {
    bVar9 = bVar9 | 4;
  }
  if (pbVar3[0x3b] != 0) {
    bVar9 = bVar9 | 8;
  }
  if ((pbVar3[0x12] & 0x13) != 0) {
    bVar9 = bVar9 | 0x80;
  }
  if ((pbVar3[0x1b] & 3) != 0) {
    bVar9 = bVar9 | 0x40;
  }
  if (*pcVar4 != '\0') {
    bVar9 = bVar9 | 0x20;
  }
  if (*DAT_0801f330 != '\0') {
    bVar9 = bVar9 | 0x10;
  }
  puVar2[2] = bVar9;
  puVar2[3] = *(byte *)(DAT_0801f334 + 0x14) >> 1;
  iVar12 = DAT_0801f338;
  puVar2[4] = (char)*(undefined2 *)(DAT_0801f338 + 0x1e) + '(';
  puVar2[5] = (char)*(undefined2 *)(iVar12 + 0x22) + '(';
  puVar2[6] = *DAT_0801f33c << 6 | *DAT_0801f340 << 4 | *DAT_0801f344 < 2 | *pcVar7 == '\0' |
              *pbVar5;
  puVar2[7] = *DAT_0801f348 | *DAT_0801f34c << 4;
  FUN_0800a670(DAT_0801f304,8,0x102,0,4,0);
  fVar8 = DAT_0801f354;
  uVar11 = VectorFloatToUnsigned(*(float *)(DAT_0801f350 + 0x114) * DAT_0801f354,3);
  *puVar2 = (char)uVar11;
  puVar2[1] = (char)((uint)uVar11 >> 8);
  puVar2[2] = (char)((uint)uVar11 >> 0x10);
  puVar2[3] = (char)((uint)uVar11 >> 0x18);
  iVar12 = 0;
  if (pbVar3[0x3b] == 0) {
    if (pbVar3[0x3a] != 0) {
      iVar12 = VectorFloatToUnsigned(*(float *)(DAT_0801f358 + 0x14) * fVar8,3);
    }
  }
  else {
    uVar10 = VectorFloatToUnsigned(*(float *)(DAT_0801f358 + 0x10) * fVar8,3);
    iVar12 = ~uVar10 + 1;
  }
  puVar2[4] = (char)iVar12;
  puVar2[5] = (char)((uint)iVar12 >> 8);
  puVar2[6] = (char)((uint)iVar12 >> 0x10);
  puVar2[7] = (char)((uint)iVar12 >> 0x18);
  FUN_0800a670(DAT_0801f304,8,0x103,0,4);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801f35c at 0x0801f35c
// ---------------------------------------------------------------------------

undefined4 FUN_0801f35c(void)

{
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801f360 at 0x0801f360
// ---------------------------------------------------------------------------

void FUN_0801f360(void)

{
  float *pfVar1;
  int iVar2;
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  uint in_r3;
  uint local_10;
  
  FUN_08014fa4();
  FUN_08016148();
  FUN_08013a04();
  FUN_08013b48();
  FUN_08014f80();
  FUN_080158d0();
  FUN_080159b8();
  FUN_080153b8();
  FUN_08013374();
  FUN_080218b8();
  FUN_08015f28();
  FUN_08012984();
  pfVar1 = DAT_0801f458;
  local_10 = in_r3 & 0xffffff00;
  while ((local_10 & 0xff) < 10) {
    FUN_0801f8ac();
    FUN_0800e44c();
    FUN_08009144();
    if ((*pfVar1 < pfVar1[3]) && (2 < (local_10 & 0xff))) break;
    FUN_0800db18(0xfa);
    local_10 = CONCAT31(local_10._1_3_,(char)local_10 + '\x01');
  }
  FUN_08015a9c();
  FUN_08009144();
  iVar2 = DAT_0801f45c;
  if ((*(char *)(DAT_0801f45c + 0x4a) == '\0') || (*DAT_0801f460 != '\0')) {
    if (*DAT_0801f464 <= DAT_0801f464[3]) {
      *(byte *)(DAT_0801f45c + 0x12) = *(byte *)(DAT_0801f45c + 0x12) | 1;
    }
    else {
      FUN_0800acd8();
    }
  }
  else {
    FUN_0800ac9c();
  }
  if (pfVar1[3] <= *pfVar1) {
    *(byte *)(iVar2 + 0x1b) = *(byte *)(iVar2 + 0x1b) | 1;
  }
  else {
    FUN_08015844();
    FUN_0800c940();
  }
  FUN_08014698();
  FUN_08019844(0,4);
  FUN_080196d0(0x1ea,extraout_r1,extraout_r2,local_10);
  return;
}



// ---------------------------------------------------------------------------
// Function: SysTick_Handler at 0x0801f468
// ---------------------------------------------------------------------------

void SysTick_Handler(void)

{
  FUN_0801fbcc();
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801f478 at 0x0801f478
// ---------------------------------------------------------------------------

void FUN_0801f478(void)

{
  SystemInit();
  FUN_08017df0(0x12);
  DAT_e000e014 = DAT_0801f4a0;
  *(undefined1 *)(DAT_0801f4a4 + 0xd14) = 0xf0;
  DAT_e000e018 = 0;
  DAT_e000e010 = 7;
  return;
}



// ---------------------------------------------------------------------------
// Function: SystemInit at 0x0801f4a8
// ---------------------------------------------------------------------------

void SystemInit(void)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  FUN_080159e4();
  *DAT_0801f558 = *DAT_0801f558 | 0xf00000;
  puVar1 = DAT_0801f55c;
  *DAT_0801f55c = *DAT_0801f55c | 1;
  puVar1[1] = puVar1[1] & DAT_0801f560;
  *puVar1 = *puVar1 & DAT_0801f564;
  *puVar1 = *puVar1 & 0xfffbffff;
  puVar1[1] = puVar1[1] & DAT_0801f568;
  puVar1[0xb] = 0;
  puVar1[0xc] = 0;
  puVar1[2] = 0x9f0000;
  puVar1[7] = puVar1[7] | 0x10000000;
  iVar2 = DAT_0801f56c;
  *(uint *)(DAT_0801f56c + 0xc) = *(uint *)(DAT_0801f56c + 0xc) | 1;
  puVar1[7] = puVar1[7] & 0xefffffff;
  *DAT_0801f570 = *DAT_0801f570 | 0x90;
  FUN_0801efd0();
  if (*(int *)(DAT_0801f574 + 0x298) != DAT_0801f578) {
    puVar1[7] = puVar1[7] | 0x10000000;
    uVar3 = (*DAT_0801f57c & 0x1fffffff) >> 0x18;
    uVar4 = *(uint *)(iVar2 + 0xc) & 0xfffffc1f;
    if (uVar3 + 1 < 0x1e) {
      uVar4 = uVar4 | (uVar3 + 2) * 0x20;
    }
    else {
      uVar4 = uVar4 | 0x3e0;
    }
    *(uint *)(iVar2 + 0xc) = uVar4;
    puVar1[7] = puVar1[7] & 0xefffffff;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801f580 at 0x0801f580
// ---------------------------------------------------------------------------

void FUN_0801f580(void)

{
  char cVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  float local_18;
  float local_14;
  
  FUN_08016a60();
  if (*DAT_0801f634 != '\0') {
    FUN_080218b8();
  }
  iVar4 = DAT_0801f63c;
  iVar3 = DAT_0801f638;
  if (*(char *)(DAT_0801f638 + 0x3d) == '\0') {
    *(undefined1 *)(DAT_0801f63c + 0x13) = 1;
  }
  else {
    *(undefined1 *)(DAT_0801f63c + 0x13) = 8;
  }
  if ((*DAT_0801f640 == '\0') || (*(char *)(iVar3 + 0x3f) == '\0')) {
    *(char *)(iVar4 + 1) = *(char *)(iVar4 + 1) + '\x01';
    if (*(byte *)(iVar4 + 0x13) <= *(byte *)(iVar4 + 1)) {
      *(undefined1 *)(iVar4 + 1) = 0;
      FUN_08009144();
    }
  }
  else {
    *(undefined1 *)(iVar4 + 1) = 0;
  }
  if ((*(char *)(iVar3 + 0x3a) == '\0') && (*(char *)(iVar3 + 0x3b) == '\0')) {
    FUN_0800bcc4();
  }
  if ((*(char *)(iVar3 + 0x3a) == '\0') && (*(char *)(iVar3 + 0x3b) == '\0')) {
    if (*DAT_0801f648 == '\0') {
      *(undefined1 *)(iVar3 + 0x3e) = 0;
    }
  }
  else if (*(char *)(iVar3 + 0x3e) == '\0') {
    *(undefined1 *)(iVar3 + 0x3e) = 1;
  }
  FUN_0800c718();
  FUN_08020858();
  FUN_080128d0();
  FUN_0800ad9c();
  FUN_0800c9d4();
  FUN_0801f842();
  if ((*DAT_0801f64c != '\0') && (*(char *)(DAT_0801f650 + 0x16) == '\x01')) {
    FUN_0800b8dc();
  }
  iVar3 = DAT_0801715c;
  fVar2 = DAT_08017150;
  if (*DAT_08017138 == '\x01') {
    return;
  }
  if (*DAT_0801713c == '\x01') {
    return;
  }
  if (*DAT_08017140 == '\x01') {
    return;
  }
  if (*DAT_08017144 == '\x01') {
    return;
  }
  if (*DAT_08017148 == '\x01') {
    return;
  }
  if (*DAT_0801714c == '\0') {
    return;
  }
  local_18 = DAT_08017150;
  local_14 = DAT_08017150;
  cVar1 = *DAT_08017154;
  if (cVar1 == '\0') {
    *(undefined1 *)(DAT_08017158 + 3) = 0;
    if (*(char *)(iVar3 + 0x4c) != '\0') {
      FUN_0800c8f4();
    }
    if (*(char *)(iVar3 + 0x4d) == '\0') {
      return;
    }
  }
  else {
    if (cVar1 != '\x01') {
      if (cVar1 == '\x02') {
        if (*(char *)(DAT_0801715c + 0x4c) != '\x01') {
          FUN_0800c940();
        }
        if (*(char *)(iVar3 + 0x4d) == '\x01') {
          return;
        }
        FUN_0800acd8();
        return;
      }
      if (cVar1 != '\x03') {
        return;
      }
      *(undefined1 *)(DAT_08017158 + 3) = 0;
      if (*(char *)(iVar3 + 0x4d) != '\x01') {
        FUN_0800acd8();
      }
      if (*(char *)(iVar3 + 0x4c) == '\0') {
        return;
      }
      FUN_08018574(&local_14);
      if (local_14 < 0.0) {
        local_14 = fVar2;
      }
      if (*DAT_08017160 <= local_14) {
        return;
      }
      FUN_0800c8f4();
      return;
    }
    *(undefined1 *)(DAT_08017158 + 3) = 0;
    if (*(char *)(iVar3 + 0x4c) != '\x01') {
      FUN_0800c940();
    }
    if (*(char *)(iVar3 + 0x4d) == '\0') {
      return;
    }
    FUN_08018574(&local_18);
    if (0.0 < local_18) {
      local_18 = fVar2;
    }
    local_18 = -local_18;
    if (*DAT_08017164 <= local_18) {
      return;
    }
  }
  FUN_0800ac9c();
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801f654 at 0x0801f654
// ---------------------------------------------------------------------------

void FUN_0801f654(void)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  
  FUN_0801f8ac();
  if ((*(char *)(DAT_0801f6c0 + 0x3a) != '\0') || (*(char *)(DAT_0801f6c0 + 0x3b) != '\0')) {
    FUN_0800bcc4();
  }
  FUN_08008d40();
  if (*DAT_0801f6c4 == '\x01') {
    FUN_0800f218();
  }
  if (*DAT_0801f6c8 == '\x01') {
    FUN_08017168();
  }
  FUN_08017580();
  FUN_0800f0f0();
  FUN_080192fc();
  FUN_0800f670();
  FUN_0801f860();
  FUN_08019120();
  FUN_0800f480();
  FUN_0800aa68();
  FUN_0800cb70();
  FUN_08017844();
  FUN_0801953c();
  FUN_0800afbc();
  iVar6 = DAT_080097a0;
  fVar5 = DAT_0800979c;
  fVar4 = DAT_08009798;
  pfVar3 = DAT_08009794;
  iVar2 = DAT_08009790;
  iVar1 = DAT_0800978c;
  if (*(char *)(DAT_0800978c + 1) == '\x01') {
    *(undefined2 *)(DAT_0800978c + 6) = 0;
  }
  else {
    if (((*(char *)(DAT_08009790 + 0x4c) != '\0') || (*(char *)(DAT_08009790 + 0x3b) == '\0')) ||
       (DAT_0800979c / (*DAT_08009794 * DAT_08009798) <= *(float *)(DAT_080097a0 + 0x10))) {
      *(undefined2 *)(DAT_0800978c + 6) = 0;
    }
    else {
      *(short *)(DAT_0800978c + 6) = *(short *)(DAT_0800978c + 6) + 1;
      if (*(ushort *)(iVar1 + 4) <= *(ushort *)(iVar1 + 6)) {
        *(undefined2 *)(iVar1 + 6) = 0;
        FUN_0800c400();
      }
    }
    if ((*(char *)(iVar2 + 0x3a) != '\0') && (*(float *)(iVar6 + 0x14) < fVar5 / (*pfVar3 * fVar4)))
    {
      if (*(char *)(iVar2 + 0x4d) != '\0') {
        return;
      }
      *(undefined2 *)(iVar1 + 8) = 0;
      *(short *)(iVar1 + 10) = *(short *)(iVar1 + 10) + 1;
      if (*(ushort *)(iVar1 + 10) < *(ushort *)(iVar1 + 4)) {
        return;
      }
      *(undefined2 *)(iVar1 + 10) = 0;
      FUN_0800c400();
      return;
    }
  }
  *(undefined2 *)(iVar1 + 8) = 0;
  *(undefined2 *)(iVar1 + 10) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801f6cc at 0x0801f6cc
// ---------------------------------------------------------------------------

void FUN_0801f6cc(void)

{
  int iVar1;
  
  iVar1 = DAT_0801f768;
  if (*(char *)(DAT_0801f764 + 0x3d) != '\0') {
    if (*(byte *)(DAT_0801f768 + 0x26) < 4) {
      *(char *)(DAT_0801f768 + 0x26) = *(char *)(DAT_0801f768 + 0x26) + '\x01';
      goto LAB_0801f716;
    }
    *(undefined1 *)(DAT_0801f768 + 0x26) = 1;
  }
  FUN_0801fc8c();
  FUN_08016790();
  FUN_0800af2c();
  FUN_0800caa4();
  FUN_080136a4();
  FUN_0800f070();
  FUN_0800a03c();
  FUN_0801953e();
  FUN_0801f88a();
LAB_0801f716:
  if (((int)(*(float *)(DAT_0801f76c + 0xc) - *(float *)(DAT_0801f770 + 0xc)) < 0x3f800001) &&
     (*(short *)(DAT_0801f774 + 0x1e) < 0x78)) {
    *(undefined2 *)(iVar1 + 0x4c) = 0;
    return;
  }
  *(short *)(iVar1 + 0x4c) = *(short *)(iVar1 + 0x4c) + 1;
  if (0x5460 < *(ushort *)(iVar1 + 0x4c)) {
    *(undefined2 *)(iVar1 + 0x4c) = 0;
    *DAT_0801f778 = 1;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801f77c at 0x0801f77c
// ---------------------------------------------------------------------------

void FUN_0801f77c(void)

{
  if (*DAT_0801f7ac != '\0') {
    if (*(char *)(DAT_0801f7b0 + 0x16) == '\0') {
      FUN_0800b8dc();
    }
    FUN_08008af4();
  }
  FUN_08008c6c();
  FUN_0801eb74();
  FUN_0801ca54();
  FUN_0801f89c();
  *DAT_0801f7b4 = 0xaaaa;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801f7b8 at 0x0801f7b8
// ---------------------------------------------------------------------------

void FUN_0801f7b8(void)

{
  int iVar1;
  
  iVar1 = DAT_0801f800;
  if (*(char *)(DAT_0801f7fc + 0x3d) == '\0') {
    *(short *)(DAT_0801f800 + 10) = *(short *)(DAT_0801f800 + 10) + 1;
    if (1000 < *(ushort *)(iVar1 + 10)) {
      *(undefined2 *)(iVar1 + 10) = 0;
      if (*(short *)(iVar1 + 0x10) == *(short *)(iVar1 + 8)) {
        FUN_0800db18(0x14);
        if (*(short *)(iVar1 + 0x10) == *(short *)(iVar1 + 8)) {
          FUN_080161bc(0);
        }
      }
      *(undefined2 *)(iVar1 + 0x10) = *(undefined2 *)(iVar1 + 8);
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: TIM1_CC_IRQHandler at 0x0801f804
// ---------------------------------------------------------------------------

undefined4 TIM1_CC_IRQHandler(void)

{
  FUN_0801f838(0x40000000);
  return 0x40000000;
}



// ---------------------------------------------------------------------------
// Function: TIM2_IRQHandler at 0x0801f81c
// ---------------------------------------------------------------------------

undefined4 TIM2_IRQHandler(void)

{
  undefined4 uVar1;
  
  uVar1 = DAT_0801f834;
  FUN_0801f838(DAT_0801f834,1);
  return uVar1;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801f838 at 0x0801f838
// ---------------------------------------------------------------------------

void FUN_0801f838(int param_1,uint param_2)

{
  *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) & ~param_2;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801f842 at 0x0801f842
// ---------------------------------------------------------------------------

void FUN_0801f842(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  char cVar4;
  undefined4 uVar5;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  FUN_08010f38();
  FUN_0800c520();
  FUN_0800c58c();
  FUN_0800fd3c();
  FUN_0800ff5c();
  iVar2 = DAT_0802173c;
  if ((((*DAT_08021738 == '\x01') || (*DAT_08021740 == '\x01')) && (*DAT_08021744 == '\0')) &&
     (*(char *)(DAT_0802173c + 6) != '\0')) {
    local_18._0_2_ = CONCAT11(0x1f,*(undefined1 *)(DAT_0802173c + 6));
    local_18._0_3_ = CONCAT12(0x40,(undefined2)local_18);
    local_18 = CONCAT13(1,(undefined3)local_18);
    local_14 = CONCAT13(1,CONCAT12(0x40,(undefined2)local_18));
    FUN_0801b55c(local_14);
    FUN_0800db18(2);
    local_18 = CONCAT13(2,(undefined3)local_18);
    local_14 = CONCAT13(2,(undefined3)local_18);
    FUN_0801b764(local_14);
    *(char *)(iVar2 + 0xd) = *(char *)(iVar2 + 0xd) + '\x01';
    if (9 < *(byte *)(iVar2 + 0xd)) {
      *(undefined1 *)(iVar2 + 0xd) = 0;
      local_18 = CONCAT13(0x10,(undefined3)local_18);
      local_14 = CONCAT13(0x10,(undefined3)local_18);
      FUN_0801ba30(local_14);
      FUN_0800db18(2);
      local_18 = CONCAT13(0x11,(undefined3)local_18);
      local_14 = CONCAT13(0x11,(undefined3)local_18);
      FUN_0801badc(local_14);
      FUN_0800db18(2);
      local_18 = CONCAT13(0x12,(undefined3)local_18);
      local_14 = CONCAT13(0x12,(undefined3)local_18);
      FUN_0801bc04(local_14);
      FUN_0800fd60();
      local_1c = 0;
      local_18 = 0;
      if (*DAT_0801aeb0 != '\x01') {
        cVar4 = FUN_08010edc();
        uVar5 = local_1c;
        puVar1 = DAT_0801aec4;
        local_1c = CONCAT31(local_1c._1_3_,cVar4);
        uVar3 = local_1c;
        if (*(char *)(DAT_0801aeb4 + 0x2f) != '\0') {
          local_18 = local_18 | 1;
        }
        if (*(char *)(DAT_0801aeb4 + 0x25) != '\0') {
          local_18 = local_18 | 2;
        }
        if (*(char *)(DAT_0801aeb4 + 0x34) != '\0') {
          local_18 = local_18 | 4;
        }
        if (*(char *)(DAT_0801aeb4 + 0x2a) != '\0') {
          local_18 = local_18 | 8;
        }
        if (*(char *)(DAT_0801aeb8 + 8) != '\0') {
          local_18 = local_18 | 0x10;
        }
        if ((*(byte *)(DAT_0801aeb4 + 0x39) & 1) != 0) {
          local_18 = local_18 | 0x400;
        }
        if (((int)((uint)*(byte *)(DAT_0801aeb4 + 0x39) << 0x1e) < 0) && (*DAT_0801aebc == '\x01'))
        {
          local_18 = local_18 | 0x1000;
        }
        if (((int)((uint)*(byte *)(DAT_0801aeb4 + 0x39) << 0x1e) < 0) && (*DAT_0801aebc == '\x02'))
        {
          local_18 = local_18 | 0x2000;
        }
        if ((int)((uint)*(byte *)(DAT_0801aeb4 + 0x39) << 0x1d) < 0) {
          local_18 = local_18 | 0x4000;
        }
        if ((*(byte *)(DAT_0801aeb4 + 0x39) & 1) != 0) {
          local_18 = local_18 | 0x8000;
        }
        if ((~*(byte *)(DAT_0801aeb4 + 7) & 0x11) == 0) {
          local_18 = local_18 | 0x10000;
        }
        if ((~*(byte *)(DAT_0801aeb4 + 7) & 0x21) == 0) {
          local_18 = local_18 | 0x20000;
        }
        if ((~*(byte *)(DAT_0801aeb4 + 8) & 0x11) == 0) {
          local_18 = local_18 | 0x40000;
        }
        if ((~*(byte *)(DAT_0801aeb4 + 8) & 0x21) == 0) {
          local_18 = local_18 | 0x80000;
        }
        if (*(char *)(DAT_0801aeb4 + 0x11) != '\0') {
          local_18 = local_18 | 0x100000;
        }
        if (*(char *)(DAT_0801aeb8 + 9) != '\0') {
          local_18 = local_18 | 0x200000;
        }
        if (*(char *)(DAT_0801aeb8 + 10) != '\0') {
          local_18 = local_18 | 0x400000;
        }
        if (*(char *)(DAT_0801aeb4 + 0x45) != '\0') {
          local_18 = local_18 | 0x1000000;
        }
        if (*(char *)(DAT_0801aeb4 + 0x44) != '\0') {
          local_18 = local_18 | 0x2000000;
        }
        if (*(char *)(DAT_0801aeb4 + 0x46) != '\0') {
          local_18 = local_18 | 0x8000000;
        }
        if (*(char *)(DAT_0801aeb8 + 0xb) != '\0') {
          local_18 = local_18 | 0x10000000;
        }
        if (*(char *)(DAT_0801aeb4 + 0x47) != '\0') {
          local_18 = local_18 | 0x20000000;
        }
        if (((((cVar4 == '\0') && (local_1c._3_1_ = SUB41(uVar5,3), local_1c._3_1_ == '\0')) &&
             ((char)local_18 == '\0')) && ((local_18._1_1_ == '\0' && (local_18._2_1_ == '\0')))) &&
           (local_18._3_1_ == '\0')) {
          *(undefined1 *)DAT_0801aec4 = *DAT_0801aec0;
          *(undefined1 *)((int)puVar1 + 1) = 0x1f;
          *(undefined1 *)((int)puVar1 + 2) = 0xe;
          *(undefined1 *)((int)puVar1 + 3) = 0;
        }
        else {
          *(undefined1 *)DAT_0801aec4 = *DAT_0801aec0;
          *(undefined1 *)((int)puVar1 + 1) = 0x1f;
          *(undefined1 *)((int)puVar1 + 2) = 0xe;
          *(undefined1 *)((int)puVar1 + 3) = 5;
        }
        local_1c = uVar3;
        uVar5 = FUN_0801ef94(*puVar1);
        FUN_08023084(&local_1c,8,uVar5,0,4);
      }
      return;
    }
  }
  else {
    *(undefined1 *)(DAT_0802173c + 0xc) = 0;
    *(undefined1 *)(iVar2 + 0xd) = 0;
    *(undefined1 *)(iVar2 + 7) = 0;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801f860 at 0x0801f860
// ---------------------------------------------------------------------------

void FUN_0801f860(void)

{
  char *pcVar1;
  int iVar2;
  
  FUN_0801796c();
  FUN_0800ff04();
  FUN_0801a848();
  FUN_080090c4();
  FUN_0801647c();
  FUN_080109cc();
  FUN_0800fd60();
  FUN_08010f14();
  iVar2 = DAT_0800c25c;
  pcVar1 = DAT_0800c258;
  if ((*DAT_0800c258 == '\x02') || (*DAT_0800c258 == '\x03')) {
    *(char *)(DAT_0800c25c + 0x35) = *(char *)(DAT_0800c25c + 0x35) + '\x01';
    if (4 < *(byte *)(iVar2 + 0x35)) {
      *(undefined1 *)(iVar2 + 0x35) = 0;
      *pcVar1 = '\0';
      return;
    }
  }
  else {
    *(undefined1 *)(DAT_0800c25c + 0x35) = 0;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801f88a at 0x0801f88a
// ---------------------------------------------------------------------------

void FUN_0801f88a(void)

{
  FUN_080097a4();
  FUN_0800fc48();
  FUN_080207fc();
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801f89c at 0x0801f89c
// ---------------------------------------------------------------------------

void FUN_0801f89c(void)

{
  FUN_08011474();
  FUN_08016360();
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801f8ac at 0x0801f8ac
// ---------------------------------------------------------------------------

void FUN_0801f8ac(void)

{
  byte *pbVar1;
  undefined1 *puVar2;
  char *pcVar3;
  undefined1 *puVar4;
  byte *pbVar5;
  int iVar6;
  undefined2 uVar7;
  int iVar8;
  undefined1 *puVar9;
  byte bVar10;
  short sStack_58;
  undefined1 auStack_56 [38];
  byte local_30;
  ushort local_2c;
  char local_28;
  
  pbVar1 = DAT_0801fb04;
  if ((((*DAT_0801fafc != '\0') || (*DAT_0801fb00 != '\0')) || (DAT_0801fb00[0x10] != '\0')) ||
     ((DAT_0801fb00[0x51] != '\0' || (DAT_0801fb00[0x3d] == '\0')))) {
    iVar8 = FUN_08009bd8(auStack_56,*DAT_0801fb04);
    pbVar5 = DAT_0801fb14;
    puVar4 = DAT_0801fb10;
    pcVar3 = DAT_0801fb0c;
    puVar2 = DAT_0801fb08;
    if (iVar8 == 0) {
      *DAT_0801fb08 = 1;
    }
    else {
      for (local_30 = 1; iVar8 = DAT_0801fb38, local_30 <= *pbVar5; local_30 = local_30 + 1) {
        if ((*pbVar1 < local_30) && ((*pcVar3 == '\0' || (*pbVar5 < local_30)))) {
          local_28 = local_30 - (*pcVar3 + *pbVar1);
          switch(local_28) {
          default:
            puVar9 = puVar4;
            break;
          case '\x02':
            puVar9 = DAT_0801fb18;
            break;
          case '\x03':
            puVar9 = DAT_0801fb1c;
            break;
          case '\x04':
            puVar9 = DAT_0801fb20;
            break;
          case '\x05':
            puVar9 = DAT_0801fb24;
            break;
          case '\x06':
            puVar9 = DAT_0801fb28;
            break;
          case '\a':
            puVar9 = DAT_0801fb2c;
            break;
          case '\b':
            puVar9 = DAT_0801fb30;
          }
          uVar7 = FUN_08016cfc(*puVar9);
          *(undefined2 *)(auStack_56 + (uint)local_30 * 2 + -2) = uVar7;
        }
      }
      local_2c = 0;
      if (*DAT_0801fb34 == '\x01') {
        uVar7 = FUN_08016cfc(*DAT_0801fb3c);
        *(undefined2 *)(iVar8 + 0x118) = uVar7;
      }
      iVar6 = DAT_0801fb44;
      if (*DAT_0801fb40 == '\x01') {
        uVar7 = FUN_08016cfc(*DAT_0801fb48);
        *(undefined2 *)(iVar6 + 0x40) = uVar7;
      }
      if ((*DAT_0801fb4c == '\x01') && (*DAT_0801fb50 != '\0')) {
        for (local_30 = 1; local_30 <= *pbVar5; local_30 = local_30 + 1) {
          if ((*(short *)(auStack_56 + (uint)local_30 * 2 + -2) < 0x19) &&
             (10 < (int)*(short *)(iVar8 + 0x118) -
                   (int)*(short *)(auStack_56 + (uint)local_30 * 2 + -2))) {
            *(undefined2 *)(iVar8 + (uint)local_30 * 2 + 0x100) = *(undefined2 *)(iVar8 + 0x118);
            local_2c = (ushort)(1 << local_30) | local_2c;
          }
          else {
            *(undefined2 *)(iVar8 + (uint)local_30 * 2 + 0x100) =
                 *(undefined2 *)(auStack_56 + (uint)local_30 * 2 + -2);
          }
        }
        *(ushort *)(puVar2 + 0xe) = local_2c;
      }
      else {
        for (local_30 = 1; local_30 <= *pbVar5; local_30 = local_30 + 1) {
          *(undefined2 *)(iVar8 + (uint)local_30 * 2 + 0x100) =
               *(undefined2 *)(auStack_56 + (uint)local_30 * 2 + -2);
        }
      }
      *(undefined2 *)(iVar6 + 0x1e) = *(undefined2 *)(iVar8 + 0x102);
      *(undefined2 *)(iVar6 + 0x22) = *(undefined2 *)(iVar8 + 0x102);
      *(undefined1 *)(iVar6 + 0x20) = 1;
      *(undefined1 *)(iVar6 + 0x24) = 1;
      for (bVar10 = 2; bVar10 <= *pbVar5; bVar10 = bVar10 + 1) {
        if (*(short *)(iVar8 + (uint)bVar10 * 2 + 0x100) < *(short *)(iVar6 + 0x22)) {
          *(undefined2 *)(iVar6 + 0x22) = *(undefined2 *)(iVar8 + (uint)bVar10 * 2 + 0x100);
          *(byte *)(iVar6 + 0x24) = bVar10;
        }
        if (*(short *)(iVar6 + 0x1e) < *(short *)(iVar8 + (uint)bVar10 * 2 + 0x100)) {
          *(undefined2 *)(iVar6 + 0x1e) = *(undefined2 *)(iVar8 + (uint)bVar10 * 2 + 0x100);
          *(byte *)(iVar6 + 0x20) = bVar10;
        }
      }
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801fbcc at 0x0801fbcc
// ---------------------------------------------------------------------------

void FUN_0801fbcc(void)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = DAT_0801fc70;
  *(short *)(DAT_0801fc70 + 4) = *(short *)(DAT_0801fc70 + 4) + 1;
  *(short *)(iVar2 + 6) = *(short *)(iVar2 + 6) + 1;
  *(short *)(iVar2 + 8) = *(short *)(iVar2 + 8) + 1;
  iVar3 = DAT_0801fc78;
  iVar2 = DAT_0801fc74;
  if (*(char *)(DAT_0801fc74 + 0x15) != '\0') {
    *(short *)(DAT_0801fc78 + 0x12) = *(short *)(DAT_0801fc78 + 0x12) + 1;
  }
  if (*(char *)(iVar2 + 0x16) != '\0') {
    *(short *)(iVar3 + 0x14) = *(short *)(iVar3 + 0x14) + 1;
  }
  iVar4 = DAT_0801fc7c;
  if (*(char *)(iVar2 + 0x1e) != '\0') {
    *(short *)(DAT_0801fc7c + 0x12) = *(short *)(DAT_0801fc7c + 0x12) + 1;
  }
  if (*(char *)(iVar2 + 0x1f) != '\0') {
    *(short *)(iVar4 + 0x14) = *(short *)(iVar4 + 0x14) + 1;
  }
  if (*(char *)(iVar2 + 0x19) != '\0') {
    *(short *)(iVar3 + 0x24) = *(short *)(iVar3 + 0x24) + 1;
  }
  if (*(char *)(iVar2 + 0x1a) != '\0') {
    *(short *)(iVar3 + 0x26) = *(short *)(iVar3 + 0x26) + 1;
  }
  if (*(char *)(iVar2 + 0x23) != '\0') {
    *(short *)(iVar4 + 0x24) = *(short *)(iVar4 + 0x24) + 1;
  }
  if (*(char *)(iVar2 + 0x24) != '\0') {
    *(short *)(iVar4 + 0x26) = *(short *)(iVar4 + 0x26) + 1;
  }
  iVar3 = DAT_0801fc80;
  if (*(char *)(iVar2 + 0x3f) != '\0') {
    *(short *)(DAT_0801fc80 + 0x10) = *(short *)(DAT_0801fc80 + 0x10) + 1;
    *(short *)(iVar3 + 0x20) = *(short *)(iVar3 + 0x20) + 1;
    *(short *)(iVar3 + 0x22) = *(short *)(iVar3 + 0x22) + 1;
  }
  if (*DAT_0801fc84 != '\0') {
    *(int *)(DAT_0801fc84 + 4) = *(int *)(DAT_0801fc84 + 4) + 1;
  }
  FUN_0801ed44();
  puVar1 = DAT_0800f0ec;
  if (*(char *)(DAT_0800f0e8 + 0x3e) != '\0') {
    *(short *)(DAT_0800f0ec + 4) = *(short *)(DAT_0800f0ec + 4) + 1;
    if (9 < *(ushort *)(puVar1 + 4)) {
      *(undefined2 *)(puVar1 + 4) = 0;
      *puVar1 = 1;
    }
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0801fc8c at 0x0801fc8c
// ---------------------------------------------------------------------------

void FUN_0801fc8c(undefined4 param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  float *pfVar5;
  float *pfVar6;
  int iVar7;
  uint *puVar8;
  byte extraout_r1;
  byte bVar9;
  int extraout_r2;
  uint in_fpscr;
  float fVar10;
  uint uVar11;
  undefined8 uVar12;
  
  iVar4 = DAT_0801fe1c;
  iVar2 = DAT_0801fe18;
  uVar3 = DAT_0801fe14;
  uVar1 = *(undefined1 *)(DAT_0801fe18 + 0x3d);
  *(undefined2 *)(DAT_0801fe1c + 0x20) = 900;
  iVar7 = DAT_0801fe24;
  pfVar5 = DAT_0801fe20;
  fVar10 = *DAT_0801fe20;
  if (((int)fVar10 < DAT_0801fe24) || (fVar10 = DAT_0801fe20[1], (uint)fVar10 < 2)) {
    FUN_0801375c(fVar10,uVar1,param_3,param_4,param_3 & 0xffff0000,uVar3);
    FUN_08015844();
    puVar8 = DAT_0801fe28;
    if (((int)*pfVar5 < iVar7) || ((uint)pfVar5[1] < 2)) {
      pfVar5[1] = (float)(*DAT_0801fe28 / 100);
      fVar10 = (float)VectorUnsignedToFloat((int)pfVar5[1] * 100,(byte)(in_fpscr >> 0x16) & 3);
      *pfVar5 = fVar10;
      uVar12 = FUN_08008548(*puVar8);
      FUN_08008364((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),(int)DAT_0801fe2c,
                   (int)((ulonglong)DAT_0801fe2c >> 0x20));
      fVar10 = (float)FUN_08008562();
      pfVar5[2] = fVar10;
      FUN_08015844();
      FUN_0801975c();
    }
  }
  if (*(byte *)((int)pfVar5 + 0x12) >> 1 != *(byte *)(iVar4 + 7) >> 1) {
    *(undefined1 *)(iVar4 + 7) = *(undefined1 *)((int)pfVar5 + 0x12);
    FUN_0801975c();
  }
  if (((*(char *)(iVar2 + 0x3a) == '\0') && (*(char *)(iVar2 + 0x3b) == '\0')) &&
     (*(char *)((int)pfVar5 + 0x12) != -0x38)) {
    fVar10 = (float)VectorSignedToFloat(pfVar5[2],(byte)(in_fpscr >> 0x16) & 3);
    in_fpscr = in_fpscr & 0xfffffff;
    if (*pfVar5 == fVar10) {
      *(undefined1 *)((int)pfVar5 + 0x12) = 200;
      *(undefined1 *)((int)pfVar5 + 0x13) = 200;
      *(undefined1 *)(pfVar5 + 5) = 200;
    }
  }
  fVar10 = (float)FUN_0801a020();
  if (*(char *)(iVar2 + 0x3a) == '\0') {
    *(short *)(iVar4 + 0x1e) = *(short *)(iVar4 + 0x1e) + 1;
  }
  else {
    *(undefined2 *)(iVar4 + 0x1e) = 0;
  }
  pfVar6 = DAT_0801fe20;
  if (0x4a < *(ushort *)(iVar4 + 0x1e)) {
    *(undefined2 *)(iVar4 + 0x1e) = 0;
    *(float *)(iVar4 + 0x60) = (fVar10 + pfVar6[0x18] * *pfVar5) / 12.0 + *(float *)(iVar4 + 0x60);
    uVar11 = VectorFloatToUnsigned(*(undefined4 *)(iVar4 + 0x60),3);
    fVar10 = (float)VectorUnsignedToFloat(uVar11 & 0xffff,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(iVar4 + 0x60) = *(float *)(iVar4 + 0x60) - fVar10;
    if (0 < (int)pfVar5[2]) {
      pfVar5[2] = (float)((int)pfVar5[2] - (uVar11 & 0xffff));
    }
    pfVar5[3] = (float)((int)pfVar5[3] + (uVar11 & 0xffff));
    *(undefined1 *)((int)pfVar6 + 0x3a) = 1;
  }
  if (*(char *)((int)pfVar6 + 0x3a) != '\0') {
    *(undefined1 *)((int)pfVar6 + 0x3a) = 0;
    FUN_0800b460();
  }
  FUN_080193a4();
  FUN_0800bbac();
  FUN_0800aa10();
  FUN_080189d8();
  iVar2 = DAT_08019108;
  if ((*DAT_080190fc != '\0') && (*DAT_08019104 == '\x01')) {
    if (DAT_080190fc[7] != '\x02') {
      if (DAT_08019114 < (int)(*(float *)(DAT_0801910c + 0xc) - *(float *)(DAT_08019110 + 0xc))) {
        return;
      }
      if ((*(char *)(DAT_08019100 + 0x3b) == '\0') && (*(char *)(DAT_08019100 + 0x3a) == '\0')) {
        *(short *)(DAT_08019108 + 0x2a) = *(short *)(DAT_08019108 + 0x2a) + 1;
        if (*(ushort *)(iVar2 + 0x2a) < 900) {
          return;
        }
        *(undefined2 *)(iVar2 + 0x2a) = 0;
        uVar11 = FUN_080112a4();
        bVar9 = extraout_r1;
        while ((bVar9 < 100 && (*(uint *)(*DAT_08019118 + (99 - (uint)bVar9) * 4) <= uVar11))) {
          bVar9 = bVar9 + 1;
        }
        if (bVar9 < 0x28) {
          *(byte *)(extraout_r2 + 1) = bVar9;
          *(undefined1 *)(extraout_r2 + 7) = 1;
          uVar3 = DAT_0801911c;
          *(undefined4 *)(extraout_r2 + 0xc) = DAT_0801911c;
          *(undefined4 *)(extraout_r2 + 8) = uVar3;
          return;
        }
        return;
      }
    }
    *(undefined2 *)(DAT_08019108 + 0x2a) = 0;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: UART5_IRQHandler at 0x0801fe34
// ---------------------------------------------------------------------------

void UART5_IRQHandler(void)

{
  ushort *puVar1;
  
  puVar1 = DAT_0801fe78;
  if ((*DAT_0801fe78 & 0x28) != 0) {
    FUN_0801d9c4((char)DAT_0801fe78[2]);
    *puVar1 = *puVar1 & 0xffd7;
  }
  if (((int)((uint)DAT_0801fe78[6] << 0x18) < 0) && ((int)((uint)*puVar1 << 0x18) < 0)) {
    FUN_0801dd70();
    *puVar1 = *puVar1 & 0xff7f;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0802008c at 0x0802008c
// ---------------------------------------------------------------------------

void FUN_0802008c(void)

{
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  int *piVar7;
  int *piVar8;
  int iVar9;
  undefined2 in_r3;
  int iVar10;
  undefined2 local_28;
  undefined1 local_26;
  undefined1 local_25;
  
  pcVar1 = DAT_080202a0;
  _local_28 = CONCAT13(0x10,CONCAT12(1,in_r3));
  if ((*DAT_080202a0 == '\x02') || (*DAT_080202a0 == '\x04')) {
    FUN_08020568(DAT_080202a4,0);
  }
  pcVar2 = DAT_080202a8;
  if ((*DAT_080202a8 == '\x02') || (*DAT_080202a8 == '\x04')) {
    FUN_08020568(DAT_080202ac,0);
  }
  pcVar3 = DAT_080202b0;
  if ((*DAT_080202b0 == '\x02') || (*DAT_080202b0 == '\x04')) {
    FUN_08020568(DAT_080202b4,0);
  }
  pcVar4 = DAT_080202b8;
  if ((*DAT_080202b8 == '\x02') || (*DAT_080202b8 == '\x04')) {
    FUN_08020568(DAT_080202bc,0);
  }
  pcVar5 = DAT_080202c0;
  if ((*DAT_080202c0 == '\x02') || (*DAT_080202c0 == '\x04')) {
    FUN_08020568(DAT_080202c4,0);
  }
  pcVar6 = DAT_080202c8;
  if ((*DAT_080202c8 == '\x02') || (*DAT_080202c8 == '\x04')) {
    FUN_08020568(DAT_080202cc,0);
  }
  piVar8 = DAT_080202d4;
  piVar7 = DAT_080202d0;
  iVar10 = (int)DAT_080202d0 >> 0x14;
  if (*pcVar6 != '\0') {
    if (*DAT_080202d8 == '\n') {
      _local_28 = CONCAT22(_local_26,0x600);
      FUN_0801031c(DAT_080202d0 + -5,&local_28);
      *piVar7 = iVar10;
      *piVar7 = 0x200;
    }
    else if (*DAT_080202d8 == '\a') {
      _local_28 = CONCAT22(_local_26,0xc0);
      FUN_0801031c(DAT_080202d4 + -5,&local_28);
      *piVar8 = 0x80;
      *piVar8 = 0x40;
    }
  }
  if (*pcVar5 != '\0') {
    if (*DAT_080202dc == '\x03') {
      _local_28 = CONCAT22(_local_26,0xc);
      FUN_0801031c(DAT_080202d0 + -5,&local_28);
      *piVar7 = 8;
      *piVar7 = 4;
    }
    else if (*DAT_080202dc == '\x05') {
      _local_28 = CONCAT22(_local_26,0x30);
      FUN_0801031c(DAT_080202d4 + -5,&local_28);
      *piVar8 = 0x20;
      *piVar8 = 0x10;
    }
  }
  if ((*pcVar4 != '\0') && (*DAT_080202e0 == '\v')) {
    _local_28 = CONCAT22(_local_26,0xc00);
    FUN_0801031c(DAT_080202d4 + -5,&local_28);
    *piVar8 = 0x800;
    *piVar8 = iVar10;
  }
  iVar9 = DAT_080202e4;
  if (*pcVar3 != '\0') {
    if (*DAT_080202e8 == '\x0e') {
      _local_28 = CONCAT22(_local_26,0x6000);
      FUN_0801031c(DAT_080202d0 + -5,&local_28);
      *piVar7 = 0x4000;
      *piVar7 = 0x2000;
    }
    else if (*DAT_080202e8 == '\v') {
      _local_28 = CONCAT22(_local_26,0xc00);
      FUN_0801031c(DAT_080202e4,&local_28);
      *(undefined4 *)(iVar9 + 0x14) = 0x800;
      *(int *)(iVar9 + 0x14) = iVar10;
    }
  }
  if ((*pcVar2 != '\0') && (*DAT_080202ec == '\x0e')) {
    _local_28 = CONCAT22(_local_26,0x6000);
    FUN_0801031c(DAT_080202d4 + -5,&local_28);
    *piVar8 = 0x4000;
    *piVar8 = 0x2000;
  }
  if ((*pcVar1 != '\0') && (*DAT_080202f0 == '\x01')) {
    _local_28 = CONCAT22(_local_26,3);
    FUN_0801031c(iVar9,&local_28);
    *(undefined4 *)(iVar9 + 0x14) = 1;
    *(undefined4 *)(iVar9 + 0x14) = 2;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080202f4 at 0x080202f4
// ---------------------------------------------------------------------------

void FUN_080202f4(void)

{
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  
  pcVar1 = DAT_08020518;
  if ((*DAT_08020518 == '\x02') || (*DAT_08020518 == '\x04')) {
    FUN_08020568(DAT_0802051c,0);
  }
  pcVar2 = DAT_08020520;
  if ((*DAT_08020520 == '\x02') || (*DAT_08020520 == '\x04')) {
    FUN_08020568(DAT_08020524,0);
  }
  pcVar3 = DAT_08020528;
  if ((*DAT_08020528 == '\x02') || (*DAT_08020528 == '\x04')) {
    FUN_08020568(DAT_0802052c,0);
  }
  pcVar4 = DAT_08020530;
  if ((*DAT_08020530 == '\x02') || (*DAT_08020530 == '\x04')) {
    FUN_08020568(DAT_08020534,0);
  }
  pcVar5 = DAT_08020538;
  if ((*DAT_08020538 == '\x02') || (*DAT_08020538 == '\x04')) {
    FUN_08020568(DAT_0802053c,0);
  }
  pcVar6 = DAT_08020540;
  if ((*DAT_08020540 == '\x02') || (*DAT_08020540 == '\x04')) {
    FUN_08020568(DAT_08020544,0);
  }
  uVar12 = DAT_0802054c;
  uVar9 = DAT_08020548;
  if ((*pcVar6 == '\x01') || (*pcVar6 == '\x02')) {
    if (*DAT_08020550 == '\n') {
      uVar8 = 0x400;
      if (*pcVar6 == '\x01') {
        uVar10 = 0xc;
        uVar11 = 0x48;
      }
      else {
        uVar10 = 8;
        uVar11 = 4;
      }
      uVar7 = DAT_08020548;
    }
    else {
      if (*DAT_08020550 != '\a') goto LAB_080203d6;
      if (*pcVar6 == '\x01') {
        uVar10 = 0xc;
        uVar11 = 0x48;
      }
      else {
        uVar10 = 8;
        uVar11 = 4;
      }
      uVar8 = 0x80;
      uVar7 = DAT_0802054c;
    }
    FUN_0800ffa8(uVar7,uVar8,uVar11,uVar10);
  }
LAB_080203d6:
  if ((*pcVar5 == '\x01') || (*pcVar5 == '\x02')) {
    if (*DAT_08020554 == '\x03') {
      if (*pcVar5 == '\x01') {
        uVar11 = 0xc;
        uVar8 = 0x48;
      }
      else {
        uVar11 = 8;
        uVar8 = 4;
      }
      uVar7 = 8;
      uVar10 = uVar9;
    }
    else {
      if (*DAT_08020554 != '\x05') goto LAB_08020422;
      if (*pcVar5 == '\x01') {
        uVar11 = 0xc;
        uVar8 = 0x48;
      }
      else {
        uVar11 = 8;
        uVar8 = 4;
      }
      uVar7 = 0x20;
      uVar10 = uVar12;
    }
    FUN_0800ffa8(uVar10,uVar7,uVar8,uVar11);
  }
LAB_08020422:
  if (((*pcVar4 == '\x01') || (*pcVar4 == '\x02')) && (*DAT_08020558 == '\v')) {
    if (*pcVar4 == '\x01') {
      uVar11 = 0xc;
      uVar8 = 0x48;
    }
    else {
      uVar11 = 8;
      uVar8 = 4;
    }
    FUN_0800ffa8(uVar12,0x800,uVar8,uVar11);
  }
  uVar8 = DAT_0802055c;
  if ((*pcVar3 == '\x01') || (*pcVar3 == '\x02')) {
    if (*DAT_08020560 == '\x0e') {
      if (*pcVar3 == '\x01') {
        uVar10 = 0xc;
        uVar11 = 0x48;
      }
      else {
        uVar10 = 8;
        uVar11 = 4;
      }
      uVar7 = 0x4000;
    }
    else {
      if (*DAT_08020560 != '\v') goto LAB_080204ac;
      if (*pcVar3 == '\x01') {
        uVar10 = 0xc;
        uVar11 = 0x48;
      }
      else {
        uVar10 = 8;
        uVar11 = 4;
      }
      uVar7 = 0x800;
      uVar9 = DAT_0802055c;
    }
    FUN_0800ffa8(uVar9,uVar7,uVar11,uVar10);
  }
LAB_080204ac:
  pcVar3 = DAT_08020564;
  if (((*pcVar2 == '\x01') || (*pcVar2 == '\x02')) && (*DAT_08020564 == '\x0e')) {
    if (*pcVar2 == '\x01') {
      uVar11 = 0xc;
      uVar9 = 0x48;
    }
    else {
      uVar11 = 8;
      uVar9 = 4;
    }
    FUN_0800ffa8(uVar12,0x4000,uVar9,uVar11);
  }
  if (((*pcVar1 != '\x01') && (*pcVar1 != '\x02')) || (*pcVar3 != '\x01')) {
    return;
  }
  if (*pcVar1 == '\x01') {
    uVar12 = 0xc;
    uVar9 = 0x48;
  }
  else {
    uVar12 = 8;
    uVar9 = 4;
  }
  FUN_0800ffa8(uVar8,2,uVar9,uVar12);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08020568 at 0x08020568
// ---------------------------------------------------------------------------

void FUN_08020568(int param_1,int param_2)

{
  ushort uVar1;
  
  if (param_2 == 1) {
    uVar1 = *(ushort *)(param_1 + 0xc) | 8;
  }
  else {
    uVar1 = *(ushort *)(param_1 + 0xc) & 0xfff7;
  }
  *(ushort *)(param_1 + 0xc) = uVar1;
  return;
}



// ---------------------------------------------------------------------------
// Function: SPI2_IRQHandler at 0x0802057c
// ---------------------------------------------------------------------------

void SPI2_IRQHandler(void)

{
  ushort *puVar1;
  
  puVar1 = DAT_080205c0;
  if ((*DAT_080205c0 & 0x28) != 0) {
    FUN_0801d5e8((char)DAT_080205c0[2]);
    *puVar1 = *puVar1 & 0xffd7;
  }
  if (((int)((uint)DAT_080205c0[6] << 0x18) < 0) && ((int)((uint)*puVar1 << 0x18) < 0)) {
    FUN_0801db50();
    *puVar1 = *puVar1 & 0xff7f;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: USART1_IRQHandler at 0x080205c4
// ---------------------------------------------------------------------------

void USART1_IRQHandler(void)

{
  ushort *puVar1;
  
  puVar1 = DAT_08020608;
  if ((*DAT_08020608 & 0x28) != 0) {
    FUN_0801d6f8((char)DAT_08020608[2]);
    *puVar1 = *puVar1 & 0xffd7;
  }
  if (((int)((uint)DAT_08020608[6] << 0x18) < 0) && ((int)((uint)*puVar1 << 0x18) < 0)) {
    FUN_0801dc08();
    *puVar1 = *puVar1 & 0xff7f;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: USART2_IRQHandler at 0x0802060c
// ---------------------------------------------------------------------------

void USART2_IRQHandler(void)

{
  ushort *puVar1;
  
  puVar1 = DAT_08020650;
  if ((*DAT_08020650 & 0x28) != 0) {
    FUN_0801d8c0((char)DAT_08020650[2]);
    *puVar1 = *puVar1 & 0xffd7;
  }
  if (((int)((uint)DAT_08020650[6] << 0x18) < 0) && ((int)((uint)*puVar1 << 0x18) < 0)) {
    FUN_0801dcc0();
    *puVar1 = *puVar1 & 0xff7f;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08020654 at 0x08020654
// ---------------------------------------------------------------------------

void FUN_08020654(int param_1,uint param_2,int param_3)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = (param_2 & 0xff) >> 5;
  uVar2 = 1 << (param_2 & 0x1f);
  if (uVar3 == 1) {
    puVar1 = (uint *)(param_1 + 0xc);
  }
  else if (uVar3 == 2) {
    puVar1 = (uint *)(param_1 + 0x10);
  }
  else {
    puVar1 = (uint *)(param_1 + 0x14);
  }
  if (param_3 == 0) {
    uVar2 = *puVar1 & ~uVar2;
  }
  else {
    uVar2 = *puVar1 | uVar2;
  }
  *puVar1 = uVar2;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08020684 at 0x08020684
// ---------------------------------------------------------------------------

void FUN_08020684(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == DAT_08020710) {
    uVar1 = 0x4000;
LAB_080206e8:
    FUN_08017cc8(uVar1,1);
LAB_08020706:
    FUN_08017cc8(uVar1,0);
    return;
  }
  uVar1 = 0x20000;
  if (param_1 != DAT_08020714) {
    if (param_1 == DAT_08020718) {
      FUN_08017c98(0x40000,1);
      uVar1 = 0x40000;
      goto LAB_080206d8;
    }
    if (param_1 == DAT_0802071c) {
      uVar1 = 0x80000;
    }
    else {
      if (param_1 != DAT_08020720) {
        if (param_1 != DAT_08020724) {
          if (param_1 != DAT_08020728) {
            return;
          }
          FUN_08017cc8(0x40000,1);
          uVar1 = 0x40000;
          goto LAB_08020706;
        }
        goto LAB_080206e8;
      }
      uVar1 = 0x100000;
    }
  }
  FUN_08017c98(uVar1,1);
LAB_080206d8:
  FUN_08017c98(uVar1,0);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_0802072c at 0x0802072c
// ---------------------------------------------------------------------------

void FUN_0802072c(int param_1,int param_2)

{
  ushort uVar1;
  
  if (param_2 == 0) {
    uVar1 = *(ushort *)(param_1 + 0xc) & 0xdfff;
  }
  else {
    uVar1 = *(ushort *)(param_1 + 0xc) | 0x2000;
  }
  *(ushort *)(param_1 + 0xc) = uVar1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08020740 at 0x08020740
// ---------------------------------------------------------------------------

void FUN_08020740(int param_1,int *param_2)

{
  uint uVar1;
  undefined1 auStack_28 [8];
  int local_20;
  int local_1c;
  
  *(ushort *)(param_1 + 0x10) = *(ushort *)((int)param_2 + 6) | *(ushort *)(param_1 + 0x10) & 0xcfff
  ;
  *(ushort *)(param_1 + 0xc) =
       *(ushort *)(param_2 + 1) | *(ushort *)(param_2 + 2) |
       *(ushort *)((int)param_2 + 10) | *(ushort *)(param_1 + 0xc) & 0xe9f3;
  *(ushort *)(param_1 + 0x14) = *(ushort *)(param_2 + 3) | *(ushort *)(param_1 + 0x14) & 0xfcff;
  FUN_08017d04(auStack_28);
  if (((param_1 != DAT_080207d4) && (param_1 != DAT_080207d8)) && (param_1 != DAT_080207dc)) {
    local_1c = local_20;
  }
  uVar1 = (uint)(local_1c * 0x19) / (uint)(*param_2 << 2);
  *(ushort *)(param_1 + 8) =
       (ushort)(((uVar1 % 100) * 0x10 + 0x32) / 100) & 0xf | (ushort)(uVar1 / 100 << 4);
  return;
}



// ---------------------------------------------------------------------------
// Function: CAN1_TX_IRQHandler at 0x080207e0
// ---------------------------------------------------------------------------

void CAN1_TX_IRQHandler(void)

{
  int *piVar1;
  undefined1 *puVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  uint local_18;
  
  FUN_0800a828(DAT_080207f8,0,DAT_080207f4);
  piVar1 = DAT_080172f0;
  if (DAT_080172f0[1] != 0) {
    FUN_08017304();
    FUN_0800bfd8();
    FUN_08018798();
    FUN_08020f1c(piVar1[1],(int)piVar1 + 0xb,*(undefined1 *)((int)piVar1 + 10));
    piVar1[1] = 0;
  }
  pbVar4 = DAT_080172fc;
  iVar3 = DAT_080172f8;
  puVar2 = DAT_080172f4;
  iVar5 = *piVar1;
  if (iVar5 == 0) goto LAB_080172e0;
  if (iVar5 == 1) {
    if (*(char *)((int)piVar1 + 9) == '\0') {
      DAT_080172fc[1] = 1;
      *pbVar4 = 0;
      *(undefined2 *)(iVar3 + 0x260) = 0;
      *puVar2 = 0;
      *(undefined2 *)(iVar3 + 300) = 1;
    }
  }
  else {
    if (iVar5 == 2) {
      if ((*(char *)((int)piVar1 + 9) != '\0') || (DAT_080172fc[1] != 1)) goto LAB_080172de;
      local_18 = 0;
      while ((byte)local_18 < 8) {
        *(undefined1 *)(iVar3 + *pbVar4 + local_18) = *(undefined1 *)((int)piVar1 + local_18 + 0xb);
        local_18 = (uint)(byte)((byte)local_18 + 1);
      }
      *pbVar4 = *pbVar4 + 8;
    }
    if (((iVar5 == 3) && (*(char *)((int)piVar1 + 9) == '\0')) && (pbVar4[1] == 1)) {
      pbVar4[1] = 3;
      *pbVar4 = 0;
      *(undefined1 *)(iVar3 + 0x25c) = 1;
      *(undefined2 *)(iVar3 + 0x25e) = 0;
      *(undefined1 *)(iVar3 + 0x262) = 5;
    }
  }
LAB_080172de:
  *piVar1 = 0;
LAB_080172e0:
  *(undefined4 *)(DAT_08017300 + 4) = 0;
  *puVar2 = 0;
  *(undefined2 *)(iVar3 + 0x260) = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080207fc at 0x080207fc
// ---------------------------------------------------------------------------

void FUN_080207fc(void)

{
  uint in_fpscr;
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  
  fVar3 = (float)VectorUnsignedToFloat
                           ((uint)*(ushort *)(DAT_08020848 + 0x10),(byte)(in_fpscr >> 0x16) & 3);
  fVar2 = DAT_08020850 - fVar3 * *DAT_0802084c;
  fVar3 = DAT_08020844;
  if (0.0 <= fVar2) {
    fVar3 = fVar2;
  }
  uVar1 = VectorFloatToUnsigned(fVar3,3);
  *DAT_08020854 = (char)uVar1;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08020858 at 0x08020858
// ---------------------------------------------------------------------------

void FUN_08020858(void)

{
  byte bVar1;
  char *pcVar2;
  undefined4 uVar3;
  int iVar4;
  float *pfVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  byte *pbVar10;
  byte *pbVar11;
  byte *pbVar12;
  char *pcVar13;
  undefined1 uVar14;
  float *pfVar15;
  uint in_fpscr;
  uint uVar16;
  uint uVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  
  pcVar2 = DAT_08020c64;
  iVar4 = DAT_08020c60;
  uVar3 = DAT_08020c5c;
  if ((*(char *)(DAT_08020c60 + 0x12) != '\0') && (*(char *)(DAT_08020c60 + 0x1b) != '\0')) {
    return;
  }
  if (*(char *)(DAT_08020c60 + 0x3a) == '\0') {
    pcVar2[0x1a] = '\0';
    pcVar2[0x1b] = '\0';
  }
  else if (*(ushort *)(DAT_08020c64 + 0x1a) < 0x14) {
    *(short *)(DAT_08020c64 + 0x1a) = *(short *)(DAT_08020c64 + 0x1a) + 1;
  }
  iVar8 = DAT_08020c7c;
  iVar7 = DAT_08020c74;
  pfVar6 = DAT_08020c70;
  pfVar5 = DAT_08020c6c;
  fVar20 = DAT_08020c68;
  pfVar15 = (float *)(DAT_08020c74 + -0x20);
  if ((((*(char *)(iVar4 + 0x12) != '\0') ||
       ((*(char *)(iVar4 + 0x2f) != '\0' && (*DAT_08020c78 != '\0')))) &&
      (*(char *)(iVar4 + 0x3a) != '\0')) &&
     (((0x13 < *(ushort *)(pcVar2 + 0x1a) &&
       (fVar18 = DAT_08020c6c[3], fVar21 = DAT_08020c70[3], (int)(fVar18 - fVar21) < DAT_08020c7c))
      && (uVar16 = in_fpscr & 0xfffffff, in_fpscr = uVar16,
         DAT_08020c6c[3] < *DAT_08020c6c + DAT_08020c68)))) {
    fVar19 = DAT_08020c70[3];
    fVar22 = *DAT_08020c70 + DAT_08020c68;
    uVar17 = uVar16 | (uint)(fVar19 < fVar22) << 0x1f | (uint)(fVar19 == fVar22) << 0x1e;
    in_fpscr = uVar17 | (uint)(NAN(fVar19) || NAN(fVar22)) << 0x1c;
    bVar1 = (byte)(uVar17 >> 0x18);
    if (!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
      pcVar2[0x1a] = '\0';
      pcVar2[0x1b] = '\0';
      if (*pcVar2 != '\0') {
        *(undefined1 *)(iVar7 + 0x19) = 1;
      }
      fVar19 = (float)VectorSignedToFloat(*(undefined4 *)(iVar7 + -0x18),
                                          (byte)(in_fpscr >> 0x16) & 3);
      in_fpscr = uVar16;
      if (fVar19 != *pfVar15) {
        FUN_08019844(0,0x25,fVar18 - fVar21,iVar8,uVar3);
        *(int *)(iVar7 + -0x18) = (int)*pfVar15;
        if ((*DAT_08020c80 == '\0') && (pcVar2[3] == '\0')) {
          uVar14 = 0xc6;
        }
        else {
          uVar14 = 200;
        }
        *(undefined1 *)(iVar7 + -0xe) = uVar14;
        *(undefined1 *)(iVar7 + -0xd) = uVar14;
        *(undefined1 *)(iVar7 + -0xc) = uVar14;
        FUN_0801975c();
        in_fpscr = uVar16;
      }
      iVar8 = DAT_08020c74;
      *(undefined4 *)(pcVar2 + 0x30) = uVar3;
      *(undefined4 *)(iVar8 + 0x84) = uVar3;
      *(undefined4 *)(iVar8 + 0x88) = uVar3;
      FUN_08019124();
    }
  }
  if (*(char *)(iVar4 + 0x3a) == '\0') {
    pcVar2[0x14] = '\0';
    pcVar2[0x15] = '\0';
    if (*(char *)(iVar4 + 0x3b) != '\0') {
      pcVar2[3] = '\0';
    }
  }
  else {
    pcVar2[2] = '\0';
    uVar16 = in_fpscr & 0xfffffff;
    uVar17 = uVar16 | (uint)(*(float *)(DAT_08020c84 + 0x114) < *(float *)(iVar7 + 0x28)) << 0x1f;
    in_fpscr = uVar17 | (uint)(NAN(*(float *)(DAT_08020c84 + 0x114)) ||
                              NAN(*(float *)(iVar7 + 0x28))) << 0x1c;
    if (((byte)(uVar17 >> 0x1f) != ((byte)(in_fpscr >> 0x1c) & 1)) ||
       (in_fpscr = uVar16, *(float *)(iVar7 + 0x2c) <= *(float *)(DAT_08020c88 + 0x14))) {
      pcVar2[0x14] = '\0';
      pcVar2[0x15] = '\0';
    }
    else if ((uint)*(ushort *)(pcVar2 + 0x14) < (uint)*(ushort *)(iVar7 + 0x3c) * 10) {
      *(short *)(pcVar2 + 0x14) = *(short *)(pcVar2 + 0x14) + 1;
    }
    else {
      pcVar2[0x14] = '\0';
      pcVar2[0x15] = '\0';
      if (*pcVar2 != '\0') {
        *(undefined1 *)(iVar7 + 0x19) = 1;
      }
      if ((*(char *)(iVar4 + 0x4d) != '\0') || (*(char *)(iVar4 + 0x4b) != '\0')) {
        if (*DAT_08020c8c != '\0') {
          *(byte *)(iVar4 + 0x12) = *(byte *)(iVar4 + 0x12) | 0x10;
          FUN_08019844(0x15,9);
          FUN_0800ac9c();
        }
        pcVar2[3] = '\x01';
      }
      in_fpscr = uVar16;
      if (((int)(pfVar5[3] - pfVar6[3]) < DAT_08020c7c) &&
         (uVar16 = uVar16 & 0xfffffff, in_fpscr = uVar16, pfVar5[3] < *pfVar5 + fVar20)) {
        fVar18 = pfVar6[3];
        fVar20 = *pfVar6 + fVar20;
        uVar17 = uVar16 | (uint)(fVar18 < fVar20) << 0x1f | (uint)(fVar18 == fVar20) << 0x1e;
        in_fpscr = uVar17 | (uint)(NAN(fVar18) || NAN(fVar20)) << 0x1c;
        bVar1 = (byte)(uVar17 >> 0x18);
        if (!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
          fVar20 = (float)VectorSignedToFloat(*(undefined4 *)(iVar7 + -0x18),
                                              (byte)(in_fpscr >> 0x16) & 3);
          if (fVar20 != *pfVar15) {
            *(int *)(iVar7 + -0x18) = (int)*pfVar15;
            if (((*DAT_08020c80 == '\0') && (*DAT_08020c8c == '\0')) && (pcVar2[3] == '\0')) {
              uVar14 = 0xc6;
            }
            else {
              uVar14 = 200;
            }
            *(undefined1 *)(iVar7 + -0xe) = uVar14;
            *(undefined1 *)(iVar7 + -0xd) = uVar14;
            *(undefined1 *)(iVar7 + -0xc) = uVar14;
            FUN_0801975c();
            if (*DAT_08020c8c == '\0') {
              FUN_08019844(0,0x5e);
            }
          }
          iVar8 = DAT_08020c74;
          *(undefined4 *)(pcVar2 + 0x30) = uVar3;
          *(undefined4 *)(iVar8 + 0x84) = uVar3;
          *(undefined4 *)(iVar8 + 0x88) = uVar3;
          FUN_08019124();
          in_fpscr = uVar16;
        }
      }
    }
  }
  if (*DAT_08020c90 == '\0') {
    fVar20 = pfVar6[3];
  }
  else {
    fVar20 = *(float *)(DAT_08020c84 + 0x114);
  }
  uVar16 = in_fpscr & 0xfffffff;
  uVar17 = uVar16 | (uint)(*(float *)(iVar7 + 0x48) < fVar20) << 0x1f;
  if (((SUB41(uVar17 >> 0x1f,0) == (NAN(*(float *)(iVar7 + 0x48)) || NAN(fVar20))) &&
      ((*(char *)(iVar4 + 0x3b) != '\0' || (*DAT_08020c94 != '\0')))) &&
     ((fVar18 = (float)VectorUnsignedToFloat
                                 (*(undefined4 *)(iVar7 + -0x1c),(byte)(uVar17 >> 0x16) & 3),
      uVar17 = uVar16, *(float *)(DAT_08020c88 + 0x10) < fVar18 * *DAT_08020c98 &&
      (*(short *)(pcVar2 + 0x16) = *(short *)(pcVar2 + 0x16) + 1, 0x3b < *(ushort *)(pcVar2 + 0x16))
      ))) {
    pcVar2[0x16] = '\0';
    pcVar2[0x17] = '\0';
    pcVar2[1] = '\x01';
    pcVar2[2] = '\x01';
  }
  if (*(short *)(pcVar2 + 0x16) == 0) {
    pcVar2[0x18] = '\0';
    pcVar2[0x19] = '\0';
  }
  else {
    *(short *)(pcVar2 + 0x18) = *(short *)(pcVar2 + 0x18) + 1;
    if (599 < *(ushort *)(pcVar2 + 0x18)) {
      pcVar2[0x18] = '\0';
      pcVar2[0x19] = '\0';
      pcVar2[0x16] = '\0';
      pcVar2[0x17] = '\0';
    }
  }
  if (*(char *)(iVar4 + 0x1b) == '\0') {
    pcVar2[6] = '\0';
  }
  pbVar11 = DAT_08020ca4;
  pbVar10 = DAT_08020ca0;
  iVar9 = DAT_08020c9c;
  iVar8 = DAT_08020c74;
  if (((*(short *)(DAT_08020c9c + 0x22) < (short)(ushort)*DAT_08020ca0) ||
      ((short)(ushort)*DAT_08020ca4 < *(short *)(DAT_08020c9c + 0x1e))) ||
     (((*(char *)(iVar4 + 0x1b) == '\0' || (DAT_08020ca8 <= (int)(pfVar5[3] - pfVar6[3]))) &&
      (pcVar2[1] == '\0')))) {
    if (DAT_08020ca8 <= (int)(pfVar5[3] - pfVar6[3])) {
      pcVar2[6] = '\x01';
      *(undefined1 *)(DAT_08020c74 + 0x5f) = 0;
    }
  }
  else if ((((*(char *)(DAT_08020c74 + 0x5f) == '\0') || (*(char *)(iVar4 + 0x3b) != '\0')) ||
           (uVar17 = uVar17 & 0xfffffff | (uint)(*(float *)(iVar7 + 0x48) < fVar20) << 0x1f,
           SUB41(uVar17 >> 0x1f,0) == (NAN(*(float *)(iVar7 + 0x48)) || NAN(fVar20)))) &&
          (pcVar2[6] == '\0')) {
    *(undefined1 *)(DAT_08020c74 + 0x59) = 0;
    *(undefined1 *)(iVar8 + 0x5f) = 2;
    *(undefined4 *)(iVar8 + 100) = uVar3;
    *(undefined4 *)(iVar8 + 0x60) = uVar3;
  }
  if ((((*(char *)(iVar4 + 0x1b) == '\0') &&
       ((*(char *)(iVar4 + 0x25) == '\0' || (*DAT_08020cac == '\0')))) ||
      ((*(char *)(iVar4 + 0x3b) == '\0' && (*DAT_08020c94 == '\0')))) && (pcVar2[1] == '\0')) {
    pcVar2[0x1c] = '\0';
    pcVar2[0x1d] = '\0';
    return;
  }
  pcVar2[1] = '\0';
  pcVar13 = DAT_08020f04;
  iVar8 = DAT_08020cb4;
  pbVar12 = DAT_08020cb0;
  if ((*(char *)(iVar7 + 0x19) == '\0') || (*(char *)(DAT_08020cb4 + 5) == '\x02'))
  goto LAB_08020eb2;
  fVar20 = (float)VectorSignedToFloat(*(undefined4 *)(iVar7 + -0x18),(byte)(uVar17 >> 0x16) & 3);
  fVar18 = (float)VectorUnsignedToFloat(*(int *)(iVar7 + -0x1c) * 0x1e,(byte)(uVar17 >> 0x16) & 3);
  uVar17 = uVar17 & 0xfffffff;
  if (*pfVar15 - fVar20 < fVar18) {
    *(undefined1 *)(iVar7 + 0x19) = 0;
    return;
  }
  if (*(char *)(iVar7 + 0x19) == '\x01') {
    *(undefined1 *)(iVar7 + 0x19) = 0;
    if ((*pcVar13 == '\0') &&
       ((*(short *)(iVar9 + 0x22) < (short)(ushort)*pbVar10 ||
        ((short)(ushort)*pbVar11 < *(short *)(iVar9 + 0x1e))))) {
      if (*(char *)(iVar8 + 5) != '\0') goto LAB_08020df0;
LAB_08020dbe:
      fVar20 = (float)VectorSignedToFloat(*(undefined4 *)(iVar7 + -0x18),(byte)(uVar17 >> 0x16) & 3)
      ;
      fVar20 = *pfVar15 - fVar20;
    }
    else {
      if ((uint)*pbVar12 << 1 <= (uint)*(byte *)(iVar7 + -0xe)) goto LAB_08020d86;
      if (*pcVar13 != '\0') goto LAB_08020dbe;
      fVar20 = (float)VectorSignedToFloat(*(undefined4 *)(iVar7 + -0x18),(byte)(uVar17 >> 0x16) & 3)
      ;
      fVar20 = (*pfVar15 - fVar20) - *(float *)(DAT_08020f08 + 0xc);
    }
    *pfVar15 = fVar20;
LAB_08020d7e:
    FUN_08019844(0,6);
  }
  else if (*(char *)(iVar7 + 0x19) == '\x02') {
    *(undefined1 *)(iVar7 + 0x19) = 0;
    if ((*pcVar13 == '\0') &&
       ((*(short *)(iVar9 + 0x22) < (short)(ushort)*pbVar10 ||
        ((short)(ushort)*pbVar11 < *(short *)(iVar9 + 0x1e))))) {
LAB_08020df0:
      if (((uint)*pbVar12 << 1 <= (uint)*(byte *)(iVar7 + -0xe)) || (*DAT_08020f10 == '\0'))
      goto LAB_08020d86;
    }
    fVar20 = (float)VectorSignedToFloat(*(undefined4 *)(iVar7 + -0x18),(byte)(uVar17 >> 0x16) & 3);
    FUN_08016500(*pfVar15 - fVar20);
    goto LAB_08020d7e;
  }
LAB_08020d86:
  fVar18 = *pfVar15;
  fVar20 = (float)VectorUnsignedToFloat
                            ((*DAT_08020f0c + 100) * *(int *)(iVar7 + -0x1c),
                             (byte)(uVar17 >> 0x16) & 3);
  uVar16 = uVar17 & 0xfffffff | (uint)(fVar18 < fVar20) << 0x1f | (uint)(fVar18 == fVar20) << 0x1e;
  bVar1 = (byte)(uVar16 >> 0x18);
  if ((bool)(bVar1 >> 6 & 1) || (bool)(bVar1 >> 7) != (NAN(fVar18) || NAN(fVar20))) {
    fVar20 = (float)VectorUnsignedToFloat
                              ((uint)*(ushort *)(iVar7 + -0x10),(byte)(uVar16 >> 0x16) & 3);
    fVar21 = (float)VectorUnsignedToFloat(*(undefined4 *)(iVar7 + -0x1c),(byte)(uVar16 >> 0x16) & 3)
    ;
    fVar18 = (float)VectorUnsignedToFloat(*(int *)(iVar7 + -0x1c) * 0x3c,(byte)(uVar16 >> 0x16) & 3)
    ;
    fVar18 = fVar18 - fVar20 * *(float *)(iVar7 + 0x38) * DAT_08020f14 * fVar21;
    fVar20 = *pfVar15;
    uVar16 = uVar17 & 0xfffffff | (uint)(fVar18 < fVar20) << 0x1f | (uint)(fVar18 == fVar20) << 0x1e
    ;
    bVar1 = (byte)(uVar16 >> 0x18);
    if (!(bool)(bVar1 >> 6 & 1) && (bool)(bVar1 >> 7) == (NAN(fVar18) || NAN(fVar20))) {
      fVar18 = (float)VectorUnsignedToFloat
                                ((uint)*(ushort *)(iVar7 + -0x10),(byte)(uVar16 >> 0x16) & 3);
      fVar21 = (float)VectorUnsignedToFloat
                                (*(undefined4 *)(iVar7 + -0x1c),(byte)(uVar16 >> 0x16) & 3);
      fVar20 = (float)VectorUnsignedToFloat
                                (*(int *)(iVar7 + -0x1c) * 0x3c,(byte)(uVar16 >> 0x16) & 3);
      fVar20 = fVar20 - fVar18 * *(float *)(iVar7 + 0x38) * DAT_08020f14 * fVar21;
      goto LAB_08020e80;
    }
  }
  else {
    fVar20 = (float)VectorUnsignedToFloat
                              ((*DAT_08020f0c + 100) * *(int *)(iVar7 + -0x1c),
                               (byte)(uVar16 >> 0x16) & 3);
LAB_08020e80:
    *pfVar15 = fVar20;
  }
  if ((uint)*(byte *)(iVar7 + -0xe) < (uint)*pbVar12 << 1) {
    *(undefined4 *)(iVar7 + 4) = *(undefined4 *)(iVar7 + 8);
    FUN_08019844(0,0x2b);
    *(undefined4 *)(iVar7 + -0x18) = 0;
    FUN_0800b460();
    FUN_0801975c();
    *(undefined1 *)(iVar7 + -0xe) = 0;
    *(undefined1 *)(iVar7 + -0xd) = 0;
    *(undefined1 *)(iVar7 + -0xc) = 0;
    *(undefined1 *)(iVar7 + 0x19) = 0;
    pcVar2[2] = '\x01';
  }
LAB_08020eb2:
  if (((*(byte *)(iVar7 + -0xe) >> 1 != 0) && ((uint)*(byte *)(iVar7 + -0xe) < (uint)*pbVar12 << 1))
     && (*(char *)(iVar4 + 0x3a) == '\0')) {
    *(undefined4 *)(iVar7 + 4) = *(undefined4 *)(iVar7 + 8);
    if (*(short *)(pcVar2 + 0x1c) == 0) {
      FUN_08019844(0,0x2b);
    }
    *(undefined4 *)(iVar7 + -0x18) = 0;
    FUN_0800b460();
    FUN_0801975c();
    *(undefined1 *)(iVar7 + -0xe) = 0;
    *(undefined1 *)(iVar7 + -0xd) = 0;
    *(undefined1 *)(iVar7 + -0xc) = 0;
    pcVar2[2] = '\x01';
    pcVar2[0x1c] = '\x01';
    pcVar2[0x1d] = '\0';
  }
  *(undefined4 *)(pcVar2 + 0x30) = uVar3;
  pcVar2[4] = '\0';
  return;
}



// ---------------------------------------------------------------------------
// Function: UsageFault_Handler at 0x08020f18
// ---------------------------------------------------------------------------

void UsageFault_Handler(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ---------------------------------------------------------------------------
// Function: FUN_08020f1c at 0x08020f1c
// ---------------------------------------------------------------------------

uint * FUN_08020f1c(undefined4 param_1,char *param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 uVar5;
  char cVar6;
  undefined2 uVar7;
  ushort uVar8;
  short sVar9;
  byte *pbVar10;
  undefined4 uVar11;
  uint *puVar12;
  byte bVar13;
  byte bVar14;
  uint uVar15;
  undefined4 uVar16;
  undefined1 *puVar17;
  byte extraout_r2;
  int iVar18;
  uint *puVar19;
  undefined4 *puVar20;
  int iVar21;
  undefined8 uVar22;
  byte local_74;
  byte abStack_70 [32];
  byte local_50;
  byte local_4c;
  byte local_48;
  char local_47;
  char local_46;
  undefined1 local_45;
  char local_44;
  undefined4 local_40;
  byte local_3c;
  uint local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  local_1c = 0;
  local_20 = 0;
  local_18 = (uint *)param_1;
  FUN_0800daf4(param_1);
  uVar8 = local_40._2_2_;
  puVar12 = DAT_08021208;
  if (*(char *)((int)DAT_08021208 + 1) != (char)DAT_08021208[-6]) {
    return DAT_08021208;
  }
  if (((char)*DAT_08021208 == '\x1d') && (*(char *)((int)DAT_08021208 + 1) == '\x14')) {
    return DAT_08021208;
  }
  if (((char)*DAT_08021208 == '\x14') && (*(char *)((int)DAT_08021208 + 1) == '\x1d')) {
    return DAT_08021208;
  }
  puVar19 = DAT_08021208 + 1;
  *(char *)puVar19 = (char)DAT_08021208[-6];
  *(char *)((int)puVar12 + 5) = (char)*puVar12;
  *(char *)((int)puVar12 + 6) = *(char *)((int)puVar12 + 2);
  *(char *)((int)puVar12 + 7) = *(char *)((int)puVar12 + 3);
  puVar4 = DAT_080215e4;
  puVar17 = DAT_080215d8;
  iVar3 = DAT_080215d4;
  iVar2 = DAT_080215d0;
  iVar18 = DAT_0801c0bc;
  iVar21 = DAT_0801bf58;
  bVar14 = *(byte *)((int)puVar12 + 2);
  if (bVar14 == 0x41) {
    uVar1 = *puVar19;
    bVar14 = *(byte *)((int)puVar12 + 3);
    bVar13 = 0;
    local_24 = (char *)0x0;
    local_20 = 0;
    uVar15 = local_1c >> 0x10;
    uVar7 = (undefined2)(local_1c >> 0x10);
    local_1c = uVar15 << 0x10;
    local_1c._2_2_ = uVar7;
    if (bVar14 == 1) {
      local_24._0_2_ = CONCAT11(*DAT_0801bf54,*DAT_0801bf50);
      local_1c._0_2_ =
           ((short)*(int *)(DAT_0801bf44 + 4) + (short)(*(int *)(DAT_0801bf44 + 4) << 2)) * 2;
      local_24._0_3_ = CONCAT12((char)(short)local_1c,(undefined2)local_24);
      local_24 = (char *)CONCAT13((char)((ushort)(short)local_1c >> 8),(uint3)local_24);
      uVar22 = FUN_080085d2(*(undefined4 *)(DAT_0801bf58 + 8));
      FUN_08008364((int)uVar22,(int)((ulonglong)uVar22 >> 0x20),(int)DAT_0801bf5c,
                   (int)((ulonglong)DAT_0801bf5c >> 0x20));
      uVar5 = FUN_080085a0();
      uVar11 = VectorFloatToUnsigned(*(undefined4 *)(iVar21 + 4),3);
      local_20._0_2_ = CONCAT11((char)uVar11,uVar5);
      sVar9 = 1000;
LAB_0801bdfa:
      local_1c = CONCAT22(local_1c._2_2_,sVar9);
    }
    else {
      if (bVar14 != 2) {
        if ((bVar14 < 3) || (8 < bVar14)) {
          if (bVar14 == 0x10) {
            for (; local_28 = (uint)bVar13, local_28 < 8; bVar13 = bVar13 + 1) {
              if ((*(uint *)(DAT_0801bf68 + 8) & 1 << bVar13) != 0) {
                *(undefined1 *)((int)&local_24 + local_28) = 1;
              }
            }
          }
          else if (bVar14 == 0x11) {
            for (bVar14 = 8; local_28 = (uint)bVar14, local_28 < 0x10; bVar14 = bVar14 + 1) {
              if ((*(uint *)(DAT_0801bf68 + 8) & 1 << bVar14) != 0) {
                *(undefined1 *)((int)&local_24 + local_28) = 1;
              }
            }
          }
          else {
            if (bVar14 != 0x12) {
              return (uint *)0x1;
            }
            for (bVar14 = 0x10; local_28 = (uint)bVar14, local_28 < 0x18; bVar14 = bVar14 + 1) {
              if ((*(uint *)(DAT_0801bf68 + 8) & 1 << bVar14) != 0) {
                *(undefined1 *)((int)&local_24 + local_28) = 1;
              }
            }
          }
        }
        else {
          local_28 = 0;
          while ((byte)local_28 < 4) {
            uVar11 = VectorFloatToUnsigned
                               (*(float *)(DAT_0801bf48 + (local_28 + (uint)bVar14 * 4) * 4 + 0x50)
                                * DAT_0801bf4c,3);
            local_1c = CONCAT22(local_1c._2_2_,(short)uVar11);
            *(char *)((int)&local_24 + local_28 * 2) = (char)uVar11;
            *(char *)((int)&local_24 + local_28 * 2 + 1) = (char)(local_1c >> 8);
            local_28 = (uint)(byte)((byte)local_28 + 1);
          }
        }
        goto LAB_0801be68;
      }
      local_24._0_3_ = CONCAT12((char)DAT_0801bf64[0x11],*(undefined2 *)(DAT_0801bf44 + 0x10));
      local_24 = (char *)CONCAT13((char)((ushort)DAT_0801bf64[0x11] >> 8),(uint3)local_24);
      local_20._0_2_ = DAT_0801bf64[0x10];
      if (*DAT_0801bf64 != -1) {
        sVar9 = *DAT_0801bf64;
        goto LAB_0801bdfa;
      }
      local_1c = uVar15 << 0x10;
    }
    local_20._0_3_ = CONCAT12((char)local_1c,(short)local_20);
    local_20 = CONCAT13((char)(local_1c >> 8),(uint3)local_20);
LAB_0801be68:
    local_28 = uVar1;
    uVar11 = FUN_0801ef94(uVar1);
    local_28 = 4;
    puVar12 = (uint *)FUN_08023084(&local_24,8,uVar11,0);
    return puVar12;
  }
  if (bVar14 < 0x42) {
    if (bVar14 != 4) {
      if (bVar14 != 0x11) {
        if (bVar14 != 0x40) {
          return puVar12;
        }
        if (*(char *)((int)puVar12 + 3) == '\x01') {
          local_20 = *puVar19;
          puVar12 = (uint *)FUN_0801b55c(local_20);
          return puVar12;
        }
        if (*(char *)((int)puVar12 + 3) == '\x02') {
          local_20 = *puVar19;
          puVar12 = (uint *)FUN_0801b764(local_20);
          return puVar12;
        }
        if (*(char *)((int)puVar12 + 3) == '\x03') {
          local_20 = *puVar19;
          local_18 = (uint *)0x0;
          while ((local_18 < (uint)*DAT_0801b918 &&
                 (abStack_70[(int)local_18 + 0x5d] =
                       (char)*(undefined2 *)(DAT_0801b91c + (int)local_18 * 2 + 0x102) + 0x28,
                 (byte)local_18 < 4))) {
            local_18 = (uint *)(uint)(byte)((byte)local_18 + 1);
          }
          local_18 = (uint *)local_20;
          uVar11 = FUN_0801ef94(local_20);
          local_18 = (uint *)&Reset;
          FUN_08023084(abStack_70 + 0x5c,7,uVar11,0);
          return local_18;
        }
        if (*(char *)((int)puVar12 + 3) == '\x04') {
          local_20 = *puVar19;
          VectorFloatToUnsigned(*DAT_0801b9d4,3);
          VectorFloatToUnsigned(*DAT_0801b9d8,3);
          local_18 = (uint *)local_20;
          uVar11 = FUN_0801ef94(local_20);
          local_18 = (uint *)0x4;
          puVar12 = (uint *)FUN_08023084(abStack_70 + 0x5c,8,uVar11,0);
          return puVar12;
        }
        if (*(char *)((int)puVar12 + 3) == '\x05') {
          local_20 = *puVar19;
          local_18 = (uint *)local_20;
          uVar11 = FUN_0801ef94(local_20);
          local_18 = (uint *)0x4;
          puVar12 = (uint *)FUN_08023084(abStack_70 + 0x5c,1,uVar11,0);
          return puVar12;
        }
        if (*(char *)((int)puVar12 + 3) != '\x05') {
          if ((uint *)(uint)*(byte *)((int)puVar12 + 3) == (uint *)&MemManage) {
            local_20 = *puVar19;
            puVar12 = (uint *)FUN_0801ba30(local_20);
            return puVar12;
          }
          return (uint *)(uint)*(byte *)((int)puVar12 + 3);
        }
        if (*param_2 == '\0') {
          if (*DAT_0802120c == 0) goto LAB_0801b518;
          *DAT_0802120c = extraout_r2;
          uVar11 = 0;
        }
        else {
          if ((*param_2 != '\x01') || (1 < *DAT_0802120c)) goto LAB_0801b518;
          *DAT_0802120c = 1;
          uVar11 = 1;
        }
        FUN_08021fd4(uVar11);
LAB_0801b518:
        local_20 = *puVar19;
        local_18 = (uint *)local_20;
        uVar11 = FUN_0801ef94(local_20);
        local_18 = (uint *)0x4;
        puVar12 = (uint *)FUN_08023084(abStack_70 + 0x5c,1,uVar11,0);
        return puVar12;
      }
      local_1c = *puVar12;
      local_18 = (uint *)*puVar19;
      local_24 = (char *)0x0;
      local_20 = 0;
      FUN_08008200(&local_48,0x20);
      FUN_08008200(abStack_70,0x20);
      local_4c = 0;
      local_50 = 0;
      uVar15 = local_28 >> 8;
      local_28 = uVar15 << 8;
      local_18._0_3_ = CONCAT12(4,(undefined2)local_18);
      uVar7 = (undefined2)(local_1c >> 0x10);
      if (local_1c._3_1_ == 1) {
        local_48 = 0x41;
        bVar13 = *DAT_0801b398;
        local_46 = (char)(((uint)*DAT_0801b398 % 100) / 10);
        bVar14 = *DAT_0801b398;
      }
      else {
        if (local_1c._3_1_ != 2) {
          if ((uint *)(uint)local_1c._3_1_ != (uint *)0x3) {
            return (uint *)(uint)local_1c._3_1_;
          }
          local_24 = (char *)(local_1c >> 0x10);
          local_24._0_2_ = uVar7;
          if ((*DAT_0801b394 < 0x20) && (*DAT_0801b394 != 0)) {
            local_74 = 0;
            if (*DAT_0801b394 < 0x18) {
              for (; local_74 < *DAT_0801b394; local_74 = local_74 + 1) {
                abStack_70[local_74] = DAT_0801b394[local_74 + 1];
              }
              local_50 = *DAT_0801b394;
            }
            else {
              for (; local_74 < 0x18; local_74 = local_74 + 1) {
                abStack_70[local_74] = DAT_0801b394[local_74 + 1];
              }
              local_50 = 0x18;
            }
            local_4c = local_50 >> 3;
            local_28 = CONCAT31(local_28._1_3_,local_50) & 0xffffff07;
            if ((byte)local_28 != '\0') {
              local_4c = local_4c + 1;
            }
          }
          else {
            local_4c = 0;
            local_50 = 0;
            local_28 = uVar15 << 8;
          }
          local_24._0_3_ = CONCAT12(local_50,(undefined2)local_24);
          local_24 = (char *)(uint)(uint3)local_24;
          local_20 = CONCAT31(local_20._1_3_,local_4c);
          uVar7 = FUN_0800c754(abStack_70,local_50);
          uVar15 = (uint)local_18;
          uVar11 = local_20;
          local_20._0_2_ = CONCAT11((char)uVar7,(undefined1)local_20);
          local_20._3_1_ = SUB41(uVar11,3);
          local_20._0_3_ = CONCAT12((char)((ushort)uVar7 >> 8),(short)local_20);
          local_18 = (uint *)((uint)local_18 & 0xffffff);
          uVar11 = FUN_0801ef94((uint)CONCAT12(local_18._2_1_,CONCAT11(local_18._1_1_,(char)uVar15))
                               );
          FUN_08023084(&local_24,7,uVar11,0,4);
          if (local_4c < 2) {
            if ((uint *)(uint)local_4c != (uint *)0x1) {
              return (uint *)(uint)local_4c;
            }
            local_18 = (uint *)CONCAT13(1,(undefined3)local_18);
            if (local_50 < 8) {
              uVar11 = FUN_0801ef94(CONCAT13(1,(undefined3)local_18));
              pbVar10 = abStack_70 + (uint)local_74 * 8;
              uVar15 = (uint)local_50;
              goto LAB_0801b154;
            }
          }
          else {
            local_18 = (uint *)CONCAT13(1,(undefined3)local_18);
            for (local_74 = 0; (int)(uint)local_74 < (int)(local_4c - 1); local_74 = local_74 + 1) {
              uVar11 = FUN_0801ef94(local_18);
              FUN_08023084(abStack_70 + (uint)local_74 * 8,8,uVar11,0,4);
              local_18 = (uint *)CONCAT13(local_18._3_1_ + '\x01',(undefined3)local_18);
            }
            if ((byte)local_28 != '\0') {
              uVar11 = FUN_0801ef94(local_18);
              pbVar10 = abStack_70 + (uint)local_74 * 8;
              uVar15 = local_28 & 0xff;
              goto LAB_0801b154;
            }
            if ((uint *)(local_28 & 0xff) != (uint *)0x0) {
              return (uint *)(local_28 & 0xff);
            }
          }
          uVar11 = FUN_0801ef94(local_18);
          pbVar10 = abStack_70 + (uint)local_74 * 8;
          uVar15 = 8;
          goto LAB_0801b154;
        }
        uVar15 = VectorFloatToUnsigned((*DAT_0801b39c + DAT_0801b3a0) * 10.0,3);
        bVar14 = (byte)uVar15;
        local_48 = 0x56;
        local_46 = (char)(((uVar15 & 0xff) % 100) / 10);
        bVar13 = bVar14;
      }
      local_46 = local_46 + '0';
      local_47 = bVar13 / 100 + 0x30;
      local_45 = 0x2e;
      local_44 = bVar14 % 10 + 0x30;
      local_24._0_3_ = CONCAT12(5,uVar7);
      local_24 = (char *)(uint)(uint3)local_24;
      local_20 = CONCAT31(local_20._1_3_,1);
      uVar7 = FUN_0800c754(&local_48,5);
      uVar15 = (uint)local_18;
      uVar11 = local_20;
      local_20._0_2_ = CONCAT11((char)uVar7,(undefined1)local_20);
      local_20._3_1_ = SUB41(uVar11,3);
      local_20._0_3_ = CONCAT12((char)((ushort)uVar7 >> 8),(short)local_20);
      local_18 = (uint *)((uint)local_18 & 0xffffff);
      uVar11 = FUN_0801ef94((uint)CONCAT12(local_18._2_1_,CONCAT11(local_18._1_1_,(char)uVar15)));
      FUN_08023084(&local_24,7,uVar11,0,4);
      local_18 = (uint *)CONCAT13(1,(undefined3)local_18);
      uVar11 = FUN_0801ef94(CONCAT13(1,(undefined3)local_18));
      uVar15 = 5;
      pbVar10 = &local_48;
LAB_0801b154:
      puVar12 = (uint *)FUN_08023084(pbVar10,uVar15,uVar11,0,4);
      return puVar12;
    }
    uVar15 = *puVar12;
    local_20 = param_3 & 0xff;
    local_2c = (uint)local_2c._2_2_ << 0x10;
    local_34 = 0;
    local_30 = 0;
    puVar12 = (uint *)(uVar15 >> 8 & 0xff);
    if (puVar12 != (uint *)(uint)*(byte *)(DAT_080215d0 + 6)) {
      return puVar12;
    }
    puVar12 = (uint *)(uVar15 >> 0x10 & 0xff);
    if (puVar12 != (uint *)&Reset) {
      return puVar12;
    }
    local_28._3_1_ = (byte)(uVar15 >> 0x18);
    puVar20 = (undefined4 *)(DAT_080215d0 + 0x1a);
    local_28 = uVar15;
    local_24 = param_2;
    if (local_28._3_1_ == 0) {
      *(char *)(DAT_080215d0 + 10) = *param_2;
      *(char *)(iVar2 + 0xb) = param_2[1];
      *(undefined2 *)(iVar2 + 0x16) = *(undefined2 *)(param_2 + 2);
      *(ushort *)(iVar2 + 0x12) = (ushort)(byte)param_2[4];
      *(undefined2 *)(iVar2 + 0x14) = 0;
      *(undefined2 *)(iVar2 + 0x18) = *(undefined2 *)(param_2 + 5);
      *(undefined1 *)puVar20 = *(undefined1 *)(iVar2 + 6);
      *(undefined1 *)(iVar2 + 0x1b) = *(undefined1 *)(DAT_080215d0 + 0x1e);
      *(undefined1 *)(iVar2 + 0x1c) = 10;
      *(undefined1 *)(iVar2 + 0x1d) = 0;
      if (((*(char *)(iVar2 + 10) == '\x11') && (*(char *)(iVar2 + 0xb) == '\x03')) ||
         ((*(char *)(iVar2 + 10) == 'D' && (*(char *)(iVar2 + 0xb) == -0xf)))) {
        *(char *)(iVar2 + 3) = (char)*(undefined2 *)(iVar2 + 0x16);
        if (0x18 < *(ushort *)(iVar2 + 0x16)) {
          *(undefined1 *)(iVar2 + 0x1d) = 2;
          *(undefined1 *)(iVar2 + 3) = 0x18;
        }
      }
      else {
        if ((*(char *)(iVar2 + 10) == 'D') && (*(char *)(iVar2 + 0xb) == -0xe)) {
          if (*(ushort *)(iVar2 + 0x16) < 0x801) goto LAB_080212de;
        }
        else if ((*(char *)(iVar2 + 10) != 'D') ||
                ((*(char *)(iVar2 + 0xb) != -0xd || (*(ushort *)(iVar2 + 0x16) < 0xff))))
        goto LAB_080212de;
        *(undefined1 *)(iVar2 + 0x1d) = 2;
      }
LAB_080212de:
      local_34 = (uint)*(ushort *)(iVar2 + 10);
      local_38 = *puVar20;
      uVar11 = FUN_0801ef94(local_38);
      local_38 = 4;
      puVar12 = (uint *)FUN_0800a670(&local_34,2,uVar11,0);
      return puVar12;
    }
    if ((*(char *)(DAT_080215d0 + 10) == '\x11') && (*(char *)(DAT_080215d0 + 0xb) == '\x03')) {
      if ((local_28._3_1_ == 0) || (*(ushort *)(DAT_080215d0 + 0x12) < (ushort)local_28._3_1_)) {
LAB_08021592:
        *(undefined1 *)(DAT_080215d0 + 0x1d) = 2;
        goto LAB_08021594;
      }
      local_38 = (uint)local_38._1_3_ << 8;
      while ((local_38 & 0xff) < local_20) {
        *(char *)(iVar3 + (local_38 & 0xff) + (local_28._3_1_ - 1) * 8) = param_2[local_38 & 0xff];
        local_38 = CONCAT31(local_38._1_3_,(char)local_38 + '\x01');
      }
      *(short *)(iVar2 + 0x14) = *(short *)(iVar2 + 0x14) + 1;
      if (*(ushort *)(iVar2 + 0x14) < *(ushort *)(iVar2 + 0x12)) {
LAB_0802158e:
        *(undefined1 *)(iVar2 + 0x1d) = 0;
        goto LAB_08021594;
      }
      *(undefined2 *)(iVar2 + 0x14) = 0;
      sVar9 = FUN_0800c754(DAT_080215d4,*(undefined2 *)(iVar2 + 0x16));
      local_2c = CONCAT22(local_2c._2_2_,sVar9);
      if (sVar9 == *(short *)(iVar2 + 0x18)) {
        *(undefined1 *)(iVar2 + 0x1d) = 0;
        *(undefined1 *)(iVar2 + 2) = 1;
        uVar15 = local_28;
        goto LAB_08021594;
      }
    }
    else if ((*(char *)(DAT_080215d0 + 10) == 'D') && (*(char *)(DAT_080215d0 + 0xb) == -0xf)) {
      if ((local_28._3_1_ == 0) || (*(ushort *)(DAT_080215d0 + 0x12) < (ushort)local_28._3_1_))
      goto LAB_08021592;
      iVar21 = DAT_080215d4 + 0x18;
      local_38 = (uint)local_38._1_3_ << 8;
      while ((local_38 & 0xff) < local_20) {
        *(char *)(iVar21 + (local_38 & 0xff) + (local_28._3_1_ - 1) * 8) = param_2[local_38 & 0xff];
        local_38 = CONCAT31(local_38._1_3_,(char)local_38 + '\x01');
      }
      *(short *)(iVar2 + 0x14) = *(short *)(iVar2 + 0x14) + 1;
      if (*(ushort *)(iVar2 + 0x14) < *(ushort *)(iVar2 + 0x12)) goto LAB_0802158e;
      *(undefined2 *)(iVar2 + 0x14) = 0;
      sVar9 = FUN_0800c754(DAT_080215d4 + 0x18,*(undefined2 *)(iVar2 + 0x16));
      local_2c = CONCAT22(local_2c._2_2_,sVar9);
      if (sVar9 == *(short *)(iVar2 + 0x18)) {
        *(undefined1 *)(iVar2 + 0x1d) = 0;
        iVar18 = DAT_080215d4 + -0x18;
        local_38 = local_38 & 0xffffff00;
        while ((local_38 & 0xff) < 0x18) {
          *(undefined1 *)(iVar18 + (local_38 & 0xff)) = *(undefined1 *)(iVar21 + (local_38 & 0xff));
          local_38 = CONCAT31(local_38._1_3_,(char)local_38 + '\x01');
        }
        FUN_080224d4();
        uVar15 = local_28;
        goto LAB_08021594;
      }
    }
    else if ((*(char *)(DAT_080215d0 + 10) == 'D') && (*(char *)(DAT_080215d0 + 0xb) == -0xe)) {
      if ((local_28._3_1_ == 0) || (*(ushort *)(DAT_080215d0 + 0x12) < (ushort)local_28._3_1_))
      goto LAB_08021592;
      local_38 = (uint)local_38._1_3_ << 8;
      while ((local_38 & 0xff) < local_20) {
        puVar17[(local_38 & 0xff) + (local_28._3_1_ - 1) * 8] = param_2[local_38 & 0xff];
        local_38 = CONCAT31(local_38._1_3_,(char)local_38 + '\x01');
      }
      *(short *)(iVar2 + 0x14) = *(short *)(iVar2 + 0x14) + 1;
      if (*(ushort *)(iVar2 + 0x14) < *(ushort *)(iVar2 + 0x12)) goto LAB_0802158e;
      *(undefined2 *)(iVar2 + 0x14) = 0;
      sVar9 = FUN_0800c754(DAT_080215d8,*(undefined2 *)(iVar2 + 0x16));
      local_2c = CONCAT22(local_2c._2_2_,sVar9);
      if (sVar9 == *(short *)(iVar2 + 0x18)) {
        *(undefined1 *)(iVar2 + 0x1d) = 0;
        FUN_0800fa6c(DAT_080215dc,DAT_080215d0 + 0x16,2);
        sVar9 = *(short *)(iVar2 + 0x16);
        uVar11 = DAT_080215e0;
        puVar17 = DAT_080215d8;
LAB_08021584:
        FUN_0800fa6c(uVar11,puVar17,sVar9);
        uVar15 = local_28;
        goto LAB_08021594;
      }
    }
    else {
      if ((*(char *)(DAT_080215d0 + 10) != 'D') || (*(char *)(DAT_080215d0 + 0xb) != -0xd))
      goto LAB_08021594;
      if ((local_28._3_1_ == 0) || (*(ushort *)(DAT_080215d0 + 0x12) < (ushort)local_28._3_1_))
      goto LAB_08021592;
      local_38 = (uint)local_38._1_3_ << 8;
      while ((local_38 & 0xff) < local_20) {
        puVar4[(local_38 & 0xff) + (uint)local_28._3_1_ * 8 + -6] = param_2[local_38 & 0xff];
        local_38 = CONCAT31(local_38._1_3_,(char)local_38 + '\x01');
      }
      *(short *)(iVar2 + 0x14) = *(short *)(iVar2 + 0x14) + 1;
      if (*(ushort *)(iVar2 + 0x14) < *(ushort *)(iVar2 + 0x12)) goto LAB_0802158e;
      *(undefined2 *)(iVar2 + 0x14) = 0;
      sVar9 = FUN_0800c754(puVar4 + 2,*(undefined2 *)(iVar2 + 0x16));
      local_2c = CONCAT22(local_2c._2_2_,sVar9);
      if (sVar9 == *(short *)(iVar2 + 0x18)) {
        *(undefined1 *)(iVar2 + 0x1d) = 0;
        *puVar4 = (char)*(undefined2 *)(iVar2 + 0x16);
        puVar4[1] = (char)((ushort)*(undefined2 *)(iVar2 + 0x16) >> 8);
        sVar9 = *(short *)(iVar2 + 0x16) + 2;
        uVar11 = DAT_080215e8;
        puVar17 = DAT_080215e4;
        goto LAB_08021584;
      }
    }
    *(undefined1 *)(iVar2 + 0x1d) = 3;
    uVar15 = local_28;
LAB_08021594:
    local_28 = uVar15;
    local_34 = CONCAT22(local_34._2_2_,*(undefined2 *)(iVar2 + 10));
    local_38 = *puVar20;
    uVar11 = FUN_0801ef94(local_38);
    local_38 = 4;
    puVar12 = (uint *)FUN_08023084(&local_34,2,uVar11,0);
    return puVar12;
  }
  local_18 = (uint *)param_2;
  if (bVar14 == 0x42) {
    local_30 = *puVar19;
    uVar15 = *puVar12;
    bVar14 = 0;
    local_2c = 0;
    local_28 = 0;
    local_1c._3_1_ = (byte)(uVar15 >> 0x18);
    local_20 = local_30;
    local_1c = uVar15;
    if (local_1c._3_1_ == '\x01') {
      local_2c = 0x3010000;
      uVar11 = FUN_0801ef94(local_30);
      uVar16 = 4;
    }
    else if (local_1c._3_1_ == '\x03') {
      if (*(char *)(DAT_0801c0bc + 6) != '\x14') {
        return (uint *)0x0;
      }
      if (*(char *)(DAT_0801c0bc + 5) != '\x01') {
        if ((*DAT_0801c0c0 == '\0') && (*DAT_0801c0c4 == '\0')) {
          *(char *)(DAT_0801c0bc + 4) = *param_2;
          if ((*(char *)(iVar18 + 4) == '\x01') || (*(char *)(iVar18 + 4) == '\x02')) {
            *(undefined1 *)(iVar18 + 5) = 1;
          }
        }
        else {
          *(undefined1 *)(DAT_0801c0bc + 4) = 0;
          *(undefined1 *)(iVar18 + 5) = 3;
        }
      }
      uVar11 = FUN_0801ef94(local_30);
      uVar16 = 1;
    }
    else {
      if (local_1c._3_1_ != '\x04') {
        return (uint *)0x0;
      }
      if ((*(char *)(DAT_0801c0b8 + 0x3a) == '\0') && (*(char *)(DAT_0801c0b8 + 0x3b) == '\0')) {
        bVar14 = *(byte *)(DAT_0801c0c8 + 0x14) >> 1;
      }
      local_2c = (uint)CONCAT12(bVar14,(short)(*DAT_0801c0b4 / 0xe10));
      uVar11 = FUN_0801ef94(local_30);
      uVar16 = 3;
    }
    local_30 = 4;
    puVar12 = (uint *)FUN_08023084(&local_2c,uVar16,uVar11,0);
    return puVar12;
  }
  if (bVar14 != 0x44) {
    return puVar12;
  }
  uVar7 = (undefined2)*puVar19;
  cVar6 = *(char *)((int)puVar12 + 7);
  local_34 = *puVar12;
  local_30 = 0;
  local_40 = (uint)local_40._2_2_ << 0x10;
  uVar15 = (uint)local_2c._2_2_;
  local_2c = uVar15 << 0x10;
  local_38 = local_38 & 0xffff0000;
  local_1c._3_1_ = (byte)(local_34 >> 0x18);
  local_1c = local_34;
  if (local_1c._3_1_ == '\x01') {
    local_20._0_3_ = CONCAT12(4,uVar7);
    local_20 = CONCAT13(cVar6,(uint3)local_20);
    local_40 = CONCAT22(uVar8,0x18);
    local_34._0_3_ = CONCAT12(0x18,(short)(local_34 >> 0x10));
    local_34 = (uint)(uint3)local_34;
    local_30 = 3;
    uVar7 = FUN_0800c754(DAT_0801c594,0x18);
    uVar15 = local_20;
    uVar11 = local_30;
    local_30._0_2_ = CONCAT11((char)uVar7,(undefined1)local_30);
    local_30._3_1_ = SUB41(uVar11,3);
    local_30._0_3_ = CONCAT12((char)((ushort)uVar7 >> 8),(undefined2)local_30);
    local_20 = local_20 & 0xffffff;
    local_40 = (uint)CONCAT12(local_20._2_1_,CONCAT11(local_20._1_1_,(char)uVar15));
    uVar11 = FUN_0801ef94(local_40);
    local_40 = 4;
    FUN_0800a670(&local_34,7,uVar11,0);
    local_20 = CONCAT13(1,(uint3)local_20);
    local_40 = CONCAT13(1,(uint3)local_20);
    uVar11 = FUN_0801ef94(local_40);
    local_40 = 4;
    FUN_08023084(DAT_0801c594,8,uVar11,0);
    local_20 = CONCAT13(2,(uint3)local_20);
    local_40 = CONCAT13(2,(uint3)local_20);
    uVar11 = FUN_0801ef94(local_40);
    local_40 = 4;
    FUN_08023084(DAT_0801c594 + 8,8,uVar11,0);
    local_20 = CONCAT13(3,(uint3)local_20);
    local_40 = CONCAT13(3,(uint3)local_20);
    uVar11 = FUN_0801ef94(local_40);
    uVar16 = 8;
    puVar20 = (undefined4 *)(DAT_0801c594 + 0x10);
    goto LAB_0801c2a0;
  }
  if (local_1c._3_1_ == '\x02') {
    local_20._0_3_ = CONCAT12(4,uVar7);
    local_20 = CONCAT13(cVar6,(uint3)local_20);
    local_34 = local_34 >> 0x10;
    local_2c = uVar15 << 0x10;
    FUN_0800f964(DAT_0801c598,&local_2c,2);
    if ((ushort)local_2c == -1) {
      local_2c = (uint)local_2c._2_2_ << 0x10;
    }
    else if (0x800 < (local_2c & 0xffff)) {
      local_2c = CONCAT22(local_2c._2_2_,0x800);
    }
    local_34._0_3_ = CONCAT12((char)local_2c,(undefined2)local_34);
    local_34 = CONCAT13((char)(local_2c >> 8),(uint3)local_34);
    if ((ushort)local_2c != 0) {
      if ((local_2c & 7) == 0) {
        uVar8 = (ushort)local_2c >> 3;
      }
      else {
        uVar8 = ((ushort)local_2c >> 3) + 1;
      }
      local_38 = CONCAT22(local_38._2_2_,uVar8);
      local_30 = CONCAT31(local_30._1_3_,(char)uVar8);
      FUN_0800f964(DAT_0801c5a0,DAT_0801c59c,local_2c & 0xffff);
      uVar7 = FUN_0800c754(DAT_0801c59c,local_2c & 0xffff);
      uVar15 = local_20;
      uVar11 = local_30;
      local_30._0_2_ = CONCAT11((char)uVar7,(undefined1)local_30);
      local_30._3_1_ = SUB41(uVar11,3);
      local_30._0_3_ = CONCAT12((char)((ushort)uVar7 >> 8),(undefined2)local_30);
      local_20 = local_20 & 0xffffff;
      local_40 = (uint)CONCAT12(local_20._2_1_,CONCAT11(local_20._1_1_,(char)uVar15));
      uVar11 = FUN_0801ef94(local_40);
      local_40 = 4;
      FUN_08023084(&local_34,7,uVar11,0);
      iVar21 = DAT_0801c59c;
      for (local_3c = 0; (uint *)(uint)local_3c < (uint *)(local_38 & 0xffff);
          local_3c = local_3c + 1) {
        cVar6 = local_3c + 1;
        local_20 = CONCAT13(cVar6,(uint3)local_20);
        if (((uint)local_3c == (local_38 & 0xffff) - 1) && ((local_2c & 7) != 0)) {
          local_40 = CONCAT13(cVar6,(uint3)local_20);
          uVar11 = FUN_0801ef94(local_40);
          uVar15 = local_2c & 7;
          iVar18 = (uint)local_3c * 8;
        }
        else {
          local_40 = CONCAT13(cVar6,(uint3)local_20);
          uVar11 = FUN_0801ef94(local_40);
          iVar18 = (uint)local_3c << 3;
          uVar15 = 8;
        }
        local_40 = 4;
        FUN_08023084(iVar21 + iVar18,uVar15,uVar11,0);
      }
      return (uint *)(uint)local_3c;
    }
LAB_0801c38c:
    uVar15 = local_20;
    local_30 = local_30 & 0xff000000;
    local_20 = local_20 & 0xffffff;
    local_40 = (uint)CONCAT12(local_20._2_1_,CONCAT11(local_20._1_1_,(char)uVar15));
    uVar11 = FUN_0801ef94(local_40);
    uVar16 = 7;
  }
  else {
    if (local_1c._3_1_ == '\x03') {
      local_20._0_3_ = CONCAT12(4,uVar7);
      local_20 = CONCAT13(cVar6,(uint3)local_20);
      local_34 = local_34 >> 0x10;
      local_2c = uVar15 << 0x10;
      FUN_0800f964(DAT_0801c5a4,&local_2c,2);
      iVar21 = DAT_0801c5a8;
      if ((ushort)local_2c == 0xffff) {
        local_2c = (uint)local_2c._2_2_ << 0x10;
      }
      else if (0xfe < (ushort)local_2c) {
        local_2c = CONCAT22(local_2c._2_2_,0xfe);
      }
      local_34._0_3_ = CONCAT12((char)local_2c,(undefined2)local_34);
      local_34 = CONCAT13((char)(local_2c >> 8),(uint3)local_34);
      if ((ushort)local_2c != 0) {
        if ((local_2c & 7) == 0) {
          uVar8 = (ushort)local_2c >> 3;
        }
        else {
          uVar8 = ((ushort)local_2c >> 3) + 1;
        }
        local_38 = CONCAT22(local_38._2_2_,uVar8);
        local_30 = CONCAT31(local_30._1_3_,(char)uVar8);
        FUN_0800f964(DAT_0801c5a4 + 2,DAT_0801c5a8 + 2,local_2c & 0xffff);
        uVar7 = FUN_0800c754(iVar21 + 2,local_2c & 0xffff);
        uVar15 = local_20;
        uVar11 = local_30;
        local_30._0_2_ = CONCAT11((char)uVar7,(undefined1)local_30);
        local_30._3_1_ = SUB41(uVar11,3);
        local_30._0_3_ = CONCAT12((char)((ushort)uVar7 >> 8),(undefined2)local_30);
        local_20 = local_20 & 0xffffff;
        local_40 = (uint)CONCAT12(local_20._2_1_,CONCAT11(local_20._1_1_,(char)uVar15));
        uVar11 = FUN_0801ef94(local_40);
        local_40 = 4;
        FUN_08023084(&local_34,7,uVar11,0);
        for (local_3c = 0; (uint *)(uint)local_3c < (uint *)(local_38 & 0xffff);
            local_3c = local_3c + 1) {
          cVar6 = local_3c + 1;
          local_20 = CONCAT13(cVar6,(uint3)local_20);
          if (((uint)local_3c == (local_38 & 0xffff) - 1) && ((local_2c & 7) != 0)) {
            local_40 = CONCAT13(cVar6,(uint3)local_20);
            uVar11 = FUN_0801ef94(local_40);
            uVar15 = local_2c & 7;
          }
          else {
            local_40 = CONCAT13(cVar6,(uint3)local_20);
            uVar11 = FUN_0801ef94(local_40);
            uVar15 = 8;
          }
          local_40 = 4;
          FUN_08023084(iVar21 + (uint)local_3c * 8 + 2,uVar15,uVar11,0);
        }
        return (uint *)(uint)local_3c;
      }
      goto LAB_0801c38c;
    }
    if (((local_1c._3_1_ != -0xf) && (local_1c._3_1_ != -0xe)) && (local_1c._3_1_ != -0xd)) {
      return (uint *)0xa;
    }
    local_20._0_3_ = CONCAT12(10,uVar7);
    local_20 = (uint)(uint3)local_20;
    local_34 = local_34 >> 0x10;
    local_40 = (uint)CONCAT12(10,uVar7);
    uVar11 = FUN_0801ef94(local_40);
    uVar16 = 2;
  }
  puVar20 = &local_34;
LAB_0801c2a0:
  local_40 = 4;
  puVar12 = (uint *)FUN_08023084(puVar20,uVar16,uVar11,0);
  return puVar12;
}



// ---------------------------------------------------------------------------
// Function: FUN_08021748 at 0x08021748
// ---------------------------------------------------------------------------

void FUN_08021748(void)

{
  int iVar1;
  undefined1 *puVar2;
  undefined2 *puVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  
  FUN_0801f360();
  FUN_0802302c();
  puVar2 = DAT_0802183c;
  iVar1 = DAT_08021838;
  DAT_0802183c[2] = *(undefined1 *)(DAT_08021838 + 0x16);
  *(undefined1 *)(iVar1 + 0x16) = 0;
  puVar2[1] = 0;
  puVar3 = DAT_08021840;
  *(undefined2 *)(puVar2 + 0xe) = *DAT_08021840;
  *puVar3 = *(undefined2 *)(DAT_08021844 + 8);
  piVar5 = DAT_0802184c;
  iVar4 = DAT_08021848;
  piVar6 = (int *)(puVar2 + 0x14);
  do {
    if ((9 < *(ushort *)(puVar2 + 4)) || (*(char *)(iVar4 + 0x3d) != '\0')) {
      *(undefined2 *)(puVar2 + 4) = 0;
      *piVar6 = *piVar5;
      FUN_0801f580();
    }
    if ((99 < *(ushort *)(puVar2 + 6)) || (*(char *)(iVar4 + 0x3d) != '\0')) {
      *(undefined2 *)(puVar2 + 6) = 0;
      FUN_0801f654();
      if ((puVar2[1] == '\0') &&
         (*(short *)(puVar2 + 0xc) = *(short *)(puVar2 + 0xc) + 1, 0x707 < *(ushort *)(puVar2 + 0xc)
         )) {
        *(undefined2 *)(puVar2 + 0xc) = 0;
        puVar2[1] = 1;
        *(undefined1 *)(iVar1 + 0x16) = puVar2[2];
        *puVar3 = *(undefined2 *)(puVar2 + 0xe);
      }
    }
    if ((399 < *(ushort *)(puVar2 + 8)) || (*(char *)(iVar4 + 0x3d) != '\0')) {
      *(undefined2 *)(puVar2 + 8) = 0;
      FUN_0801f6cc();
      *(int *)(puVar2 + 0x18) = *piVar5;
      if (*piVar6 == *(int *)(puVar2 + 0x18)) {
        FUN_0800db18(2);
        *piVar6 = *piVar5;
        if (*piVar6 == *(int *)(puVar2 + 0x18)) {
          *puVar2 = 1;
          *DAT_08021850 = 0;
          FUN_0801806c();
          FUN_080161bc(1);
          FUN_08018198(*DAT_08021854,DAT_08021854[1],DAT_08021854[2],DAT_08021854[3],DAT_08021854[4]
                       ,DAT_08021854[5]);
        }
      }
      else {
        *puVar2 = 0;
      }
    }
    FUN_0801f77c();
    FUN_0801f7b8();
  } while( true );
}



// ---------------------------------------------------------------------------
// Function: FUN_08021858 at 0x08021858
// ---------------------------------------------------------------------------

void FUN_08021858(void)

{
  *(undefined4 *)(DAT_08021860 + 0x10) = 4;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08021864 at 0x08021864
// ---------------------------------------------------------------------------

void FUN_08021864(void)

{
  *(undefined4 *)(DAT_0802186c + 0x14) = 4;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08021870 at 0x08021870
// ---------------------------------------------------------------------------

undefined4 FUN_08021870(undefined4 param_1,uint param_2)

{
  int iVar1;
  byte local_18 [8];
  undefined4 uStack_10;
  uint local_c;
  
  local_18[0] = 0;
  uStack_10 = param_1;
  local_c = param_2;
  FUN_080122f0(1,local_18);
  if ((int)((uint)local_18[0] << 0x19) < 0) {
    iVar1 = FUN_08009c34(param_1,DAT_080218b0,local_c & 0xff);
    if (iVar1 != 0) {
      return 1;
    }
    *DAT_080218b4 = 1;
  }
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_080218b8 at 0x080218b8
// ---------------------------------------------------------------------------

longlong FUN_080218b8(undefined4 param_1,uint param_2,undefined4 param_3,uint param_4)

{
  uint uVar1;
  byte *pbVar2;
  undefined2 uVar3;
  int iVar4;
  uint in_fpscr;
  float fVar5;
  ushort local_20;
  undefined2 uStack_1e;
  uint local_1c;
  float local_18;
  uint local_14;
  
  pbVar2 = DAT_080219b4;
  uStack_1e = (undefined2)((uint)param_1 >> 0x10);
  local_14 = param_4 & 0xffffff00;
  local_20 = 0;
  local_1c = param_2 & 0xffffff00;
  local_18 = DAT_080219b0;
LAB_080218d4:
  do {
    FUN_08011464();
    iVar4 = FUN_080122f0(0x6e,&local_14,1);
    if ((iVar4 != 0) && ((char)local_14 != -0x33)) {
      FUN_08012720(0x6e,0xcd,1);
      FUN_0800db18(0x15e);
    }
    iVar4 = FUN_0800d428(&local_18);
    if (iVar4 == 0) {
      FUN_080219c0();
      FUN_0800db18(10);
      FUN_0801ca54();
    }
    else {
      fVar5 = (float)VectorUnsignedToFloat((uint)*pbVar2,(byte)(in_fpscr >> 0x16) & 3);
      uVar1 = in_fpscr & 0xfffffff | (uint)(local_18 < fVar5) << 0x1f;
      in_fpscr = uVar1 | (uint)(NAN(local_18) || NAN(fVar5)) << 0x1c;
      if ((byte)(uVar1 >> 0x1f) == ((byte)(in_fpscr >> 0x1c) & 1)) {
        local_1c = local_1c & 0xffffff00;
        while ((byte)local_1c < 5) {
          FUN_0800db18(100);
          iVar4 = FUN_0800d428(&local_18);
          if (iVar4 != 0) {
            fVar5 = (float)VectorUnsignedToFloat((uint)*pbVar2,(byte)(in_fpscr >> 0x16) & 3);
            in_fpscr = in_fpscr & 0xfffffff;
            if (local_18 < fVar5) break;
          }
          local_1c = CONCAT31(local_1c._1_3_,(byte)local_1c + 1);
        }
        if ((local_1c & 0xff) == 5) {
          thunk_FUN_0800d5fc();
          uVar3 = FUN_0800d5cc();
          *DAT_080219b8 = uVar3;
          if (*DAT_080219bc == '\0') {
            FUN_0800c940();
            FUN_0800acd8();
          }
          return (ulonglong)CONCAT42(local_1c,uStack_1e) << 0x10;
        }
        goto LAB_080218d4;
      }
    }
    local_20 = local_20 + 1;
    if (1 < local_20) {
      return CONCAT44(local_1c,CONCAT22(uStack_1e,local_20));
    }
  } while( true );
}



// ---------------------------------------------------------------------------
// Function: FUN_080219c0 at 0x080219c0
// ---------------------------------------------------------------------------

void FUN_080219c0(void)

{
  *DAT_080219c8 = 0;
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080219cc at 0x080219cc
// ---------------------------------------------------------------------------

void FUN_080219cc(void)

{
  undefined4 in_r3;
  undefined4 local_8;
  
  local_8 = in_r3;
  FUN_08017cb0(4,1);
  FUN_08017cb0(8,1);
  FUN_08017cb0(0x10,1);
  FUN_08017cb0(0x20,1);
  FUN_08017cb0(0x40,1);
  FUN_08017cb0(0x80,1);
  FUN_08017cb0(1);
  FUN_0801f478();
  *(uint *)(DAT_08021a44 + 0x1c) = *(uint *)(DAT_08021a44 + 0x1c) | 0x10000000;
  *DAT_08021a48 = *DAT_08021a48 | 8;
  FUN_08012984();
  local_8 = DAT_08021a4c;
  FUN_08009c48(&local_8,1);
  FUN_0800db18(8);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08021a50 at 0x08021a50
// ---------------------------------------------------------------------------

void FUN_08021a50(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  byte bVar2;
  undefined4 uStack_c;
  undefined4 local_8;
  
  uStack_c = param_3;
  local_8 = param_4;
  for (bVar2 = 0; bVar2 < 4; bVar2 = bVar2 + 1) {
    *(undefined1 *)((int)&uStack_c + (uint)bVar2) = *(undefined1 *)(param_1 + (uint)bVar2);
  }
  uVar1 = FUN_08016658(&uStack_c,4);
  local_8 = CONCAT31(local_8._1_3_,uVar1);
  FUN_0800f850(0x28e,&uStack_c,5);
  FUN_08019844(0,0x85);
  FUN_0801aa48(0xff);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08021b54 at 0x08021b54
// ---------------------------------------------------------------------------

void FUN_08021b54(uint param_1,undefined4 param_2)

{
  undefined1 local_10 [4];
  uint local_c;
  undefined4 local_8;
  
  local_8._0_1_ = (undefined1)param_2;
  local_10[0] = (undefined1)local_8;
  local_c = param_1;
  local_8 = param_2;
  FUN_080127e0(param_1 & 0xffff,local_10,1);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08021b70 at 0x08021b70
// ---------------------------------------------------------------------------

undefined4 FUN_08021b70(uint param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  char local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_14;
  uint local_10;
  uint local_c;
  undefined4 local_8;
  
  local_18 = '@';
  local_10._0_1_ = (undefined1)param_1;
  local_17 = (undefined1)local_10;
  local_c._0_1_ = (char)param_2;
  local_16 = (char)local_c;
  local_10 = param_1;
  local_c = param_2;
  local_8 = param_3;
  local_14 = FUN_08022fa2(&local_18,3);
  FUN_08012578();
  FUN_080126b0(0x40);
  iVar1 = FUN_080124a4();
  if (iVar1 == 0) {
    FUN_080126b0(local_10 & 0xff);
    iVar1 = FUN_080124a4();
    if (iVar1 == 0) {
      FUN_080126b0(local_c & 0xff);
      iVar1 = FUN_080124a4();
      if (iVar1 == 0) {
        FUN_080126b0(local_14);
        iVar1 = FUN_080124a4();
        if (iVar1 == 0) {
          FUN_0801260c();
          FUN_0800db18(5);
          if ((char)local_8 == '\0') {
            return 1;
          }
          FUN_080122f0(local_10 & 0xff,&local_18,1);
          if (local_18 == (char)local_c) {
            return 1;
          }
          return 0;
        }
      }
    }
  }
  FUN_0801260c();
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_08021c10 at 0x08021c10
// ---------------------------------------------------------------------------

undefined4 FUN_08021c10(uint param_1,undefined1 *param_2,uint param_3)

{
  int iVar1;
  char local_98 [120];
  byte local_20;
  undefined1 local_1c;
  uint local_18;
  undefined1 *puStack_14;
  uint local_10;
  
  local_98[0] = '@';
  local_18._0_1_ = (undefined1)param_1;
  local_98[1] = (undefined1)local_18;
  local_98[2] = *param_2;
  local_18 = param_1;
  puStack_14 = param_2;
  local_10 = param_3;
  local_1c = FUN_08022fa2(local_98,3);
  FUN_08012578();
  FUN_080126b0(0x40);
  iVar1 = FUN_080124a4();
  if (iVar1 == 0) {
    FUN_080126b0(local_18 & 0xff);
    iVar1 = FUN_080124a4();
    if (iVar1 == 0) {
      FUN_080126b0(*param_2);
      iVar1 = FUN_080124a4();
      if (iVar1 == 0) {
        FUN_080126b0(local_1c);
        iVar1 = FUN_080124a4();
        if (iVar1 == 0) {
          local_20 = 0;
          while( true ) {
            if ((int)((local_10 & 0xff) - 1) <= (int)(uint)local_20) {
              FUN_0801260c();
              FUN_0800db18(5);
              FUN_080122f0(local_18 & 0xff,local_98,local_10 & 0xff);
              local_20 = 0;
              while( true ) {
                if ((byte)local_10 <= local_20) {
                  return 1;
                }
                if (local_98[local_20] != param_2[local_20]) break;
                local_20 = local_20 + 1;
              }
              return 0;
            }
            FUN_080126b0(param_2[local_20 + 1]);
            iVar1 = FUN_080124a4();
            if (iVar1 != 0) break;
            FUN_08022fa2(param_2 + local_20 + 1,1);
            FUN_080126b0();
            iVar1 = FUN_080124a4();
            if (iVar1 != 0) break;
            local_20 = local_20 + 1;
          }
        }
      }
    }
  }
  FUN_0801260c();
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_08021d1c at 0x08021d1c
// ---------------------------------------------------------------------------

undefined4 FUN_08021d1c(uint param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  char local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_14;
  uint local_10;
  uint local_c;
  undefined4 local_8;
  
  local_18 = '@';
  local_10._0_1_ = (undefined1)param_1;
  local_17 = (undefined1)local_10;
  local_c._0_1_ = (undefined1)param_2;
  local_16 = (undefined1)local_c;
  local_10 = param_1;
  local_c = param_2;
  local_8 = param_3;
  local_14 = FUN_08022fa2(&local_18,3);
  FUN_08012578();
  FUN_080126b0(0x40);
  iVar1 = FUN_080124a4();
  if (iVar1 == 0) {
    FUN_080126b0(local_10 & 0xff);
    iVar1 = FUN_080124a4();
    if (iVar1 == 0) {
      FUN_080126b0(local_c & 0xff);
      iVar1 = FUN_080124a4();
      if (iVar1 == 0) {
        FUN_080126b0(local_14);
        iVar1 = FUN_080124a4();
        if (iVar1 == 0) {
          FUN_0801260c();
          FUN_0800db18(2);
          FUN_080122f0(local_10 & 0xff,&local_18,1);
          if (local_18 == (char)local_8) {
            return 1;
          }
          return 0;
        }
      }
    }
  }
  FUN_0801260c();
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_08021db6 at 0x08021db6
// ---------------------------------------------------------------------------

void FUN_08021db6(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  byte bVar2;
  undefined4 uStack_c;
  undefined4 local_8;
  
  uStack_c = param_3;
  local_8 = param_4;
  for (bVar2 = 0; bVar2 < 4; bVar2 = bVar2 + 1) {
    *(undefined1 *)((int)&uStack_c + (uint)bVar2) = *(undefined1 *)(param_1 + (uint)bVar2);
  }
  uVar1 = FUN_08016658(&uStack_c,4);
  local_8 = CONCAT31(local_8._1_3_,uVar1);
  FUN_0800f850(0x293,&uStack_c,5);
  FUN_08019844(0,0x86);
  FUN_0801aa48(0xff);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08021f50 at 0x08021f50
// ---------------------------------------------------------------------------

void FUN_08021f50(int param_1)

{
  undefined1 auStack_18 [15];
  undefined1 local_9;
  byte local_8;
  
  for (local_8 = 0; local_8 < 0xf; local_8 = local_8 + 1) {
    auStack_18[local_8] = *(undefined1 *)(param_1 + (uint)local_8);
  }
  local_9 = FUN_08016658(auStack_18,0xf);
  FUN_0800f850(0x29b,auStack_18,0x10);
  FUN_08019844(0,0x88);
  FUN_0801aa48(0xff);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08021fae at 0x08021fae
// ---------------------------------------------------------------------------

undefined4 FUN_08021fae(undefined2 param_1,ushort param_2)

{
  uint uVar1;
  
  FUN_08022e7c(param_1,param_2);
  uVar1 = FUN_08018768(param_1);
  if (uVar1 == param_2) {
    return 1;
  }
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_08021fd4 at 0x08021fd4
// ---------------------------------------------------------------------------

void FUN_08021fd4(undefined4 param_1)

{
  undefined2 local_10 [4];
  undefined4 local_8;
  
  local_8._0_1_ = (char)param_1;
  if ((char)local_8 == '\x01') {
    local_10[0] = 0x55aa;
  }
  else {
    local_10[0] = 0xffff;
  }
  local_8 = param_1;
  FUN_080127e0(0x18e,local_10,2);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080222c0 at 0x080222c0
// ---------------------------------------------------------------------------

void FUN_080222c0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  byte bVar2;
  undefined4 uStack_c;
  
  uStack_c = param_4;
  for (bVar2 = 0; bVar2 < 2; bVar2 = bVar2 + 1) {
    *(undefined1 *)((int)&uStack_c + (uint)bVar2) = *(undefined1 *)(param_1 + (uint)bVar2);
  }
  uVar1 = FUN_08016658(&uStack_c,2);
  uStack_c._0_3_ = CONCAT12(uVar1,(undefined2)uStack_c);
  FUN_0800f850(0x298,&uStack_c,3);
  FUN_08019844(0,0x87);
  FUN_0801aa48(0xff);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080224d4 at 0x080224d4
// ---------------------------------------------------------------------------

void FUN_080224d4(void)

{
  FUN_080127e0(0x1a8,DAT_080224e0,0x18);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_080225b0 at 0x080225b0
// ---------------------------------------------------------------------------

void FUN_080225b0(uint param_1,undefined4 param_2)

{
  undefined1 local_10;
  undefined1 local_f;
  undefined1 local_e;
  undefined1 local_d;
  uint local_c;
  undefined4 local_8;
  
  local_10 = (undefined1)((uint)param_2 >> 0x18);
  local_f = (undefined1)((uint)param_2 >> 0x10);
  local_e = (undefined1)((uint)param_2 >> 8);
  local_d = (undefined1)param_2;
  local_c = param_1;
  local_8 = param_2;
  FUN_080127e0(param_1 & 0xffff,&local_10,4);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08022b0c at 0x08022b0c
// ---------------------------------------------------------------------------

void FUN_08022b0c(void)

{
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08022b40 at 0x08022b40
// ---------------------------------------------------------------------------

undefined4 FUN_08022b40(void)

{
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_08022e7c at 0x08022e7c
// ---------------------------------------------------------------------------

void FUN_08022e7c(uint param_1,undefined4 param_2)

{
  undefined1 local_10;
  undefined1 local_f;
  uint local_c;
  undefined4 local_8;
  
  local_10 = (undefined1)((uint)param_2 >> 8);
  local_f = (undefined1)param_2;
  local_c = param_1;
  local_8 = param_2;
  FUN_080127e0(param_1 & 0xffff,&local_10,2);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08022ea0 at 0x08022ea0
// ---------------------------------------------------------------------------

/* WARNING: Removing unreachable block (ram,0x08022ec6) */

void FUN_08022ea0(uint param_1,undefined1 *param_2,char param_3)

{
  bool bVar1;
  char local_20;
  
  FUN_08012528();
  FUN_08012648(0xa0);
  FUN_08012424();
  FUN_08012648((char)(param_1 >> 8));
  FUN_08012424();
  FUN_08012648(param_1 & 0xff);
  FUN_08012424();
  local_20 = param_3;
  while (bVar1 = local_20 != '\0', local_20 = local_20 + -1, bVar1) {
    FUN_08012648(*param_2);
    FUN_08012424();
    param_2 = param_2 + 1;
  }
  FUN_080125d4();
  FUN_0800db18(8);
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08022f20 at 0x08022f20
// ---------------------------------------------------------------------------

void FUN_08022f20(uint param_1)

{
  if (-1 < (int)param_1) {
    *(int *)(&DAT_e000e100 + (param_1 >> 5) * 4) = 1 << (param_1 & 0x1f);
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08022f3c at 0x08022f3c
// ---------------------------------------------------------------------------

void FUN_08022f3c(void)

{
  DataSynchronizationBarrier(0xf);
  *DAT_08022f58 = *DAT_08022f58 & 0x700 | DAT_08022f5c;
  DataSynchronizationBarrier(0xf);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ---------------------------------------------------------------------------
// Function: FUN_08022f60 at 0x08022f60
// ---------------------------------------------------------------------------

void FUN_08022f60(void)

{
  DataSynchronizationBarrier(0xf);
  *DAT_08022f7c = *DAT_08022f7c & 0x700 | DAT_08022f80;
  DataSynchronizationBarrier(0xf);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ---------------------------------------------------------------------------
// Function: __scatterload_zeroinit at 0x08022f94
// ---------------------------------------------------------------------------

void __scatterload_zeroinit(undefined4 param_1,undefined4 *param_2,int param_3)

{
  for (; param_3 != 0; param_3 = param_3 + -4) {
    *param_2 = 0;
    param_2 = param_2 + 1;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08022fa2 at 0x08022fa2
// ---------------------------------------------------------------------------

void FUN_08022fa2(int param_1,char param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  
  uVar2 = 0;
  uVar1 = 0;
  while (bVar5 = param_2 != '\0', param_2 = param_2 + -1, bVar5) {
    uVar3 = 0x80;
    do {
      iVar4 = uVar1 << 0x18;
      uVar1 = (uVar1 & 0x7f) << 1;
      if (iVar4 < 0) {
        uVar1 = uVar1 ^ 7;
      }
      if ((*(byte *)(param_1 + uVar2) & uVar3) != 0) {
        uVar1 = uVar1 ^ 7;
      }
      uVar3 = uVar3 >> 1;
    } while (uVar3 != 0);
    uVar2 = uVar2 + 1 & 0xff;
  }
  return;
}



// ---------------------------------------------------------------------------
// Function: main at 0x08022fe0
// ---------------------------------------------------------------------------

undefined4 main(void)

{
  FUN_08017df0(0x12);
  *DAT_0802301c = DAT_08023018;
  DAT_e000e014 = DAT_08023020;
  *(undefined1 *)(DAT_08023024 + 0xd14) = 0xf0;
  DAT_e000e018 = 0;
  DAT_e000e010 = 7;
  FUN_08021748();
  *DAT_08023028 = 0xaaaa;
  return 0;
}



// ---------------------------------------------------------------------------
// Function: FUN_0802302c at 0x0802302c
// ---------------------------------------------------------------------------

void FUN_0802302c(void)

{
  int iVar1;
  
  iVar1 = DAT_0802306c;
  *(undefined4 *)(DAT_0802306c + 4) = DAT_08023068;
  *(undefined4 *)(iVar1 + 8) = DAT_08023070;
  *(undefined4 *)(iVar1 + 0xc) = DAT_08023074;
  *(undefined4 *)(iVar1 + 0x10) = DAT_08023078;
  *(undefined4 *)(iVar1 + 0x14) = DAT_0802307c;
  *(undefined4 *)(iVar1 + 0x18) = DAT_08023080;
  FUN_080207fc();
  FUN_080129b4();
  FUN_08013f88();
  FUN_08015364();
  FUN_0800bc4c();
  FUN_0800c8f4();
  FUN_0800ac9c();
  return;
}



// ---------------------------------------------------------------------------
// Function: FUN_08023084 at 0x08023084
// ---------------------------------------------------------------------------

bool FUN_08023084(int param_1,byte param_2,undefined4 param_3,undefined1 param_4,undefined1 param_5)

{
  undefined4 *puVar1;
  int iVar2;
  byte bVar3;
  
  puVar1 = DAT_080230ec;
  *DAT_080230ec = param_3;
  puVar1[1] = param_3;
  *(undefined1 *)(puVar1 + 2) = param_5;
  *(undefined1 *)((int)puVar1 + 9) = param_4;
  *(byte *)((int)puVar1 + 10) = param_2;
  bVar3 = 0;
  while( true ) {
    if (param_2 <= bVar3) break;
    *(undefined1 *)((int)puVar1 + bVar3 + 0xb) = *(undefined1 *)(param_1 + (uint)bVar3);
    bVar3 = bVar3 + 1;
  }
  iVar2 = FUN_0800a950(DAT_080230f0,DAT_080230ec);
  if (iVar2 == 4) {
    FUN_0800db18(1);
  }
  else {
    FUN_0800db18(1);
  }
  return iVar2 != 4;
}



