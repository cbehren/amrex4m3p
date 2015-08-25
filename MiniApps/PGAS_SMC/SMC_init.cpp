
#include <SMC.H>
#include <SMC_F.H>

void
SMC::build_multifabs ()
{
    IntVect dlo(0, 0, 0);
    IntVect dhi(ncell[0]-1, ncell[1]-1, ncell[2]-1);
    Box bx(dlo, dhi);

    BoxArray ba(bx);
    ba.maxSize(max_grid_size);

    if (ParallelDescriptor::IOProcessor()) {
	std::cout << "Number of boxes: " << ba.size() << std::endl;
    }

    RealBox real_box(prob_lo.dataPtr(), prob_hi.dataPtr());  // physical size
    int coord = 0; // Cartesian coordinates
    Array<int> is_per(3, 1); // triply periodic
    geom.define(bx, &real_box, 0, &is_per[0]);

         U.define(ba, ncons, ngrow, Fab_allocate);
      Utmp.define(ba, ncons, ngrow, Fab_allocate);
    Uprime.define(ba, ncons, 0    , Fab_allocate);
         Q.define(ba, nprim, ngrow, Fab_allocate);
        mu.define(ba, 1    , ngrow, Fab_allocate);
        xi.define(ba, 1    , ngrow, Fab_allocate);
       lam.define(ba, 1    , ngrow, Fab_allocate);
     Ddiag.define(ba, nspec, ngrow, Fab_allocate);

    Q.setVal(0.0);
}

void
SMC::init_from_scratch ()
{
    t = 0.0;
    dt = 1.e10;
    courno = -1.e10;
    for (int i=0; i<3; ++i) {
	dx[i] = (prob_hi[i]-prob_lo[i]) / Real(ncell[i]);
    }

#ifdef _OPENMP
#pragma omp parallel
#endif    
    for (MFIter mfi(U,true); mfi.isValid(); ++mfi)
    {
	const Box& bx  = mfi.tilebox();
	const Box& vbx = mfi.validbox();

	init_data_3d(bx.loVect(), bx.hiVect(), vbx.loVect(), vbx.hiVect(), &ngrow, 
		     dx, U[mfi].dataPtr(), prob_lo.dataPtr(), prob_hi.dataPtr());
    }
}