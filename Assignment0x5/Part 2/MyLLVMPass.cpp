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
	Value* fib_logger = M.getFunction("fib_logger");
	const Twine &NameStr="mycall";

	for(Function& F: M) {
		if(F.getName() == "fib") {
			for(Function::iterator bb = F.begin(); bb != F.end(); ++bb) {
				for(BasicBlock::iterator i = bb->begin(), e = bb->end(); i != e; ++i) {
					if(isa<CallInst>(i)) {
						Instruction* ci = dyn_cast<Instruction>(i);
						if(cast<CallInst>(i)->getCalledFunction()->getName() == "fib") {
							ConstantInt* h = ConstantInt::get(M.getContext(), APInt(32, StringRef("1"), 10));
							std::vector<Value*> help;
							help.push_back(i->getOperand(0));
							help.push_back(h);	
							CallInst::Create(fib_logger, help, NameStr, ci);
						}
					}
					if(isa<ReturnInst>(i)) {
						Instruction* ci = dyn_cast<Instruction>(i);
						ConstantInt* h = ConstantInt::get(M.getContext(), APInt(32, StringRef("0"), 10));
						std::vector<Value*> help;
						help.push_back(i->getOperand(0));
						help.push_back(h);	
						CallInst::Create(fib_logger, help, NameStr, ci);
					}
				}		
			}
		}
	}
	changed = true;
        return changed;
    }
  };
}

char MyLLVMPass::ID = 0;
static RegisterPass<MyLLVMPass> X("MyLLVMPass", "MyLLVMPass");

