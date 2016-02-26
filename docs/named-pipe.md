Named pipe
==========

- For comunication with WPF gui

- Message examples:
	1. Process image - apply matrix 3x3:
		- Template: "REQUEST:{<proces name>}_PARAMS:{mWidth,mHeight,bias,factor,m0.0f,m0.1f,m1.0f,..}<image datas>"
		- Sample sharpen: "REQUEST:{matrix}_PARAMS:{3,3,0.0,0.0,-1.0,-1.0,-1.0,-1.0,-9.0,-1.0,-1.0,-1.0,-1.0}"