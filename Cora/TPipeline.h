#pragma once

template<typename _Function1, typename _Function2>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41, typename _Function42>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41, _Function42 &_Func42)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run(_Func42);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41, typename _Function42, typename _Function43>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41, _Function42 &_Func42, _Function43 &_Func43)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run(_Func42);
  tg.run(_Func43);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41, typename _Function42, typename _Function43, typename _Function44>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41, _Function42 &_Func42, _Function43 &_Func43, _Function44 &_Func44)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run(_Func42);
  tg.run(_Func43);
  tg.run(_Func44);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41, typename _Function42, typename _Function43, typename _Function44, typename _Function45>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41, _Function42 &_Func42, _Function43 &_Func43, _Function44 &_Func44, _Function45 &_Func45)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run(_Func42);
  tg.run(_Func43);
  tg.run(_Func44);
  tg.run(_Func45);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41, typename _Function42, typename _Function43, typename _Function44, typename _Function45, typename _Function46>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41, _Function42 &_Func42, _Function43 &_Func43, _Function44 &_Func44, _Function45 &_Func45, _Function46 &_Func46)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run(_Func42);
  tg.run(_Func43);
  tg.run(_Func44);
  tg.run(_Func45);
  tg.run(_Func46);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41, typename _Function42, typename _Function43, typename _Function44, typename _Function45, typename _Function46, typename _Function47>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41, _Function42 &_Func42, _Function43 &_Func43, _Function44 &_Func44, _Function45 &_Func45, _Function46 &_Func46, _Function47 &_Func47)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run(_Func42);
  tg.run(_Func43);
  tg.run(_Func44);
  tg.run(_Func45);
  tg.run(_Func46);
  tg.run(_Func47);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41, typename _Function42, typename _Function43, typename _Function44, typename _Function45, typename _Function46, typename _Function47, typename _Function48>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41, _Function42 &_Func42, _Function43 &_Func43, _Function44 &_Func44, _Function45 &_Func45, _Function46 &_Func46, _Function47 &_Func47, _Function48 &_Func48)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run(_Func42);
  tg.run(_Func43);
  tg.run(_Func44);
  tg.run(_Func45);
  tg.run(_Func46);
  tg.run(_Func47);
  tg.run(_Func48);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41, typename _Function42, typename _Function43, typename _Function44, typename _Function45, typename _Function46, typename _Function47, typename _Function48, typename _Function49>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41, _Function42 &_Func42, _Function43 &_Func43, _Function44 &_Func44, _Function45 &_Func45, _Function46 &_Func46, _Function47 &_Func47, _Function48 &_Func48, _Function49 &_Func49)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run(_Func42);
  tg.run(_Func43);
  tg.run(_Func44);
  tg.run(_Func45);
  tg.run(_Func46);
  tg.run(_Func47);
  tg.run(_Func48);
  tg.run(_Func49);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41, typename _Function42, typename _Function43, typename _Function44, typename _Function45, typename _Function46, typename _Function47, typename _Function48, typename _Function49, typename _Function50>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41, _Function42 &_Func42, _Function43 &_Func43, _Function44 &_Func44, _Function45 &_Func45, _Function46 &_Func46, _Function47 &_Func47, _Function48 &_Func48, _Function49 &_Func49, _Function50 &_Func50)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run(_Func42);
  tg.run(_Func43);
  tg.run(_Func44);
  tg.run(_Func45);
  tg.run(_Func46);
  tg.run(_Func47);
  tg.run(_Func48);
  tg.run(_Func49);
  tg.run(_Func50);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41, typename _Function42, typename _Function43, typename _Function44, typename _Function45, typename _Function46, typename _Function47, typename _Function48, typename _Function49, typename _Function50, typename _Function51>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41, _Function42 &_Func42, _Function43 &_Func43, _Function44 &_Func44, _Function45 &_Func45, _Function46 &_Func46, _Function47 &_Func47, _Function48 &_Func48, _Function49 &_Func49, _Function50 &_Func50, _Function51 &_Func51)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run(_Func42);
  tg.run(_Func43);
  tg.run(_Func44);
  tg.run(_Func45);
  tg.run(_Func46);
  tg.run(_Func47);
  tg.run(_Func48);
  tg.run(_Func49);
  tg.run(_Func50);
  tg.run(_Func51);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41, typename _Function42, typename _Function43, typename _Function44, typename _Function45, typename _Function46, typename _Function47, typename _Function48, typename _Function49, typename _Function50, typename _Function51, typename _Function52>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41, _Function42 &_Func42, _Function43 &_Func43, _Function44 &_Func44, _Function45 &_Func45, _Function46 &_Func46, _Function47 &_Func47, _Function48 &_Func48, _Function49 &_Func49, _Function50 &_Func50, _Function51 &_Func51, _Function52 &_Func52)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run(_Func42);
  tg.run(_Func43);
  tg.run(_Func44);
  tg.run(_Func45);
  tg.run(_Func46);
  tg.run(_Func47);
  tg.run(_Func48);
  tg.run(_Func49);
  tg.run(_Func50);
  tg.run(_Func51);
  tg.run(_Func52);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41, typename _Function42, typename _Function43, typename _Function44, typename _Function45, typename _Function46, typename _Function47, typename _Function48, typename _Function49, typename _Function50, typename _Function51, typename _Function52, typename _Function53>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41, _Function42 &_Func42, _Function43 &_Func43, _Function44 &_Func44, _Function45 &_Func45, _Function46 &_Func46, _Function47 &_Func47, _Function48 &_Func48, _Function49 &_Func49, _Function50 &_Func50, _Function51 &_Func51, _Function52 &_Func52, _Function53 &_Func53)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run(_Func42);
  tg.run(_Func43);
  tg.run(_Func44);
  tg.run(_Func45);
  tg.run(_Func46);
  tg.run(_Func47);
  tg.run(_Func48);
  tg.run(_Func49);
  tg.run(_Func50);
  tg.run(_Func51);
  tg.run(_Func52);
  tg.run(_Func53);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41, typename _Function42, typename _Function43, typename _Function44, typename _Function45, typename _Function46, typename _Function47, typename _Function48, typename _Function49, typename _Function50, typename _Function51, typename _Function52, typename _Function53, typename _Function54>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41, _Function42 &_Func42, _Function43 &_Func43, _Function44 &_Func44, _Function45 &_Func45, _Function46 &_Func46, _Function47 &_Func47, _Function48 &_Func48, _Function49 &_Func49, _Function50 &_Func50, _Function51 &_Func51, _Function52 &_Func52, _Function53 &_Func53, _Function54 &_Func54)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run(_Func42);
  tg.run(_Func43);
  tg.run(_Func44);
  tg.run(_Func45);
  tg.run(_Func46);
  tg.run(_Func47);
  tg.run(_Func48);
  tg.run(_Func49);
  tg.run(_Func50);
  tg.run(_Func51);
  tg.run(_Func52);
  tg.run(_Func53);
  tg.run(_Func54);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41, typename _Function42, typename _Function43, typename _Function44, typename _Function45, typename _Function46, typename _Function47, typename _Function48, typename _Function49, typename _Function50, typename _Function51, typename _Function52, typename _Function53, typename _Function54, typename _Function55>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41, _Function42 &_Func42, _Function43 &_Func43, _Function44 &_Func44, _Function45 &_Func45, _Function46 &_Func46, _Function47 &_Func47, _Function48 &_Func48, _Function49 &_Func49, _Function50 &_Func50, _Function51 &_Func51, _Function52 &_Func52, _Function53 &_Func53, _Function54 &_Func54, _Function55 &_Func55)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run(_Func42);
  tg.run(_Func43);
  tg.run(_Func44);
  tg.run(_Func45);
  tg.run(_Func46);
  tg.run(_Func47);
  tg.run(_Func48);
  tg.run(_Func49);
  tg.run(_Func50);
  tg.run(_Func51);
  tg.run(_Func52);
  tg.run(_Func53);
  tg.run(_Func54);
  tg.run(_Func55);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41, typename _Function42, typename _Function43, typename _Function44, typename _Function45, typename _Function46, typename _Function47, typename _Function48, typename _Function49, typename _Function50, typename _Function51, typename _Function52, typename _Function53, typename _Function54, typename _Function55, typename _Function56>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41, _Function42 &_Func42, _Function43 &_Func43, _Function44 &_Func44, _Function45 &_Func45, _Function46 &_Func46, _Function47 &_Func47, _Function48 &_Func48, _Function49 &_Func49, _Function50 &_Func50, _Function51 &_Func51, _Function52 &_Func52, _Function53 &_Func53, _Function54 &_Func54, _Function55 &_Func55, _Function56 &_Func56)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run(_Func42);
  tg.run(_Func43);
  tg.run(_Func44);
  tg.run(_Func45);
  tg.run(_Func46);
  tg.run(_Func47);
  tg.run(_Func48);
  tg.run(_Func49);
  tg.run(_Func50);
  tg.run(_Func51);
  tg.run(_Func52);
  tg.run(_Func53);
  tg.run(_Func54);
  tg.run(_Func55);
  tg.run(_Func56);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41, typename _Function42, typename _Function43, typename _Function44, typename _Function45, typename _Function46, typename _Function47, typename _Function48, typename _Function49, typename _Function50, typename _Function51, typename _Function52, typename _Function53, typename _Function54, typename _Function55, typename _Function56, typename _Function57>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41, _Function42 &_Func42, _Function43 &_Func43, _Function44 &_Func44, _Function45 &_Func45, _Function46 &_Func46, _Function47 &_Func47, _Function48 &_Func48, _Function49 &_Func49, _Function50 &_Func50, _Function51 &_Func51, _Function52 &_Func52, _Function53 &_Func53, _Function54 &_Func54, _Function55 &_Func55, _Function56 &_Func56, _Function57 &_Func57)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run(_Func42);
  tg.run(_Func43);
  tg.run(_Func44);
  tg.run(_Func45);
  tg.run(_Func46);
  tg.run(_Func47);
  tg.run(_Func48);
  tg.run(_Func49);
  tg.run(_Func50);
  tg.run(_Func51);
  tg.run(_Func52);
  tg.run(_Func53);
  tg.run(_Func54);
  tg.run(_Func55);
  tg.run(_Func56);
  tg.run(_Func57);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41, typename _Function42, typename _Function43, typename _Function44, typename _Function45, typename _Function46, typename _Function47, typename _Function48, typename _Function49, typename _Function50, typename _Function51, typename _Function52, typename _Function53, typename _Function54, typename _Function55, typename _Function56, typename _Function57, typename _Function58>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41, _Function42 &_Func42, _Function43 &_Func43, _Function44 &_Func44, _Function45 &_Func45, _Function46 &_Func46, _Function47 &_Func47, _Function48 &_Func48, _Function49 &_Func49, _Function50 &_Func50, _Function51 &_Func51, _Function52 &_Func52, _Function53 &_Func53, _Function54 &_Func54, _Function55 &_Func55, _Function56 &_Func56, _Function57 &_Func57, _Function58 &_Func58)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run(_Func42);
  tg.run(_Func43);
  tg.run(_Func44);
  tg.run(_Func45);
  tg.run(_Func46);
  tg.run(_Func47);
  tg.run(_Func48);
  tg.run(_Func49);
  tg.run(_Func50);
  tg.run(_Func51);
  tg.run(_Func52);
  tg.run(_Func53);
  tg.run(_Func54);
  tg.run(_Func55);
  tg.run(_Func56);
  tg.run(_Func57);
  tg.run(_Func58);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41, typename _Function42, typename _Function43, typename _Function44, typename _Function45, typename _Function46, typename _Function47, typename _Function48, typename _Function49, typename _Function50, typename _Function51, typename _Function52, typename _Function53, typename _Function54, typename _Function55, typename _Function56, typename _Function57, typename _Function58, typename _Function59>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41, _Function42 &_Func42, _Function43 &_Func43, _Function44 &_Func44, _Function45 &_Func45, _Function46 &_Func46, _Function47 &_Func47, _Function48 &_Func48, _Function49 &_Func49, _Function50 &_Func50, _Function51 &_Func51, _Function52 &_Func52, _Function53 &_Func53, _Function54 &_Func54, _Function55 &_Func55, _Function56 &_Func56, _Function57 &_Func57, _Function58 &_Func58, _Function59 &_Func59)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run(_Func42);
  tg.run(_Func43);
  tg.run(_Func44);
  tg.run(_Func45);
  tg.run(_Func46);
  tg.run(_Func47);
  tg.run(_Func48);
  tg.run(_Func49);
  tg.run(_Func50);
  tg.run(_Func51);
  tg.run(_Func52);
  tg.run(_Func53);
  tg.run(_Func54);
  tg.run(_Func55);
  tg.run(_Func56);
  tg.run(_Func57);
  tg.run(_Func58);
  tg.run(_Func59);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41, typename _Function42, typename _Function43, typename _Function44, typename _Function45, typename _Function46, typename _Function47, typename _Function48, typename _Function49, typename _Function50, typename _Function51, typename _Function52, typename _Function53, typename _Function54, typename _Function55, typename _Function56, typename _Function57, typename _Function58, typename _Function59, typename _Function60>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41, _Function42 &_Func42, _Function43 &_Func43, _Function44 &_Func44, _Function45 &_Func45, _Function46 &_Func46, _Function47 &_Func47, _Function48 &_Func48, _Function49 &_Func49, _Function50 &_Func50, _Function51 &_Func51, _Function52 &_Func52, _Function53 &_Func53, _Function54 &_Func54, _Function55 &_Func55, _Function56 &_Func56, _Function57 &_Func57, _Function58 &_Func58, _Function59 &_Func59, _Function60 &_Func60)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run(_Func42);
  tg.run(_Func43);
  tg.run(_Func44);
  tg.run(_Func45);
  tg.run(_Func46);
  tg.run(_Func47);
  tg.run(_Func48);
  tg.run(_Func49);
  tg.run(_Func50);
  tg.run(_Func51);
  tg.run(_Func52);
  tg.run(_Func53);
  tg.run(_Func54);
  tg.run(_Func55);
  tg.run(_Func56);
  tg.run(_Func57);
  tg.run(_Func58);
  tg.run(_Func59);
  tg.run(_Func60);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41, typename _Function42, typename _Function43, typename _Function44, typename _Function45, typename _Function46, typename _Function47, typename _Function48, typename _Function49, typename _Function50, typename _Function51, typename _Function52, typename _Function53, typename _Function54, typename _Function55, typename _Function56, typename _Function57, typename _Function58, typename _Function59, typename _Function60, typename _Function61>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41, _Function42 &_Func42, _Function43 &_Func43, _Function44 &_Func44, _Function45 &_Func45, _Function46 &_Func46, _Function47 &_Func47, _Function48 &_Func48, _Function49 &_Func49, _Function50 &_Func50, _Function51 &_Func51, _Function52 &_Func52, _Function53 &_Func53, _Function54 &_Func54, _Function55 &_Func55, _Function56 &_Func56, _Function57 &_Func57, _Function58 &_Func58, _Function59 &_Func59, _Function60 &_Func60, _Function61 &_Func61)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run(_Func42);
  tg.run(_Func43);
  tg.run(_Func44);
  tg.run(_Func45);
  tg.run(_Func46);
  tg.run(_Func47);
  tg.run(_Func48);
  tg.run(_Func49);
  tg.run(_Func50);
  tg.run(_Func51);
  tg.run(_Func52);
  tg.run(_Func53);
  tg.run(_Func54);
  tg.run(_Func55);
  tg.run(_Func56);
  tg.run(_Func57);
  tg.run(_Func58);
  tg.run(_Func59);
  tg.run(_Func60);
  tg.run(_Func61);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41, typename _Function42, typename _Function43, typename _Function44, typename _Function45, typename _Function46, typename _Function47, typename _Function48, typename _Function49, typename _Function50, typename _Function51, typename _Function52, typename _Function53, typename _Function54, typename _Function55, typename _Function56, typename _Function57, typename _Function58, typename _Function59, typename _Function60, typename _Function61, typename _Function62>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41, _Function42 &_Func42, _Function43 &_Func43, _Function44 &_Func44, _Function45 &_Func45, _Function46 &_Func46, _Function47 &_Func47, _Function48 &_Func48, _Function49 &_Func49, _Function50 &_Func50, _Function51 &_Func51, _Function52 &_Func52, _Function53 &_Func53, _Function54 &_Func54, _Function55 &_Func55, _Function56 &_Func56, _Function57 &_Func57, _Function58 &_Func58, _Function59 &_Func59, _Function60 &_Func60, _Function61 &_Func61, _Function62 &_Func62)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run(_Func42);
  tg.run(_Func43);
  tg.run(_Func44);
  tg.run(_Func45);
  tg.run(_Func46);
  tg.run(_Func47);
  tg.run(_Func48);
  tg.run(_Func49);
  tg.run(_Func50);
  tg.run(_Func51);
  tg.run(_Func52);
  tg.run(_Func53);
  tg.run(_Func54);
  tg.run(_Func55);
  tg.run(_Func56);
  tg.run(_Func57);
  tg.run(_Func58);
  tg.run(_Func59);
  tg.run(_Func60);
  tg.run(_Func61);
  tg.run(_Func62);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41, typename _Function42, typename _Function43, typename _Function44, typename _Function45, typename _Function46, typename _Function47, typename _Function48, typename _Function49, typename _Function50, typename _Function51, typename _Function52, typename _Function53, typename _Function54, typename _Function55, typename _Function56, typename _Function57, typename _Function58, typename _Function59, typename _Function60, typename _Function61, typename _Function62, typename _Function63>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41, _Function42 &_Func42, _Function43 &_Func43, _Function44 &_Func44, _Function45 &_Func45, _Function46 &_Func46, _Function47 &_Func47, _Function48 &_Func48, _Function49 &_Func49, _Function50 &_Func50, _Function51 &_Func51, _Function52 &_Func52, _Function53 &_Func53, _Function54 &_Func54, _Function55 &_Func55, _Function56 &_Func56, _Function57 &_Func57, _Function58 &_Func58, _Function59 &_Func59, _Function60 &_Func60, _Function61 &_Func61, _Function62 &_Func62, _Function63 &_Func63)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run(_Func42);
  tg.run(_Func43);
  tg.run(_Func44);
  tg.run(_Func45);
  tg.run(_Func46);
  tg.run(_Func47);
  tg.run(_Func48);
  tg.run(_Func49);
  tg.run(_Func50);
  tg.run(_Func51);
  tg.run(_Func52);
  tg.run(_Func53);
  tg.run(_Func54);
  tg.run(_Func55);
  tg.run(_Func56);
  tg.run(_Func57);
  tg.run(_Func58);
  tg.run(_Func59);
  tg.run(_Func60);
  tg.run(_Func61);
  tg.run(_Func62);
  tg.run(_Func63);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

