// Copyright (C) 2021 by the IntelliStream team
// (https://github.com/intelliStream) :

//
// Created by Shuhao Zhang on 26/07/2021.
//

#include "Algorithm/AlgorithmFactory.hpp"

#include "Algorithm/Birch.hpp"
#include "Algorithm/CluStream.hpp"
#include "Algorithm/DBStream.hpp"
#include "Algorithm/DStream.hpp"
#include "Algorithm/DataStructure/CoresetTree.hpp"
#include "Algorithm/DataStructure/MeyersonSketch.hpp"
#include "Algorithm/DenStream.hpp"
#include "Algorithm/DesignAspect/Generic.hpp"
#include "Algorithm/DesignAspect/V1.hpp"
#include "Algorithm/DesignAspect/V10.hpp"
#include "Algorithm/DesignAspect/V2.hpp"
#include "Algorithm/DesignAspect/V3.hpp"
#include "Algorithm/DesignAspect/V4.hpp"
#include "Algorithm/DesignAspect/V5.hpp"
#include "Algorithm/DesignAspect/V6.hpp"
#include "Algorithm/DesignAspect/V7.hpp"
#include "Algorithm/DesignAspect/V8.hpp"
#include "Algorithm/DesignAspect/V9.hpp"
#include "Algorithm/EDMStream.hpp"
#include "Algorithm/OutlierDetection/OutlierDetection.hpp"
#include "Algorithm/SlidingWindowClustering.hpp"
#include "Algorithm/StreamKM.hpp"

namespace SESAME
{
AlgorithmPtr AlgorithmFactory::create(param_t &cmd_params)
{
    switch (cmd_params.algo)
    {
    case (StreamKMeansType):
    {
        return std::make_shared<StreamKM>(cmd_params);
    }
    case (CluStreamType):
    {
        return std::make_shared<CluStream>(cmd_params);
    }
    // case (BirchType): {
    //   return std::make_shared<Birch>(cmd_params);
    // }
    case (DenStreamType):
    {
        return std::make_shared<DenStream>(cmd_params);
    }
    case (EDMStreamType):
    {
        return std::make_shared<EDMStream>(cmd_params);
    }
    case (DBStreamType):
    {
        return std::make_shared<DBStream>(cmd_params);
    }
    case (DStreamType):
    {
        return std::make_shared<DStream>(cmd_params);
    }
    case (SLKMeansType):
    {
        return std::make_shared<SlidingWindowClustering>(cmd_params);
    }
    case (V1Stream):
    {
        return std::make_shared<V1>(cmd_params);
    }
    case (V2Stream):
    {
        return std::make_shared<V2>(cmd_params);
    }
    case (V3Stream):
    {
        return std::make_shared<V3>(cmd_params);
    }
    case (V4Stream):
    {
        return std::make_shared<V4>(cmd_params);
    }
    case (V5Stream):
    {
        return std::make_shared<V5>(cmd_params);
    }
    case (V6Stream):
    {
        return std::make_shared<V6>(cmd_params);
    }
    case (V7Stream):
    {
        return std::make_shared<V7>(cmd_params);
    }
    case (V8Stream):
    {
        return std::make_shared<V8>(cmd_params);
    }
    case (V9Stream):
    case (G9Stream):
    {
        return std::make_shared<V9>(cmd_params);
    }
    case (Generic):
    {
        using W = Landmark;
        using D = ClusteringFeaturesTree;
        using O = DistanceDetection<true, false>;
        using R = KMeans;
        shared_ptr<StreamClustering<W, D, O, R>> generic =
            std::make_shared<StreamClustering<W, D, O, R>>(cmd_params);
        return (AlgorithmPtr)generic;
    }
    case (G1Stream):
    {
        return std::make_shared<StreamClustering<Landmark, ClusteringFeaturesTree,
                                                 DistanceDetection<false, false>, KMeans>>(
            cmd_params);
    }
    case (G2Stream):
    {
        return std::make_shared<StreamClustering<Landmark, ClusteringFeaturesTree,
                                                 DistanceDetection<false, false>, DBSCAN>>(
            cmd_params);
    }
    case (G3Stream):
    {
        return std::make_shared<StreamClustering<Landmark, ClusteringFeaturesTree,
                                                 DistanceDetection<false, false>, NoRefinement>>(
            cmd_params);
    }
    case (G4Stream):
    {
        return std::make_shared<StreamClustering<Sliding, ClusteringFeaturesTree,
                                                 DistanceDetection<true, false>, NoRefinement>>(
            cmd_params);
    }
    case (G5Stream):
    {
        return std::make_shared<StreamClustering<Damped, ClusteringFeaturesTree,
                                                 DistanceDetection<false, false>, NoRefinement>>(
            cmd_params);
    }
    case (BirchType):
    {
        return std::make_shared<
            StreamClustering<Landmark, ClusteringFeaturesTree, NoDetection, NoRefinement>>(
            cmd_params);
    }
    case (G6Stream):
    {
        return std::make_shared<
            StreamClustering<Landmark, ClusteringFeaturesTree, NoDetection, NoRefinement>>(
            cmd_params);
    }
    case (G7Stream):
    {
        return std::make_shared<StreamClustering<Landmark, ClusteringFeaturesTree,
                                                 DensityDetection<true, false>, NoRefinement>>(
            cmd_params);
    }
    case (G8Stream):
    {
        return std::make_shared<StreamClustering<Landmark, ClusteringFeaturesList,
                                                 DistanceDetection<false, false>, NoRefinement>>(
            cmd_params);
    }
    case (G10Stream):
    {
        return std::make_shared<V10>(cmd_params);
    }
    case (G11Stream):
    {
        return std::make_shared<StreamClustering<Landmark, ClusteringFeaturesTree,
                                                 DistanceDetection<false, true>, NoRefinement>>(
            cmd_params);
    }
    case (G12Stream):
    {
        return std::make_shared<StreamClustering<Landmark, ClusteringFeaturesTree,
                                                 DistanceDetection<false, false>, NoRefinement>>(
            cmd_params);
    }
    case (G13Stream):
    {
        return std::make_shared<StreamClustering<Landmark, ClusteringFeaturesTree,
                                                 DistanceDetection<true, true>, NoRefinement>>(
            cmd_params);
    }
    case (G14Stream):
    {
        return std::make_shared<StreamClustering<Landmark, MeyersonSketch,
                                                 OutlierDetection<false, false>, NoRefinement>>(
            cmd_params);
    }
    case (G15Stream):
    {
        return std::make_shared<
            StreamClustering<Landmark, CoresetTree, OutlierDetection<false, false>, NoRefinement>>(
            cmd_params);
    }
    default: throw std::invalid_argument("Unsupported algorithm");
    }
}

}  // namespace SESAME
