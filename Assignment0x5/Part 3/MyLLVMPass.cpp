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
    	static const char xorKey = 0x07;  // bell -- non-printable character.
	int xorCipher(char *dst, char *src) {
	    int len = strlen(src);
	    for (int i = 0; i < len; i++) {
		//  Not a good cipher.
		dst[i] = src[i] ^ xorKey;
	    }
	    dst[len] = '\0';
	    return len;
	}
    virtual bool runOnModule(Module &M) {
        bool changed = false;
	auto &Ctx = M.getContext();

	for (auto g = M.global_begin(); g != M.global_end(); ++g) {
		GlobalVariable *gv = g;
		if(gv->hasInitializer()){
			Constant *Initializer = gv->getInitializer();
			if(isa<ConstantDataArray>(Initializer)) {
				auto v = dyn_cast<ConstantDataArray>(gv->getInitializer());
				if(v->isString()) {
					std::string x = v->getAsCString();
					char *extract = new char[x.length() + 1];
					std::copy(x.begin(), x.end(), extract);
					extract[x.size()] = '\0'; 
					//errs() << "Original: " << extract;
					//errs() << "\n";
					char *cypher = new char[x.length() + 1];
					int h = xorCipher(cypher, extract);
					//errs() << "Obfuscated: " << cypher;
					//errs() << "\n";

					Constant *NewConst = ConstantDataArray::getString(Ctx, StringRef(cypher, x.length() + 1), false);
					//NewConst->dump();
					//errs() << "Original: ";
					//gv->getInitializer()->dump();
					gv->setInitializer(NewConst);
					//errs() << "Obfuscated: ";
					//gv->getInitializer()->dump();

					
										

					/*
					Value* xorcypher = M.getFunction("xorCipher");
					const Twine &NameStr="mycall";
					std::vector<Value*> help;
					help.push_back(i->getOperand(0));
					help.push_back(i->getOperand(0));
					CallInst::Create(fib_logger, help, NameStr, i);
					*/
				}
			}
		}
	}

	for(Function& F: M) {
		for(BasicBlock& bb : F)	{
			for(Instruction& i : bb) {
				if(isa<GetElementPtrInst>(i) || isa<CallInst>(i)) {
					errs() << "Outside \n" << i;
				
					//errs() << i.getNumOperands() << "\n";
					for(unsigned int x = 0; x < i.getNumOperands(); x++){
						auto A = i.getOperand(x);
						//A->dump();
						if(isa<GetElementPtrInst>(A) || isa<CallInst>(A))
						{
							Instruction * AB = dyn_cast<Instruction>(A);
							for(unsigned int x = 0; x < AB->getNumOperands(); x++) {
								auto B = AB->getOperand(x);
								errs() << "Inside \n";
								AB->dump();
								//B->dump();
								errs() << "\n";
								if(isa<GlobalVariable>(B))
								{
									errs() << A << "\n Global Operands: \n\n";
									B->dump();
								}								
							}
						}
						if(isa<GlobalVariable>(A))
						{
							errs() << i << "\n Global Operands: \n\n";
							A->dump();
						}
					}
				}
			}									
		}
	}

	changed = false;
        return changed;
    }
  };

}


char MyLLVMPass::ID = 0;
static RegisterPass<MyLLVMPass> X("MyLLVMPass", "MyLLVMPass");

