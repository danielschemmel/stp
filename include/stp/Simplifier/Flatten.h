/********************************************************************
 * AUTHORS: Trevor Hansen
 *
  *
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
********************************************************************/

/*
 Sharing aware flattening. 

* For example, given something like ((x + y ) + z) if this is the only occurence of (x+y) anywhere, then transform it into (x + y + z)
* Given ((x+ g) + (x+g)) it shouldn't do anything, even if this is the only reference to (x+g).
* This isn't idempotent. Node creation time simplifications might prune nodes, reducing their count and making extra nodes eligible for flattening.
*/

#ifndef FLATTEN_H_
#define FLATTEN_H_


#include "stp/AST/AST.h"
#include "stp/STPManager/STPManager.h"
#include "stp/Simplifier/Simplifier.h"
#include <map>

namespace stp
{

class Flatten
{
  STPMgr* stpMgr;
  NodeFactory* nf;

  std::unordered_map<uint64_t, uint8_t> shareCount;
  std::unordered_map<uint64_t, ASTNode> fromTo;

  int removed;
  int top_removed;

  // sharecount is 1 if the node has one reference in the tree.
  void buildShareCount(const ASTNode& n);
  ASTNode flatten(const ASTNode& n, bool top=false);

public:
  Flatten(const Flatten&) = delete;
  Flatten & operator=(const Flatten&) = delete;
  
  Flatten(STPMgr* stp_, NodeFactory* nf_)
  {
    stpMgr = stp_;
    nf = nf_;
  }

  ASTNode topLevel(ASTNode& n);
};
}

#endif
