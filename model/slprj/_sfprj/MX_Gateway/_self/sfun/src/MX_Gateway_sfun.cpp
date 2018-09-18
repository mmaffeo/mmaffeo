/* Include files */

#define IN_SF_MACHINE_SOURCE           1
#include "MX_Gateway_sfun.h"
#include "MX_Gateway_sfun_debug_macros.h"
#include "c1_MX_Gateway.h"
#include "c2_MX_Gateway.h"
#include "c6_MX_Gateway.h"
#include "c42_MX_Gateway.h"
#include "c63_MX_Gateway.h"
#include "c78_MX_Gateway.h"
#include "c81_MX_Gateway.h"
#include "c83_MX_Gateway.h"
#include "c100_MX_Gateway.h"
#include "c105_MX_Gateway.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _MX_GatewayMachineNumber_;

/* Function Declarations */

/* Function Definitions */
void MX_Gateway_initializer(void)
{
}

void MX_Gateway_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_MX_Gateway_method_dispatcher(SimStruct *simstructPtr, unsigned
  int chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==1) {
    c1_MX_Gateway_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==2) {
    c2_MX_Gateway_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==6) {
    c6_MX_Gateway_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==42) {
    c42_MX_Gateway_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==63) {
    c63_MX_Gateway_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==78) {
    c78_MX_Gateway_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==81) {
    c81_MX_Gateway_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==83) {
    c83_MX_Gateway_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==100) {
    c100_MX_Gateway_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==105) {
    c105_MX_Gateway_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_MX_Gateway_process_check_sum_call( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>1 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"machine")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3409925157U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(525067463U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2489710205U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1467384767U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 1:
        {
          extern void sf_c1_MX_Gateway_get_check_sum(mxArray *plhs[]);
          sf_c1_MX_Gateway_get_check_sum(plhs);
          break;
        }

       case 2:
        {
          extern void sf_c2_MX_Gateway_get_check_sum(mxArray *plhs[]);
          sf_c2_MX_Gateway_get_check_sum(plhs);
          break;
        }

       case 6:
        {
          extern void sf_c6_MX_Gateway_get_check_sum(mxArray *plhs[]);
          sf_c6_MX_Gateway_get_check_sum(plhs);
          break;
        }

       case 42:
        {
          extern void sf_c42_MX_Gateway_get_check_sum(mxArray *plhs[]);
          sf_c42_MX_Gateway_get_check_sum(plhs);
          break;
        }

       case 63:
        {
          extern void sf_c63_MX_Gateway_get_check_sum(mxArray *plhs[]);
          sf_c63_MX_Gateway_get_check_sum(plhs);
          break;
        }

       case 78:
        {
          extern void sf_c78_MX_Gateway_get_check_sum(mxArray *plhs[]);
          sf_c78_MX_Gateway_get_check_sum(plhs);
          break;
        }

       case 81:
        {
          extern void sf_c81_MX_Gateway_get_check_sum(mxArray *plhs[]);
          sf_c81_MX_Gateway_get_check_sum(plhs);
          break;
        }

       case 83:
        {
          extern void sf_c83_MX_Gateway_get_check_sum(mxArray *plhs[]);
          sf_c83_MX_Gateway_get_check_sum(plhs);
          break;
        }

       case 100:
        {
          extern void sf_c100_MX_Gateway_get_check_sum(mxArray *plhs[]);
          sf_c100_MX_Gateway_get_check_sum(plhs);
          break;
        }

       case 105:
        {
          extern void sf_c105_MX_Gateway_get_check_sum(mxArray *plhs[]);
          sf_c105_MX_Gateway_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3012640683U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1326814170U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2711350529U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3827619406U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1228606042U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1742718857U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1402843732U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1069635151U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_MX_Gateway_autoinheritance_info( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char aiChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;
  mxGetString(prhs[2], aiChksum,sizeof(aiChksum)/sizeof(char));
  aiChksum[(sizeof(aiChksum)/sizeof(char)-1)] = '\0';

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(aiChksum, "N1Z0uUH1oEDfzi7AE0Ll0G") == 0) {
          extern mxArray *sf_c1_MX_Gateway_get_autoinheritance_info(void);
          plhs[0] = sf_c1_MX_Gateway_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 2:
      {
        if (strcmp(aiChksum, "07qmQvLt6nKjj3fj1HZKJ") == 0) {
          extern mxArray *sf_c2_MX_Gateway_get_autoinheritance_info(void);
          plhs[0] = sf_c2_MX_Gateway_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 6:
      {
        if (strcmp(aiChksum, "XUr0aB6ytbqrDp6ICWQVS") == 0) {
          extern mxArray *sf_c6_MX_Gateway_get_autoinheritance_info(void);
          plhs[0] = sf_c6_MX_Gateway_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 42:
      {
        if (strcmp(aiChksum, "pxtaD2Da8adeHzNQNCft0F") == 0) {
          extern mxArray *sf_c42_MX_Gateway_get_autoinheritance_info(void);
          plhs[0] = sf_c42_MX_Gateway_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 63:
      {
        if (strcmp(aiChksum, "UN4pRHyS0hdDDtekQWM6UG") == 0) {
          extern mxArray *sf_c63_MX_Gateway_get_autoinheritance_info(void);
          plhs[0] = sf_c63_MX_Gateway_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 78:
      {
        if (strcmp(aiChksum, "ZlmISBBjl7x0GNXIAG3l8E") == 0) {
          extern mxArray *sf_c78_MX_Gateway_get_autoinheritance_info(void);
          plhs[0] = sf_c78_MX_Gateway_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 81:
      {
        if (strcmp(aiChksum, "328a3hA02us8wQR2ksXuEF") == 0) {
          extern mxArray *sf_c81_MX_Gateway_get_autoinheritance_info(void);
          plhs[0] = sf_c81_MX_Gateway_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 83:
      {
        if (strcmp(aiChksum, "kGMWstsmFMHu1cek21TMN") == 0) {
          extern mxArray *sf_c83_MX_Gateway_get_autoinheritance_info(void);
          plhs[0] = sf_c83_MX_Gateway_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 100:
      {
        if (strcmp(aiChksum, "Cl6irihn7evt2wW54IxUVH") == 0) {
          extern mxArray *sf_c100_MX_Gateway_get_autoinheritance_info(void);
          plhs[0] = sf_c100_MX_Gateway_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 105:
      {
        if (strcmp(aiChksum, "fjLyx6I1Caw87W6FwgaW0G") == 0) {
          extern mxArray *sf_c105_MX_Gateway_get_autoinheritance_info(void);
          plhs[0] = sf_c105_MX_Gateway_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_MX_Gateway_get_eml_resolved_functions_info( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  char instanceChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    mxGetString(prhs[2], instanceChksum,sizeof(instanceChksum)/sizeof(char));
    instanceChksum[(sizeof(instanceChksum)/sizeof(char)-1)] = '\0';
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(instanceChksum, "s8M3M9hTmqGErGRAInzYMG") == 0) {
          extern const mxArray *sf_c1_MX_Gateway_get_eml_resolved_functions_info
            (void);
          mxArray *persistentMxArray = (mxArray *)
            sf_c1_MX_Gateway_get_eml_resolved_functions_info();
          plhs[0] = mxDuplicateArray(persistentMxArray);
          mxDestroyArray(persistentMxArray);
          break;
        }
      }

     case 2:
      {
        if (strcmp(instanceChksum, "scMFRmMFG9bYgu9E22onI7D") == 0) {
          extern const mxArray *sf_c2_MX_Gateway_get_eml_resolved_functions_info
            (void);
          mxArray *persistentMxArray = (mxArray *)
            sf_c2_MX_Gateway_get_eml_resolved_functions_info();
          plhs[0] = mxDuplicateArray(persistentMxArray);
          mxDestroyArray(persistentMxArray);
          break;
        }
      }

     case 6:
      {
        if (strcmp(instanceChksum, "sI3MHraxPC4qQUXHVeztKnG") == 0) {
          extern const mxArray *sf_c6_MX_Gateway_get_eml_resolved_functions_info
            (void);
          mxArray *persistentMxArray = (mxArray *)
            sf_c6_MX_Gateway_get_eml_resolved_functions_info();
          plhs[0] = mxDuplicateArray(persistentMxArray);
          mxDestroyArray(persistentMxArray);
          break;
        }
      }

     case 42:
      {
        if (strcmp(instanceChksum, "sSZ0SoeBMBcebVfOAbY5oMG") == 0) {
          extern const mxArray
            *sf_c42_MX_Gateway_get_eml_resolved_functions_info(void);
          mxArray *persistentMxArray = (mxArray *)
            sf_c42_MX_Gateway_get_eml_resolved_functions_info();
          plhs[0] = mxDuplicateArray(persistentMxArray);
          mxDestroyArray(persistentMxArray);
          break;
        }
      }

     case 63:
      {
        if (strcmp(instanceChksum, "s4AKRTI2TbEmNI2BtdnbNCF") == 0) {
          extern const mxArray
            *sf_c63_MX_Gateway_get_eml_resolved_functions_info(void);
          mxArray *persistentMxArray = (mxArray *)
            sf_c63_MX_Gateway_get_eml_resolved_functions_info();
          plhs[0] = mxDuplicateArray(persistentMxArray);
          mxDestroyArray(persistentMxArray);
          break;
        }
      }

     case 78:
      {
        if (strcmp(instanceChksum, "srCmhmRs9Mv9hgCdexntGK") == 0) {
          extern const mxArray
            *sf_c78_MX_Gateway_get_eml_resolved_functions_info(void);
          mxArray *persistentMxArray = (mxArray *)
            sf_c78_MX_Gateway_get_eml_resolved_functions_info();
          plhs[0] = mxDuplicateArray(persistentMxArray);
          mxDestroyArray(persistentMxArray);
          break;
        }
      }

     case 81:
      {
        if (strcmp(instanceChksum, "somr7G2gpx595q6hnPmbO2B") == 0) {
          extern const mxArray
            *sf_c81_MX_Gateway_get_eml_resolved_functions_info(void);
          mxArray *persistentMxArray = (mxArray *)
            sf_c81_MX_Gateway_get_eml_resolved_functions_info();
          plhs[0] = mxDuplicateArray(persistentMxArray);
          mxDestroyArray(persistentMxArray);
          break;
        }
      }

     case 83:
      {
        if (strcmp(instanceChksum, "sQsW2oTHToYb8lybBaGBH6G") == 0) {
          extern const mxArray
            *sf_c83_MX_Gateway_get_eml_resolved_functions_info(void);
          mxArray *persistentMxArray = (mxArray *)
            sf_c83_MX_Gateway_get_eml_resolved_functions_info();
          plhs[0] = mxDuplicateArray(persistentMxArray);
          mxDestroyArray(persistentMxArray);
          break;
        }
      }

     case 100:
      {
        if (strcmp(instanceChksum, "s0dZTa6OSP8YXP03DoFV56D") == 0) {
          extern const mxArray
            *sf_c100_MX_Gateway_get_eml_resolved_functions_info(void);
          mxArray *persistentMxArray = (mxArray *)
            sf_c100_MX_Gateway_get_eml_resolved_functions_info();
          plhs[0] = mxDuplicateArray(persistentMxArray);
          mxDestroyArray(persistentMxArray);
          break;
        }
      }

     case 105:
      {
        if (strcmp(instanceChksum, "sShGWn5L2HPiQsOJQjIcAaF") == 0) {
          extern const mxArray
            *sf_c105_MX_Gateway_get_eml_resolved_functions_info(void);
          mxArray *persistentMxArray = (mxArray *)
            sf_c105_MX_Gateway_get_eml_resolved_functions_info();
          plhs[0] = mxDuplicateArray(persistentMxArray);
          mxDestroyArray(persistentMxArray);
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_MX_Gateway_third_party_uses_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the third_party_uses_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_third_party_uses_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "s8M3M9hTmqGErGRAInzYMG") == 0) {
          extern mxArray *sf_c1_MX_Gateway_third_party_uses_info(void);
          plhs[0] = sf_c1_MX_Gateway_third_party_uses_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "scMFRmMFG9bYgu9E22onI7D") == 0) {
          extern mxArray *sf_c2_MX_Gateway_third_party_uses_info(void);
          plhs[0] = sf_c2_MX_Gateway_third_party_uses_info();
          break;
        }
      }

     case 6:
      {
        if (strcmp(tpChksum, "sI3MHraxPC4qQUXHVeztKnG") == 0) {
          extern mxArray *sf_c6_MX_Gateway_third_party_uses_info(void);
          plhs[0] = sf_c6_MX_Gateway_third_party_uses_info();
          break;
        }
      }

     case 42:
      {
        if (strcmp(tpChksum, "sSZ0SoeBMBcebVfOAbY5oMG") == 0) {
          extern mxArray *sf_c42_MX_Gateway_third_party_uses_info(void);
          plhs[0] = sf_c42_MX_Gateway_third_party_uses_info();
          break;
        }
      }

     case 63:
      {
        if (strcmp(tpChksum, "s4AKRTI2TbEmNI2BtdnbNCF") == 0) {
          extern mxArray *sf_c63_MX_Gateway_third_party_uses_info(void);
          plhs[0] = sf_c63_MX_Gateway_third_party_uses_info();
          break;
        }
      }

     case 78:
      {
        if (strcmp(tpChksum, "srCmhmRs9Mv9hgCdexntGK") == 0) {
          extern mxArray *sf_c78_MX_Gateway_third_party_uses_info(void);
          plhs[0] = sf_c78_MX_Gateway_third_party_uses_info();
          break;
        }
      }

     case 81:
      {
        if (strcmp(tpChksum, "somr7G2gpx595q6hnPmbO2B") == 0) {
          extern mxArray *sf_c81_MX_Gateway_third_party_uses_info(void);
          plhs[0] = sf_c81_MX_Gateway_third_party_uses_info();
          break;
        }
      }

     case 83:
      {
        if (strcmp(tpChksum, "sQsW2oTHToYb8lybBaGBH6G") == 0) {
          extern mxArray *sf_c83_MX_Gateway_third_party_uses_info(void);
          plhs[0] = sf_c83_MX_Gateway_third_party_uses_info();
          break;
        }
      }

     case 100:
      {
        if (strcmp(tpChksum, "s0dZTa6OSP8YXP03DoFV56D") == 0) {
          extern mxArray *sf_c100_MX_Gateway_third_party_uses_info(void);
          plhs[0] = sf_c100_MX_Gateway_third_party_uses_info();
          break;
        }
      }

     case 105:
      {
        if (strcmp(tpChksum, "sShGWn5L2HPiQsOJQjIcAaF") == 0) {
          extern mxArray *sf_c105_MX_Gateway_third_party_uses_info(void);
          plhs[0] = sf_c105_MX_Gateway_third_party_uses_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

unsigned int sf_MX_Gateway_jit_fallback_info( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the jit_fallback_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_jit_fallback_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "s8M3M9hTmqGErGRAInzYMG") == 0) {
          extern mxArray *sf_c1_MX_Gateway_jit_fallback_info(void);
          plhs[0] = sf_c1_MX_Gateway_jit_fallback_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "scMFRmMFG9bYgu9E22onI7D") == 0) {
          extern mxArray *sf_c2_MX_Gateway_jit_fallback_info(void);
          plhs[0] = sf_c2_MX_Gateway_jit_fallback_info();
          break;
        }
      }

     case 6:
      {
        if (strcmp(tpChksum, "sI3MHraxPC4qQUXHVeztKnG") == 0) {
          extern mxArray *sf_c6_MX_Gateway_jit_fallback_info(void);
          plhs[0] = sf_c6_MX_Gateway_jit_fallback_info();
          break;
        }
      }

     case 42:
      {
        if (strcmp(tpChksum, "sSZ0SoeBMBcebVfOAbY5oMG") == 0) {
          extern mxArray *sf_c42_MX_Gateway_jit_fallback_info(void);
          plhs[0] = sf_c42_MX_Gateway_jit_fallback_info();
          break;
        }
      }

     case 63:
      {
        if (strcmp(tpChksum, "s4AKRTI2TbEmNI2BtdnbNCF") == 0) {
          extern mxArray *sf_c63_MX_Gateway_jit_fallback_info(void);
          plhs[0] = sf_c63_MX_Gateway_jit_fallback_info();
          break;
        }
      }

     case 78:
      {
        if (strcmp(tpChksum, "srCmhmRs9Mv9hgCdexntGK") == 0) {
          extern mxArray *sf_c78_MX_Gateway_jit_fallback_info(void);
          plhs[0] = sf_c78_MX_Gateway_jit_fallback_info();
          break;
        }
      }

     case 81:
      {
        if (strcmp(tpChksum, "somr7G2gpx595q6hnPmbO2B") == 0) {
          extern mxArray *sf_c81_MX_Gateway_jit_fallback_info(void);
          plhs[0] = sf_c81_MX_Gateway_jit_fallback_info();
          break;
        }
      }

     case 83:
      {
        if (strcmp(tpChksum, "sQsW2oTHToYb8lybBaGBH6G") == 0) {
          extern mxArray *sf_c83_MX_Gateway_jit_fallback_info(void);
          plhs[0] = sf_c83_MX_Gateway_jit_fallback_info();
          break;
        }
      }

     case 100:
      {
        if (strcmp(tpChksum, "s0dZTa6OSP8YXP03DoFV56D") == 0) {
          extern mxArray *sf_c100_MX_Gateway_jit_fallback_info(void);
          plhs[0] = sf_c100_MX_Gateway_jit_fallback_info();
          break;
        }
      }

     case 105:
      {
        if (strcmp(tpChksum, "sShGWn5L2HPiQsOJQjIcAaF") == 0) {
          extern mxArray *sf_c105_MX_Gateway_jit_fallback_info(void);
          plhs[0] = sf_c105_MX_Gateway_jit_fallback_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

unsigned int sf_MX_Gateway_updateBuildInfo_args_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the updateBuildInfo_args_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_updateBuildInfo_args_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "s8M3M9hTmqGErGRAInzYMG") == 0) {
          extern mxArray *sf_c1_MX_Gateway_updateBuildInfo_args_info(void);
          plhs[0] = sf_c1_MX_Gateway_updateBuildInfo_args_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "scMFRmMFG9bYgu9E22onI7D") == 0) {
          extern mxArray *sf_c2_MX_Gateway_updateBuildInfo_args_info(void);
          plhs[0] = sf_c2_MX_Gateway_updateBuildInfo_args_info();
          break;
        }
      }

     case 6:
      {
        if (strcmp(tpChksum, "sI3MHraxPC4qQUXHVeztKnG") == 0) {
          extern mxArray *sf_c6_MX_Gateway_updateBuildInfo_args_info(void);
          plhs[0] = sf_c6_MX_Gateway_updateBuildInfo_args_info();
          break;
        }
      }

     case 42:
      {
        if (strcmp(tpChksum, "sSZ0SoeBMBcebVfOAbY5oMG") == 0) {
          extern mxArray *sf_c42_MX_Gateway_updateBuildInfo_args_info(void);
          plhs[0] = sf_c42_MX_Gateway_updateBuildInfo_args_info();
          break;
        }
      }

     case 63:
      {
        if (strcmp(tpChksum, "s4AKRTI2TbEmNI2BtdnbNCF") == 0) {
          extern mxArray *sf_c63_MX_Gateway_updateBuildInfo_args_info(void);
          plhs[0] = sf_c63_MX_Gateway_updateBuildInfo_args_info();
          break;
        }
      }

     case 78:
      {
        if (strcmp(tpChksum, "srCmhmRs9Mv9hgCdexntGK") == 0) {
          extern mxArray *sf_c78_MX_Gateway_updateBuildInfo_args_info(void);
          plhs[0] = sf_c78_MX_Gateway_updateBuildInfo_args_info();
          break;
        }
      }

     case 81:
      {
        if (strcmp(tpChksum, "somr7G2gpx595q6hnPmbO2B") == 0) {
          extern mxArray *sf_c81_MX_Gateway_updateBuildInfo_args_info(void);
          plhs[0] = sf_c81_MX_Gateway_updateBuildInfo_args_info();
          break;
        }
      }

     case 83:
      {
        if (strcmp(tpChksum, "sQsW2oTHToYb8lybBaGBH6G") == 0) {
          extern mxArray *sf_c83_MX_Gateway_updateBuildInfo_args_info(void);
          plhs[0] = sf_c83_MX_Gateway_updateBuildInfo_args_info();
          break;
        }
      }

     case 100:
      {
        if (strcmp(tpChksum, "s0dZTa6OSP8YXP03DoFV56D") == 0) {
          extern mxArray *sf_c100_MX_Gateway_updateBuildInfo_args_info(void);
          plhs[0] = sf_c100_MX_Gateway_updateBuildInfo_args_info();
          break;
        }
      }

     case 105:
      {
        if (strcmp(tpChksum, "sShGWn5L2HPiQsOJQjIcAaF") == 0) {
          extern mxArray *sf_c105_MX_Gateway_updateBuildInfo_args_info(void);
          plhs[0] = sf_c105_MX_Gateway_updateBuildInfo_args_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

void MX_Gateway_debug_initialize(struct SfDebugInstanceStruct* debugInstance)
{
  _MX_GatewayMachineNumber_ = sf_debug_initialize_machine(debugInstance,
    "MX_Gateway","sfun",0,103,0,0,0);
  sf_debug_set_machine_event_thresholds(debugInstance,_MX_GatewayMachineNumber_,
    0,0);
  sf_debug_set_machine_data_thresholds(debugInstance,_MX_GatewayMachineNumber_,0);
}

void MX_Gateway_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
typedef struct SfOptimizationInfoFlagsTag {
  boolean_T isRtwGen;
  boolean_T isModelRef;
  boolean_T isExternal;
} SfOptimizationInfoFlags;

static SfOptimizationInfoFlags sOptimizationInfoFlags;
void unload_MX_Gateway_optimization_info(void);
mxArray* load_MX_Gateway_optimization_info(boolean_T isRtwGen, boolean_T
  isModelRef, boolean_T isExternal)
{
  if (sOptimizationInfoFlags.isRtwGen != isRtwGen ||
      sOptimizationInfoFlags.isModelRef != isModelRef ||
      sOptimizationInfoFlags.isExternal != isExternal) {
    unload_MX_Gateway_optimization_info();
  }

  sOptimizationInfoFlags.isRtwGen = isRtwGen;
  sOptimizationInfoFlags.isModelRef = isModelRef;
  sOptimizationInfoFlags.isExternal = isExternal;
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info("MX_Gateway",
      "MX_Gateway");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_MX_Gateway_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
