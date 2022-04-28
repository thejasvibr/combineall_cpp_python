'''
Triple generation 
=================
Generates consistent triples for a collection of multichannel TDOAs. 
This is S1 in TABLE I of the paper - 'Find all approximately consistent triples'

References
----------
* Scheuing & Yang 2008, ICASSP
'''
import numpy as np 
from itertools import combinations
from dataclasses import dataclass

@dataclass
class triple():
    '''
    Parameters
    ----------
    nodes : tuple
        Tuple with a,b,c nodes (channel #'s) e.g. (0,1,2)
    tde_ab, tde_bc, tde_ca: tuple
        Tuple which represents the time-difference estimate
        of each channel pair in that order, along with the 
        quality of that time-difference. e.g. for tde_ab
        the tuple may be (-5.5e-3, 29.3)

    TODO
    ----
    implement an equals __eq__ for the triple dataclass - to check that
    two triples have the same data
    '''
    nodes : tuple
    tde_ab: tuple
    tde_bc: tuple
    tde_ca: tuple
    
    def __post_init__(self):
        '''generate the triple ID'''
        self.triple_id = str(self.nodes)+'_'+str(self.tde_ab)+'_'+str(self.tde_bc)+'_'+str(self.tde_ca)
        self.quality = np.nan

def generate_consistent_triples(Pprime_kl, **kwargs):
    '''
    Generates all possible consistent triples from the detected TDOAs.
    First calculates all possible triple cases (e.g. for 4 channel recording
    (0,1,2), (1,2,3), (2,3,0), (0,1,3), (0,2,3))
    
    Within each triple case, the consistent triples are chosen and kept as a
    list within the triple-case. 
   
    Parameters
    ----------
    Pprime_kl : dict
    nchannels : int
        Number of channels
    twtm : float
    
    Returns
    -------
    consistent_triples : list
        List with multiple consistent triples.
    '''
    all_triplet_cases = list(combinations(range(kwargs['nchannels']), 3))
    consistent_triples_raw = []
    for triple_case in all_triplet_cases:
        consistent_triples_raw = consistent_triples_raw + choose_consistent_triples(triple_case, Pprime_kl, **kwargs)
    # reformat the contents
    consistent_triples = [ triple(each[0], each[1], each[2], each[3]) for each in consistent_triples_raw]
    return consistent_triples

def choose_consistent_triples(triple_name, Pkl, **kwargs):
    '''
    Parameters
    ----------
    triple_name
    Pkl
    twtm
    
    Returns
    -------
    consistent_triples : list
        List with sublists. Each sublist holds a consistent triple with
        the 4tuples  [(triple-case), (tdoa-ab, tdoa-ab_quality), (tdoa-bc, tdoa-bc_quality),
        (tdoa-ca, tdoa-ca_quality)]
    '''
    pair1, pair2, pair3 = make_channel_pairs_from_triple(triple_name)
    tdoas_12, tdoas_23, tdoas_31 = Pkl[pair1], Pkl[pair2], Pkl[pair3]
    # if any of the tdoas are empty - this triple case is not possible!
    tdoas_lengths = [len(each) for each in [tdoas_12, tdoas_23, tdoas_31]]
    if np.any(tdoas_lengths==0):
        return []
    # now run all through all possible m x n x o value combinations
    consistent_triples = []
    for td12 in tdoas_12:
        for td23 in tdoas_23:
            for td31 in tdoas_31:
                residual = td12[1]+td23[1]+td31[1]
                if abs(residual) <= kwargs['twtm']:
                    triplet = [triple_name,
                               (td12[1], td12[-1]), (td23[1], td23[-1]), (td31[1], td31[-1])]
                    consistent_triples.append(triplet)
    return consistent_triples

def make_channel_pairs_from_triple(triple_name):
    a,b,c = triple_name
    return (a,b), (b,c), (c,a)

def mirror_Pprime_kl(P_primekl):
    ''' The raw Pprime_kl has unique channel pairs, with pairs in 
    descending channel order (smaller channel is reference). 
    e.g. (1,0),(2,0),(3,0),(2,1),(3,1),(3,2)
    
    This function makes all combinations, by changing the sign of the 
    TDOA when the channel order is different. 

    Notes
    -----
    The sample location, coefficient and quality score are left
    as they are!! Only the TDOA in seconds is altered.
    '''
    inverted_ch_order = {}
    for ch_pair, tdoas in P_primekl.items():
        a,b =ch_pair
        inv_order = (b,a)
        inv_tdoas = []
        for tdoa in tdoas:
            tdoa_sec = tdoa[1]
            # only change sign of the TDOA in seconds
            new_tdoa_tuple = (tdoa[0], tdoa_sec*-1, tdoa[2], tdoa[3])
            inv_tdoas.append(new_tdoa_tuple)
        inverted_ch_order[inv_order] = inv_tdoas
    # Now join the two dictionaries together
    pprime_mirrored = {**P_primekl, **inverted_ch_order}
    return pprime_mirrored

if __name__ == '__main__':
    from simdata import simulate_1source_and_3reflector
    from pydatemm.timediffestim import *
    from pydatemm.raster_matching import multichannel_raster_matcher
    from itertools import permutations
    audio, distmat, arraygeom, _ = simulate_1source_and_3reflector()
    fs = 192000
    kwargs = {'nchannels':audio.shape[1], 'twtm':1e-4}
    multich_cc = generate_multich_crosscorr(audio, use_gcc=True)
    multich_ac = generate_multich_autocorr(audio)
    cc_peaks = get_multich_tdoas(multich_cc, min_height=2, fs=192000)
    multiaa = get_multich_aa_tdes(multich_ac, fs=192000, min_height=2) 

    tdoas_rm = multichannel_raster_matcher(cc_peaks, multiaa, twrm=10/fs, array_geom=arraygeom)
    tdoas_mirrored = mirror_Pprime_kl(tdoas_rm)
    true_tdoas = {}
    for chpair, _ in cc_peaks.items():
        ch1, ch2 = chpair
        # get true tDOA
        tdoa = (distmat[0,ch1]-distmat[0,ch2])/340
        true_tdoas[chpair] = tdoa
    #%%
    # Now get all approx consistent triples
    consistent_triples = generate_consistent_triples(tdoas_mirrored, **kwargs)
    