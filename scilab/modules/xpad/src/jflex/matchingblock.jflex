//CHECKSTYLE:OFF

package org.scilab.modules.xpad;

import java.io.IOException;
import javax.swing.text.Element;

%%

%public
%class MatchingBlockScanner
%final
%unicode
%char
%type int
%buffer 256

%switch

%{
    private ScilabDocument doc;
    private Element elem;
    private boolean transp = false;

    public MatchingBlockScanner(ScilabDocument doc) {
        this.doc = doc;
        this.elem = doc.getDefaultRootElement();
    }

    public MatchingPositions getMatchingBlock(int pos, boolean lr) {
        int p1, s = 1;
        transp = false;
        try {
            if (lr) {
                yyreset(new ScilabDocumentReader(doc, pos, doc.getEndPosition().getOffset()));
                yybegin(OPENCLOSE);
                if (yylex() != 1) {
                   return null;
                }

                p1 = pos + yylength();
                yybegin(LR);
            } else {
                 yyreset(new ScilabDocumentReader(doc, true, pos - 1, 0));
                 yybegin(CLOSEOPEN);
                 if (yylex() != 1) {
                    return null;
                 }
                 p1 = pos - yylength();
                 yybegin(RL);
            }

            do {
               if (yylex() == 0) {
                  s--;
               } else {
                  s++;
               }
            } while (zzMarkedPos != 0 && s != 0);
        } catch (IOException e) {
            return null;
        }
        if (s == 0) {
            if (lr) {
                return new MatchingPositions(pos, p1, pos + yychar, pos + yychar + (transp?(yylength()-1):yylength()));
            } else {
                return new MatchingPositions(p1, pos, pos - yychar - yylength(), pos - yychar);
            }
        }

        return null;
    }

    public int getAloneOpenSymbol(int start, int end) {
        int s = 0;
        yyreset(new ScilabDocumentReader(doc, true, end, start));
        yybegin(RLALONE);
        try {
           do {
              if (yylex() == 0) {
                 s--;
              } else {
                 s++;
              }
           } while (zzMarkedPos != 0 && s != -1);
           if (s == -1) {
              return end - yychar - yylength() + 2;
           } else {
              return -1;
           }
        } catch (IOException e) {
            return -1;
        }
    }

    public final class MatchingPositions {
        public int firstB;
        public int firstE;
        public int secondB;
        public int secondE;

        private MatchingPositions(int x1, int x2, int y1, int y2) {
            firstB = x1;
            firstE = x2;
            secondB = y1;
            secondE = y2;
        }
    }
%}

%eofval{
  return -1;
%eofval}

/* main character classes */
eol = \n

comment = "//".*{eol}

tnemmoc = {eol}([^\r\n]*"//")+

spec = [a-zA-Z0-9_#!$?]

id = [a-zA-Z%_#!?][a-zA-Z0-9_#!$?]*

string = (([^\'\"\r\n]*)|([\'\"]{2}))*
qstring = (\"|\'){string}(\"|\')
transp = ({spec} | ")" | "]" | "}") "'"

openK = ("if" | "for" | "while" | "select" | "try" | "function")
openKx = {openK}{spec}+

openS = "(" | "[" | "{"
closeK = ("end" | "endfunction")
closeKx = {closeK}{spec}+
xcloseK = ({spec} | "%" ){closeK}
closeS =  ")" | "]" | "}"

esolcK = ("fi" | "rof" | "elihw" | "tceles" | "yrt" | "noitcnuf")
esolcKx = {spec}{esolcK}
nepoK = ("dne" | "noitcnufdne")
nepoKx = {spec}{nepoK}

psnart = "'" {string} "'" ({spec} | ")" | "]" | "}")

%x LR, RL, OPENCLOSE, CLOSEOPEN, RLALONE

%%

<LR> {
  {transp}                       {
                                   char c = yycharat(yylength() - 2);
                                   if (c == ')' || c == ']' || c == '}') {
                                      transp = true;
                                      return 0;
                                   }
                                 }

  "elseif"                       |
  {comment}                      |
  {openKx}                       |
  {qstring}                      { }

  {openS}                        |
  {openK}                        {
                                   return 1;
                                 }

  {closeS}                       |
  {closeK}                       {
                                   return 0;
                                 }

  {id}                           |
  {closeKx}                      |
  {xcloseK}                      |
  .                              |
  {eol}                          { }
}

<RL> {
  {psnart}                       {
                                   yypushback(yylength() - 1);
                                 }

  "fiesle"                       |
  {tnemmoc}                      |
  {esolcKx}                      |
  {qstring}                      { }

  {closeS}                       |
  {nepoK}                        {
                                   return 1;
                                 }

  {openS}                        |
  {esolcK}                       {
                                   return 0;
                                 }

  {nepoKx}                       |
  .                              |
  {eol}                          { }
}

<RLALONE> {
  {psnart}                       {
                                   yypushback(yylength() - 1);
                                 }

  "fiesle"                       |
  {tnemmoc}                      |
  {esolcKx}                      |
  {qstring}                      { }

  {closeS}                       {
                                   return 1;
                                 }

  {openS}                        {
                                   return 0;
                                 }

  {nepoKx}                       |
  .                              |
  {eol}                          { }
}

<OPENCLOSE> {
  {openKx}                       {
                                   return 0;
                                 }

  {openS}                        |
  {openK}                        {
                                   return 1;
                                 }

  .                              |
  {eol}                          {
                                   return 0;
                                 }
}

<CLOSEOPEN> {
  {nepoKx}                       {
                                   return 0;
                                 }

  {closeS}                       |
  {nepoK}                        {
                                   return 1;
                                 }

  .                              |
  {eol}                          {
                                   return 0;
                                 }
}