def MakeSchedule()
  print "#pragma once\n\n"

  for i in 1..64      
      print "template<typename T1"
      for j in 2..i
          print ", typename T#{j}"
      end
      print ">\n"
      print "__forceinline void START(const T1 &t1"
      for j in 2..i
          print ", const T#{j} &t#{j}"
      end
      print ")\n"
      print "{\n"

      #print "  while (t1(my))\n"
      for j in 1..i
          print "\n  //---------------t#{j}-------------\n"
          print "  __if_exists(T#{j}::op_if)\n"
          print "  {\n"
          print "    if ( const_cast<T#{j}&>(t#{j})() )\n"
          print "  }\n"

          print "  __if_exists(T#{j}::op_if_not)\n"
          print "  {\n"
          print "    if ( !const_cast<T#{j}&>(t#{j})() )\n"
          print "  }\n"

          print "  __if_exists(T#{j}::op_else_if)\n"
          print "  {\n"
          print "    ;\n"
          print "    else if ( const_cast<T#{j}&>(t#{j})() )\n"
          print "  }\n"

          print "  __if_exists(T#{j}::op_else)\n"
          print "  {\n"
          print "    ;\n"
          print "    else\n"
          print "  }\n"

          print "  __if_exists(T#{j}::op_semi)\n"
          print "  {\n"
          print "    ;\n"
          print "  }\n"

          print "  __if_exists(T#{j}::op_while)\n"
          print "  {\n"
          print "    while ( const_cast<T#{j}&>(t#{j})() )\n"
          print "  }\n"
          
          print "  __if_exists(T#{j}::op_while_not)\n"
          print "  {\n"
          print "    while ( !const_cast<T#{j}&>(t#{j})() )\n"
          print "  }\n"

          print "  __if_exists(T#{j}::op_break)\n"
          print "  {\n"
          print "    break;\n"
          print "  }\n"

          print "  __if_exists(T#{j}::op_stop)\n"
          print "  {\n"
          print "    goto __stop__#{j}__\n"
          print "  }\n"
          
          #-----------------------------
          print "  //----------------once---------------------\n"
          print "  __if_not_exists(T#{j}::op_if)\n"
          print "  {"
          print "  __if_not_exists(T#{j}::op_if_not)\n"
          print "  {"
          print "  __if_not_exists(T#{j}::op_else_if)\n"
          print "  {"
          print "  __if_not_exists(T#{j}::op_else)\n"
          print "  {"
          print "  __if_not_exists(T#{j}::op_semi)\n"
          print "  {"
          print "  __if_not_exists(T#{j}::op_while)\n"
          print "  {"
          print "  __if_not_exists(T#{j}::op_while_not)\n"
          print "  {"
          print "  __if_not_exists(T#{j}::op_break)\n"
          print "  {"
          print "  __if_not_exists(T#{j}::op_stop)\n"
          print "  {"          
          print "  const_cast<T#{j}&>(t#{j})()"
          print "  }"
          print "  }"
          print "  }"
          print "  }"
          print "  }"
          print "  }"
          print "  }"
          print "  }"
          print "  }"
      end
      print ";\n"
      print "  return;\n\n"


      print "  //---------stop pipeline-----------------\n"
      for j in 1..i
          print "  __if_exists(T#{j}::op_stop)\n"
          print "  {\n"
          print "__stop__#{j}__:\n"
          print "    const_cast<T#{j}&>(t#{j})();\n"
          print "    return;\n"
          print "  }\n"
      end

      print "}\n"
      print "\n\n"
  end  
end


def MakeSequentialExecute()
  print "#pragma once\n\n"

  for i in 1..64      
      print "template<typename T1"
      for j in 2..i
          print ", typename T#{j}"
      end
      print ">\n"
      print "__forceinline void ONCE(T1 &&t1"
      for j in 2..i
          print ", T#{j} &&t#{j}"
      end
      print ")\n"
      print "{\n"
      for j in 1..i
          print "  t#{j}();\n"
      end
      print "}\n\n"
  end
end


def MakeParallelStart()
    print "#pragma once\n\n"
    for i in 2..64
        print "template<typename _Function1"
        for j in 2..i
            print ", typename _Function#{j}"
        end
        print ">\n"
        print "__forceinline void PARALLEL(const _Function1 &_Func1"
        for j in 2..i
            print ", const _Function#{j} &_Func#{j}"
        end
        print ")\n"
        print "{\n"
        print "  cpu_manager* cm = cpu_manager::Instance();\n"
        for j in 2..i
          print "  task_obj to#{j} = make_task_obj(_Func#{j});\n"
          print "  cm->run_task(&to#{j});\n"
        end

        print "  _Func1();\n"
        for j in 2..i
          print "  to#{j}.wait();\n";
        end
        print "}\n"
        print "\n//---------------------------------------------\n\n"
    end
end

def MakeObject()
    print "#pragma once\n\n"
    #print "#define ObjectNew new\n\n"
    print "#define ObjectNew new(_aligned_malloc(sizeof(T), __alignof(T)))\n\n"

    print "template<typename T>\n"
    print "T & CreateObject()\n"
    print "{\n"
    print "  return (T&)(*(ObjectNew T()));\n"
    print "}\n"

    for i in 1..64
        print "template<typename T, typename P1"
        for j in 2..i
            print ", typename P#{j}"
        end
        print ">\n"
        print "T & CreateObject(P1 &p1"
        for j in 2..i
            print ", P#{j} &p#{j}"
        end
        print ")\n"
        print "{\n"
        print "  return  (T&)(*(ObjectNew T(p1"
        for j in 2..i
            print ", p#{j}"
        end
        print ")));\n"
        print "}\n"
        print "\n//---------------------------------------------\n\n"
    end
end


#MakeSchedule()
#MakeObject()
MakeParallelStart()
#
#MakePipelineExecutionFunction()
#
#MakePipelineExecutionFunction()
#MakeSequentialExecute()
