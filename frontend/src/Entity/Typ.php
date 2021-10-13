<?php

namespace App\Entity;

use Doctrine\ORM\Mapping as ORM;

/**
 * Typ
 *
 * @ORM\Table(name="Typ")
 * @ORM\Entity
 */
class Typ
{
    /**
     * @var int
     *
     * @ORM\Column(name="Typ_ID", type="integer", nullable=false, options={"unsigned"=true})
     * @ORM\Id
     * @ORM\GeneratedValue(strategy="IDENTITY")
     */
    private $typId;

    /**
     * @var string|null
     *
     * @ORM\Column(name="Bezeichnung", type="text", length=65535, nullable=true)
     */
    private $bezeichnung;

    /**
     * @var string
     *
     * @ORM\Column(name="Decoder", type="text", length=65535, nullable=false)
     */
    private $decoder;

    /**
     * @return int
     */
    public function getTypId(): int
    {
        return $this->typId;
    }

    /**
     * @param int $typId
     */
    public function setTypId(int $typId): void
    {
        $this->typId = $typId;
    }

    /**
     * @return string|null
     */
    public function getBezeichnung(): ?string
    {
        return $this->bezeichnung;
    }

    /**
     * @param string|null $bezeichnung
     */
    public function setBezeichnung(?string $bezeichnung): void
    {
        $this->bezeichnung = $bezeichnung;
    }

    /**
     * @return string
     */
    public function getDecoder(): string
    {
        return $this->decoder;
    }

    /**
     * @param string $decoder
     */
    public function setDecoder(string $decoder): void
    {
        $this->decoder = $decoder;
    }


}