template<typename _Function1, typename _Function2, typename _Function3, typename _Function4, typename _Function5, typename _Function6, typename _Function7, typename _Function8, typename _Function9, typename _Function10, typename _Function11, typename _Function12, typename _Function13, typename _Function14, typename _Function15, typename _Function16, typename _Function17, typename _Function18, typename _Function19, typename _Function20, typename _Function21, typename _Function22, typename _Function23, typename _Function24, typename _Function25, typename _Function26, typename _Function27, typename _Function28, typename _Function29, typename _Function30, typename _Function31, typename _Function32, typename _Function33, typename _Function34, typename _Function35, typename _Function36, typename _Function37, typename _Function38, typename _Function39, typename _Function40, typename _Function41, typename _Function42, typename _Function43, typename _Function44, typename _Function45, typename _Function46, typename _Function47, typename _Function48, typename _Function49, typename _Function50, typename _Function51, typename _Function52, typename _Function53, typename _Function54, typename _Function55, typename _Function56, typename _Function57, typename _Function58, typename _Function59, typename _Function60, typename _Function61, typename _Function62, typename _Function63, typename _Function64>
void dsp_parallel_invoke(_Function1 &_Func1, _Function2 &_Func2, _Function3 &_Func3, _Function4 &_Func4, _Function5 &_Func5, _Function6 &_Func6, _Function7 &_Func7, _Function8 &_Func8, _Function9 &_Func9, _Function10 &_Func10, _Function11 &_Func11, _Function12 &_Func12, _Function13 &_Func13, _Function14 &_Func14, _Function15 &_Func15, _Function16 &_Func16, _Function17 &_Func17, _Function18 &_Func18, _Function19 &_Func19, _Function20 &_Func20, _Function21 &_Func21, _Function22 &_Func22, _Function23 &_Func23, _Function24 &_Func24, _Function25 &_Func25, _Function26 &_Func26, _Function27 &_Func27, _Function28 &_Func28, _Function29 &_Func29, _Function30 &_Func30, _Function31 &_Func31, _Function32 &_Func32, _Function33 &_Func33, _Function34 &_Func34, _Function35 &_Func35, _Function36 &_Func36, _Function37 &_Func37, _Function38 &_Func38, _Function39 &_Func39, _Function40 &_Func40, _Function41 &_Func41, _Function42 &_Func42, _Function43 &_Func43, _Function44 &_Func44, _Function45 &_Func45, _Function46 &_Func46, _Function47 &_Func47, _Function48 &_Func48, _Function49 &_Func49, _Function50 &_Func50, _Function51 &_Func51, _Function52 &_Func52, _Function53 &_Func53, _Function54 &_Func54, _Function55 &_Func55, _Function56 &_Func56, _Function57 &_Func57, _Function58 &_Func58, _Function59 &_Func59, _Function60 &_Func60, _Function61 &_Func61, _Function62 &_Func62, _Function63 &_Func63, _Function64 &_Func64)
{
  dsp_task_group tg;
  tg.run(_Func2);
  tg.run(_Func3);
  tg.run(_Func4);
  tg.run(_Func5);
  tg.run(_Func6);
  tg.run(_Func7);
  tg.run(_Func8);
  tg.run(_Func9);
  tg.run(_Func10);
  tg.run(_Func11);
  tg.run(_Func12);
  tg.run(_Func13);
  tg.run(_Func14);
  tg.run(_Func15);
  tg.run(_Func16);
  tg.run(_Func17);
  tg.run(_Func18);
  tg.run(_Func19);
  tg.run(_Func20);
  tg.run(_Func21);
  tg.run(_Func22);
  tg.run(_Func23);
  tg.run(_Func24);
  tg.run(_Func25);
  tg.run(_Func26);
  tg.run(_Func27);
  tg.run(_Func28);
  tg.run(_Func29);
  tg.run(_Func30);
  tg.run(_Func31);
  tg.run(_Func32);
  tg.run(_Func33);
  tg.run(_Func34);
  tg.run(_Func35);
  tg.run(_Func36);
  tg.run(_Func37);
  tg.run(_Func38);
  tg.run(_Func39);
  tg.run(_Func40);
  tg.run(_Func41);
  tg.run(_Func42);
  tg.run(_Func43);
  tg.run(_Func44);
  tg.run(_Func45);
  tg.run(_Func46);
  tg.run(_Func47);
  tg.run(_Func48);
  tg.run(_Func49);
  tg.run(_Func50);
  tg.run(_Func51);
  tg.run(_Func52);
  tg.run(_Func53);
  tg.run(_Func54);
  tg.run(_Func55);
  tg.run(_Func56);
  tg.run(_Func57);
  tg.run(_Func58);
  tg.run(_Func59);
  tg.run(_Func60);
  tg.run(_Func61);
  tg.run(_Func62);
  tg.run(_Func63);
  tg.run(_Func64);
  tg.run_and_wait(_Func1);
}

//---------------------------------------------

