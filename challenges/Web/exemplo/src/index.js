const express = require('express')

const app = express()


app.get('/health', (_, res) => res.status(200).json())


const PORT = process.env.PORT || 3000


app.listen(process.env.PORT, () => console.log(`Listening http://localhost:${PORT}`))