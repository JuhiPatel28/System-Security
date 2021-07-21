//===- MyLLVMPass.cpp - Example code from "Writing an LLVM Pass" ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements two versions of the LLVM "Hello World" pass described
// in docs/WritingAnLLVMPass.html
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "hello"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

#include <llvm/Pass.h>
#include <llvm/PassManager.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/InlineAsm.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/MathExtras.h>
#include <algorithm>

#include "llvm/IR/IRBuilder.h"

using namespace llvm;

StringRef fname;

namespace {
    // Hello - The first implementation, without getAnalysisUsage.
    struct MyLLVMPass : public ModulePass {
    static char ID; // Pass identification, replacement for typeid
      
    MyLLVMPass() : ModulePass(ID) {
    }
    
    virtual bool runOnModule(Module &M) {
        bool changed = false;

	errs() << "\nFor the Module,\n";
	for (auto g = M.global_begin(); g != M.global_end(); ++g) {
		GlobalVariable *gv = &*g;
		Type *t = gv->getType();
		const Twine &n = gv->getName();
		Constant* v;

		errs() << "NAME: " << n << ", TYPE: ";
		t->dump();
		if(gv->hasInitializer()){
			v = gv->getInitializer();
			errs() << ", VALUE: ";
			v->dump();
		}
	}
	for (auto g = M.begin(); g != M.end(); ++g) {
		Function *gv = &*g;
		Type *t = gv->getType();
		const Twine &n = gv->getName();
		errs() << "NAME: " << n << ", PROTOTYPE: ";
		t->dump();
		errs() << "\n";
	    }

	errs() << "\nFor each Function,\n";
	for(Function& F: M) {
		errs() << "INPUT PARAMS & TYPES: ";
		for(auto& A : F.getArgumentList()) {
			errs() << A << ", ";
		}

		Type *t = F.getReturnType();

		errs() << "RETURN TYPE: ";
		t->dump();
		
		int c = 0;
		for(BasicBlock& bb : F)	{
			c++;
		}
		errs() << ", # OF BASIC BLOCKS: " << c << "\n";
		
	}

	errs() << "\nFor each basic block,\n";
	for(Function& F: M) {
		for(BasicBlock& bb : F)	{
			int c = 0;
			for(Instruction& i : bb) {
				const char* n = i.getOpcodeName();
				unsigned o = i.getOpcode();
				errs() << "INST NAME: " << n << ", OPERAND: " << o << "\n";
				c++;
			}
			errs() << "# OF INSTRUCTIONS IN THIS BASIC BLOCK: " << c << "\n\n";
				
		}
	}
	changed = false;
        return changed;
    }
  };
}

char MyLLVMPass::ID = 0;
static RegisterPass<MyLLVMPass> X("MyLLVMPass", "MyLLVMPass");

