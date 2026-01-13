.entryy Label1

Label1: cmp    #-123,     NotExistLabel

	dec    #123

	lea ExternLabel,   r4

LabelStr:	.string "String-at-label3" extra-text

WarningLabel:  .entry   LabelData

LabelData:     .data    1, 0000012345  ,3

Label2: mov	LabelData,    r2
.extern ExternLabel
	
	inc 	NotExistLabel

	jmp	Label1(r1,r2)

.entry	NotExistLabel
