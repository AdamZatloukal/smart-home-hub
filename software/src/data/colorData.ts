export type colorDataType = {
    color: string
    isFavourite: boolean
}[]

export type colorDataTypeSingle = {
    color: string
    isFavourite: boolean
}

export const defaultData: colorDataType = [
    {
        color: "#ffffff",
        isFavourite: true
    }
]