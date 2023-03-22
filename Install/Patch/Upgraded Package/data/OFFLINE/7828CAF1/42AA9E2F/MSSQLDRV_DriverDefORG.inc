            Move SQL_BIGINT         to ColumnType[i].iSQLType
            Move "bigint"           to ColumnType[i].sSQLType
            Move DF_BCD             to ColumnType[i].iDataFlexType
            Move "Numeric"          to ColumnType[i].sDataFlexType
            Move "14.0"             to ColumnType[i].sPrecision
            Move True               to ColumnType[i].bCanEditSize
            Increment i

            Move SQL_BINARY         to ColumnType[i].iSQLType
            Move "binary"           to ColumnType[i].sSQLType
            Move DF_BINARY          to ColumnType[i].iDataFlexType
            Move "Binary"           to ColumnType[i].sDataFlexType
            Move "8000"             to ColumnType[i].sPrecision
            Increment i

            Move SQL_BIT            to ColumnType[i].iSQLType
            Move "bit"              to ColumnType[i].sSQLType
            Move DF_ASCII           to ColumnType[i].iDataFlexType
            Move "ASCII"            to ColumnType[i].sDataFlexType
            Move "1.0"              to ColumnType[i].sPrecision // In SQL allows "1, 0, or NULL"
            Move True               to ColumnType[i].bCanEditSize
            Increment i

            Move SQL_CHAR           to ColumnType[i].iSQLType
            Move "char"             to ColumnType[i].sSQLType
            Move DF_TEXT            to ColumnType[i].iDataFlexType
            Move "TEXT"             to ColumnType[i].sDataFlexType
            Move "8000"             to ColumnType[i].sPrecision
            Increment i

            Move SQL_DATE           to ColumnType[i].iSQLType
            Move "date"             to ColumnType[i].sSQLType
            Move DF_DATE            to ColumnType[i].iDataFlexType
            Move "Date"             to ColumnType[i].sDataFlexType
            Move "6.0"              to ColumnType[i].sPrecision
            Move True               to ColumnType[i].bCanEditSize
            Increment i

            Move SQL_DATETIME       to ColumnType[i].iSQLType
            Move "datetime"         to ColumnType[i].sSQLType
            Move DF_DATETIME        to ColumnType[i].iDataFlexType
            Move "DateTime"         to ColumnType[i].sDataFlexType
            Move "23.3"             to ColumnType[i].sPrecision
            Move True               to ColumnType[i].bCanEditSize
            Increment i

            Move SQL_TYPE_TIMESTAMP2 to ColumnType[i].iSQLType
            Move "datetime2"         to ColumnType[i].sSQLType
            Move DF_DATETIME         to ColumnType[i].iDataFlexType
            Move "DateTime"          to ColumnType[i].sDataFlexType
            Move "23.6"              to ColumnType[i].sPrecision
            Move True                to ColumnType[i].bCanEditSize
            Increment i

            Move SQL_SS_TIMESTAMPOFFSET to ColumnType[i].iSQLType
            Move "datetimeoffset"       to ColumnType[i].sSQLType
            Move DF_DATETIME            to ColumnType[i].iDataFlexType
            Move "DateTime"             to ColumnType[i].sDataFlexType
            Move "34.0"                 to ColumnType[i].sPrecision
            Move True                   to ColumnType[i].bCanEditSize
            Increment i

            Move SQL_DECIMAL        to ColumnType[i].iSQLType
            Move "decimal"          to ColumnType[i].sSQLType
            Move DF_BCD             to ColumnType[i].iDataFlexType
            Move "Numeric"          to ColumnType[i].sDataFlexType
            Move "14.8"             to ColumnType[i].sPrecision
            Increment i

            Move SQL_FLOAT          to ColumnType[i].iSQLType
            Move "float"            to ColumnType[i].sSQLType
            Move DF_BCD             to ColumnType[i].iDataFlexType
            Move "Numeric"          to ColumnType[i].sDataFlexType
            Move "14.8"             to ColumnType[i].sPrecision
            Increment i

            Move SQL_INTEGER        to ColumnType[i].iSQLType
            Move "int"              to ColumnType[i].sSQLType
            Move DF_BCD             to ColumnType[i].iDataFlexType
            Move "Numeric"          to ColumnType[i].sDataFlexType
            Move "8.0"              to ColumnType[i].sPrecision
            Move True               to ColumnType[i].bCanEditSize
            Increment i

            Move SQL_TYPE_MONEY     to ColumnType[i].iSQLType
            Move "money"            to ColumnType[i].sSQLType
            Move DF_BCD             to ColumnType[i].iDataFlexType
            Move "Numeric"          to ColumnType[i].sDataFlexType
            Move "15.4"             to ColumnType[i].sPrecision // Studio 18.0 (!)
            Increment i

            Move SQL_WCHAR          to ColumnType[i].iSQLType
            Move "nchar"            to ColumnType[i].sSQLType
            Move DF_TEXT            to ColumnType[i].iDataFlexType
            Move "TEXT"             to ColumnType[i].sDataFlexType
            Move "4000"             to ColumnType[i].sPrecision
            Increment i

            Move SQL_WLONGVARCHAR   to ColumnType[i].iSQLType
            Move "ntext"            to ColumnType[i].sSQLType
            Move DF_TEXT            to ColumnType[i].iDataFlexType
            Move "TEXT"             to ColumnType[i].sDataFlexType
            Move "16384"            to ColumnType[i].sPrecision
            Increment i

            Move SQL_NUMERIC        to ColumnType[i].iSQLType
            Move "numeric"          to ColumnType[i].sSQLType
            Move DF_BCD             to ColumnType[i].iDataFlexType
            Move "Numeric"          to ColumnType[i].sDataFlexType
            Move "14.8"             to ColumnType[i].sPrecision
            Increment i

            Move SQL_WVARCHAR       to ColumnType[i].iSQLType
            Move "nvarchar"         to ColumnType[i].sSQLType
            Move DF_TEXT            to ColumnType[i].iDataFlexType
            Move "Text"             to ColumnType[i].sDataFlexType
            Move "4000"             to ColumnType[i].sPrecision
            Increment i

            Move SQL_VARCHARMAX     to ColumnType[i].iSQLType
            Move "nvarchar(max)"    to ColumnType[i].sSQLType
            Move DF_TEXT            to ColumnType[i].iDataFlexType
            Move "TEXT"             to ColumnType[i].sDataFlexType
            Move "16384"            to ColumnType[i].sPrecision
            Move True               to ColumnType[i].bCanEditSize
            Increment i

            Move SQL_REAL           to ColumnType[i].iSQLType
            Move "real"             to ColumnType[i].sSQLType
            Move DF_BCD             to ColumnType[i].iDataFlexType
            Move "NUMERIC"          to ColumnType[i].sDataFlexType
            Move "14.8"             to ColumnType[i].sPrecision
            Increment i

            Move SQL_TYPE_SMALLDATETIME to ColumnType[i].iSQLType
            Move "smalldatetime"        to ColumnType[i].sSQLType
            Move DF_DATETIME            to ColumnType[i].iDataFlexType
            Move "DATETIME"             to ColumnType[i].sDataFlexType
            Move "23.0"                 to ColumnType[i].sPrecision
            Move True                   to ColumnType[i].bCanEditSize
            Increment i

            Move SQL_SMALLINT       to ColumnType[i].iSQLType
            Move "smallint"         to ColumnType[i].sSQLType
            Move DF_BCD             to ColumnType[i].iDataFlexType
            Move "NUMERIC"          to ColumnType[i].sDataFlexType
            Move "4.0"              to ColumnType[i].sPrecision
            Move True               to ColumnType[i].bCanEditSize
            Increment i

            Move SQL_TYPE_SMALLMONEY to ColumnType[i].iSQLType
            Move "smallmoney"        to ColumnType[i].sSQLType
            Move DF_BCD              to ColumnType[i].iDataFlexType
            Move "NUMERIC"           to ColumnType[i].sDataFlexType
            Move "10.0"              to ColumnType[i].sPrecision
            Increment i

            Move SQL_TEXT           to ColumnType[i].iSQLType
            Move "text"             to ColumnType[i].sSQLType
            Move DF_TEXT            to ColumnType[i].iDataFlexType
            Move "TEXT"             to ColumnType[i].sDataFlexType
            Move "8000"             to ColumnType[i].sPrecision
            Move True               to ColumnType[i].bCanEditSize
            Increment i

            Move SQL_TIME           to ColumnType[i].iSQLType
            Move "time"             to ColumnType[i].sSQLType
            Move DF_ASCII           to ColumnType[i].iDataFlexType
            Move "ASCII"            to ColumnType[i].sDataFlexType
            Move "19.0"             to ColumnType[i].sPrecision
            Move True               to ColumnType[i].bCanEditSize
            Increment i

            Move SQL_TINYINT        to ColumnType[i].iSQLType
            Move "tinyint"          to ColumnType[i].sSQLType
            Move DF_BCD             to ColumnType[i].iDataFlexType
            Move "NUMERIC"          to ColumnType[i].sDataFlexType
            Move "2.0"              to ColumnType[i].sPrecision
            Move True               to ColumnType[i].bCanEditSize
            Increment i

            Move SQL_GUID           to ColumnType[i].iSQLType
            Move "uniqueidentifier" to ColumnType[i].sSQLType
            Move DF_ASCII           to ColumnType[i].iDataFlexType
            Move "ASCII"            to ColumnType[i].sDataFlexType
            Move "36"               to ColumnType[i].sPrecision
            Move True               to ColumnType[i].bCanEditSize
            Increment i

            Move SQL_VARBINARY      to ColumnType[i].iSQLType
            Move "varbinary"        to ColumnType[i].sSQLType
            Move DF_BINARY          to ColumnType[i].iDataFlexType
            Move "BINARY"           to ColumnType[i].sDataFlexType
            Move "16384"            to ColumnType[i].sPrecision
            Increment i

            Move SQL_LONGVARBINARY  to ColumnType[i].iSQLType
            Move "varbinary(max)"   to ColumnType[i].sSQLType
            Move DF_BINARY          to ColumnType[i].iDataFlexType
            Move "BINARY"           to ColumnType[i].sDataFlexType
            Move "16384"            to ColumnType[i].sPrecision
            Move True               to ColumnType[i].bCanEditSize
            Increment i

            Move SQL_VARCHAR        to ColumnType[i].iSQLType
            Move "varchar"          to ColumnType[i].sSQLType
            Move DF_TEXT            to ColumnType[i].iDataFlexType // ToDo: Under 255 = ASCII type! How to deal with this?
            Move "TEXT"             to ColumnType[i].sDataFlexType
            Move "8000"             to ColumnType[i].sPrecision
            Increment i

            Move SQL_LONGVARCHAR    to ColumnType[i].iSQLType
            Move "varchar(max)"     to ColumnType[i].sSQLType
            Move DF_TEXT            to ColumnType[i].iDataFlexType
            Move "TEXT"             to ColumnType[i].sDataFlexType
            Move "16384"            to ColumnType[i].sPrecision
            Move True               to ColumnType[i].bCanEditSize
            Increment i

            Move SQL_SS_XML         to ColumnType[i].iSQLType
            Move "xml"              to ColumnType[i].sSQLType
            Move DF_TEXT            to ColumnType[i].iDataFlexType
            Move "TEXT"             to ColumnType[i].sDataFlexType
            Move "16384"            to ColumnType[i].sPrecision
            Increment i

            Move SQL_TYPE_DATE      to ColumnType[i].iSQLType
            Move "DATE"             to ColumnType[i].sSQLType
            Move DF_DATE            to ColumnType[i].iDataFlexType
            Move "date"             to ColumnType[i].sDataFlexType
            Move "6.0"              to ColumnType[i].sPrecision
            Move True               to ColumnType[i].bCanEditSize
            Increment i

            Move SQL_TYPE_TIME      to ColumnType[i].iSQLType
            Move "time"             to ColumnType[i].sSQLType
            Move DF_ASCII           to ColumnType[i].iDataFlexType
            Move "ASCII"            to ColumnType[i].sDataFlexType
            Move "8.7"              to ColumnType[i].sPrecision
            Move True               to ColumnType[i].bCanEditSize
            Increment i

            Move SQL_TYPE_TIMESTAMP to ColumnType[i].iSQLType
            Move "datetime"         to ColumnType[i].sSQLType
            Move DF_DATETIME        to ColumnType[i].iDataFlexType
            Move "DateTime"         to ColumnType[i].sDataFlexType
            Move "23.6"             to ColumnType[i].sPrecision
            Move True               to ColumnType[i].bCanEditSize
            Increment i
