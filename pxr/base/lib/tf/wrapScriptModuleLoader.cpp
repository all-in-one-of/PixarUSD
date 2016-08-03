//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#include "pxr/base/tf/weakPtr.h"
#include "pxr/base/tf/scriptModuleLoader.h"

#include "pxr/base/tf/pySingleton.h"
#include "pxr/base/tf/pyResultConversions.h"

#include <boost/python/class.hpp>

using namespace boost::python;

void wrapScriptModuleLoader() {
    typedef TfScriptModuleLoader This;
    class_<This, TfWeakPtr<This>,
        boost::noncopyable>("ScriptModuleLoader", no_init)
        .def(TfPySingleton())
        .def("GetModuleNames", &This::GetModuleNames,
             return_value_policy<TfPySequenceToList>())
        .def("GetModulesDict", &This::GetModulesDict)
        .def("WriteDotFile", &This::WriteDotFile)

        // For testing purposes only.
        .def("_RegisterLibrary", &This::RegisterLibrary)
        .def("_LoadModulesForLibrary", &This::LoadModulesForLibrary)
        ;
}

#if defined(ARCH_COMPILER_MSVC)
// There is a bug in the compiler which means we have to provide this
// implementation. See here for more information:
// https://connect.microsoft.com/VisualStudio/Feedback/Details/2852624
namespace boost
{
    template<> 
    const volatile TfScriptModuleLoader* 
    get_pointer(const volatile TfScriptModuleLoader* p)
    { 
        return p; 
    }
}
#endif 