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
#ifndef USDGEOM_GENERATED_NURBSCURVES_H
#define USDGEOM_GENERATED_NURBSCURVES_H

#include "pxr/usd/usdGeom/api.h"
#include "pxr/usd/usdGeom/curves.h"
#include "pxr/usd/usd/prim.h"
#include "pxr/usd/usd/stage.h"
#include "pxr/usd/usdGeom/tokens.h"

#include "pxr/base/vt/value.h"

#include "pxr/base/gf/vec3d.h"
#include "pxr/base/gf/vec3f.h"
#include "pxr/base/gf/matrix4d.h"

#include "pxr/base/tf/token.h"
#include "pxr/base/tf/type.h"

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// NURBSCURVES                                                                //
// -------------------------------------------------------------------------- //

/// Nurbs curves are analagous to Maya Nurbs Curves,  used for 
/// interchange of rigging and modeling curves.  Unlike Maya Curves, this 
/// curve spec supports batching of multiple curves into a single prim and 
/// widths in the schema.  Unlike maya, we require 
/// 'numSegments + 2 * degree + 1' knots (2 more than maya does).  This is to
/// be more consistent with renderman's NURBS specification.  
/// 
/// To express a periodic curve:
/// knot[0] = knot[1] - (knots[-2] - knots[-3]; 
/// knot[-1] = knot[-2] + (knot[2] - knots[1]);
/// 
/// To express a nonperiodic curve:
/// knot[0] = knot[1];
/// knot[-1] = knot[-2];
/// 
/// In spite of these slight differences in the spec, curves generated in Maya
/// should be preserved when roundtripping.
///
class UsdGeomNurbsCurves : public UsdGeomCurves
{
public:
    /// Compile-time constant indicating whether or not this class corresponds
    /// to a concrete instantiable prim type in scene description.  If this is
    /// true, GetStaticPrimDefinition() will return a valid prim definition with
    /// a non-empty typeName.
    static const bool IsConcrete = true;

    /// Construct a UsdGeomNurbsCurves on UsdPrim \p prim .
    /// Equivalent to UsdGeomNurbsCurves::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit UsdGeomNurbsCurves(const UsdPrim& prim=UsdPrim())
        : UsdGeomCurves(prim)
    {
    }

    /// Construct a UsdGeomNurbsCurves on the prim held by \p schemaObj .
    /// Should be preferred over UsdGeomNurbsCurves(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit UsdGeomNurbsCurves(const UsdSchemaBase& schemaObj)
        : UsdGeomCurves(schemaObj)
    {
    }

    /// Destructor.
    USDGEOM_API
    virtual ~UsdGeomNurbsCurves();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    USDGEOM_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);

    /// \brief Return a UsdGeomNurbsCurves holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// UsdGeomNurbsCurves(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    USDGEOM_API
    static UsdGeomNurbsCurves
    Get(const UsdStagePtr &stage, const SdfPath &path);

    /// \brief Attempt to ensure a \a UsdPrim adhering to this schema at \p path
    /// is defined (according to UsdPrim::IsDefined()) on this stage.
    ///
    /// If a prim adhering to this schema at \p path is already defined on this
    /// stage, return that prim.  Otherwise author an \a SdfPrimSpec with
    /// \a specifier == \a SdfSpecifierDef and this schema's prim type name for
    /// the prim at \p path at the current EditTarget.  Author \a SdfPrimSpec s
    /// with \p specifier == \a SdfSpecifierDef and empty typeName at the
    /// current EditTarget for any nonexistent, or existing but not \a Defined
    /// ancestors.
    ///
    /// The given \a path must be an absolute prim path that does not contain
    /// any variant selections.
    ///
    /// If it is impossible to author any of the necessary PrimSpecs, (for
    /// example, in case \a path cannot map to the current UsdEditTarget's
    /// namespace) issue an error and return an invalid \a UsdPrim.
    ///
    /// Note that this method may return a defined prim whose typeName does not
    /// specify this schema class, in case a stronger typeName opinion overrides
    /// the opinion at the current EditTarget.
    ///
    USDGEOM_API
    static UsdGeomNurbsCurves
    Define(const UsdStagePtr &stage, const SdfPath &path);

private:
    // needs to invoke _GetStaticTfType.
    friend class UsdSchemaRegistry;
    static const TfType &_GetStaticTfType();

    static bool _IsTypedSchema();

    // override SchemaBase virtuals.
    USDGEOM_API
    virtual const TfType &_GetTfType() const;

public:
    // --------------------------------------------------------------------- //
    // ORDER 
    // --------------------------------------------------------------------- //
    /// Order is degree + 1.  It must be less than or equal to the 
    /// number of cvsPerCurve
    ///
    /// \n  C++ Type: VtArray<int>
    /// \n  Usd Type: SdfValueTypeNames->IntArray
    /// \n  Variability: SdfVariabilityVarying
    /// \n  Fallback Value: []
    USDGEOM_API
    UsdAttribute GetOrderAttr() const;

    /// See GetOrderAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDGEOM_API
    UsdAttribute CreateOrderAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // KNOTS 
    // --------------------------------------------------------------------- //
    /// Knot vectors are batched together and define how to interpolate curve segments.
    ///
    /// \n  C++ Type: VtArray<double>
    /// \n  Usd Type: SdfValueTypeNames->DoubleArray
    /// \n  Variability: SdfVariabilityVarying
    /// \n  Fallback Value: No Fallback
    USDGEOM_API
    UsdAttribute GetKnotsAttr() const;

    /// See GetKnotsAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDGEOM_API
    UsdAttribute CreateKnotsAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // RANGES 
    // --------------------------------------------------------------------- //
    /// Specifies the parametric range used to evaluate the curve.
    ///
    /// \n  C++ Type: VtArray<GfVec2d>
    /// \n  Usd Type: SdfValueTypeNames->Double2Array
    /// \n  Variability: SdfVariabilityVarying
    /// \n  Fallback Value: No Fallback
    USDGEOM_API
    UsdAttribute GetRangesAttr() const;

    /// See GetRangesAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDGEOM_API
    UsdAttribute CreateRangesAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // ===================================================================== //
    // Feel free to add custom code below this line, it will be preserved by 
    // the code generator. 
    //
    // Just remember to close the class delcaration with }; and complete the
    // include guard with #endif
    // ===================================================================== //
    // --(BEGIN CUSTOM CODE)--
};

#endif
